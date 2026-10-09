# 第 08 章讲义：Tensor、MemRef、形状与 Affine

> 本讲先建立模型并读懂完整例子；练习与工具验证放在讲义之后，待本讲概念清楚再做。目标是能从 IR 判断数据表示、存储是否可变、形状信息在哪里，以及索引表达式是否属于 Affine。

## 1. 本章路线

1. Tensor 与 MemRef 的语义差别：SSA 值与可变内存。
2. 类型中的 rank、维度、元素类型和布局。
3. `tensor.extract` / `tensor.insert` 与 `memref.load` / `memref.store`。
4. 动态形状、`index` 和维度查询。
5. Tensor 切片与 MemRef 视图的差异，认识 Bufferization 的工作。
6. Affine 的维度、符号、合法表达式和适用场景。
7. 验证器能保证什么、不能证明什么。

整体上可以把一段数组计算分成三层观察：

| 层 | 要问的问题 | 常见表达 |
| --- | --- | --- |
| 逻辑数据与形状 | 有几维、每维多长、元素是什么类型？ | `tensor<2x3xf32>`、`memref<?xi32>` |
| 值与存储 | 这是一个不可变的 SSA 张量值，还是指向存储的 MemRef？ | `tensor.insert`、`memref.store` |
| 索引与迭代 | 循环迭代坐标如何映射到数据坐标？ | `index`、`affine.apply`、`affine.for` |

## 2. Tensor：不可变的多维 SSA 值

MLIR 的 `tensor` 类型表达有形状的多维值。它遵循 SSA：定义一个新值后，不能通过写操作改变那个 SSA 值本身。Tensor 类型属于 Builtin 类型体系，tensor dialect 提供创建、提取和组合这类值的操作。[Tensor Dialect](https://mlir.llvm.org/docs/Dialects/TensorOps/)

例如 `tensor<2xi32>` 表示一维、长度为 2、元素为 `i32` 的张量。下面创建 `[1, 2]`，再产生一个把第 0 项替换为 9 的新张量：

```mlir
func.func @tensor_example() -> (i32, i32) {
  %c1 = arith.constant 1 : i32
  %c2 = arith.constant 2 : i32
  %c9 = arith.constant 9 : i32
  %i0 = arith.constant 0 : index
  %t = tensor.from_elements %c1, %c2 : tensor<2xi32>
  %t2 = tensor.insert %c9 into %t[%i0] : tensor<2xi32>
  %old = tensor.extract %t[%i0] : tensor<2xi32>
  %new = tensor.extract %t2[%i0] : tensor<2xi32>
  return %old, %new : i32, i32
}
```

从语义上看，`%t` 仍表示 `[1, 2]`，`%t2` 表示 `[9, 2]`，因此 `%old` 是 1、`%new` 是 9。`tensor.insert` 的结果是新张量值，不是对 `%t` 做原地写入。实现时编译器可以消除不必要的数据复制；语义上的“新值”不等于机器上必然复制整块内存。

常见相关操作：

- `tensor.from_elements`：从标量元素形成小型张量。
- `tensor.empty`：产生具有给定形状的未初始化张量载体，元素值不能据此假定为零。
- `tensor.extract`：读取指定坐标的标量。
- `tensor.insert`：返回替换指定坐标后的张量值。
- `tensor.extract_slice` / `tensor.insert_slice`：提取或组合切片，仍按张量值语义建模。

因此，看到 `tensor.insert` 不要直接推断它像 C 数组赋值一样修改既有对象。沿 SSA use-def 链看它的结果被后续哪些操作使用。

## 3. MemRef：有形状和布局的内存引用

`memref` 类型描述一个可索引的内存引用。它不只是“裸指针”：类型还可能携带形状、元素类型、内存空间和布局信息。通过 `memref.store` 写入会影响该引用所指向的存储；`memref.load` 从该存储读取值。[MemRef Dialect](https://mlir.llvm.org/docs/Dialects/MemRef/)

```mlir
func.func @memref_example() -> i32 {
  %m = memref.alloc() : memref<2xi32>
  %i0 = arith.constant 0 : index
  %i1 = arith.constant 1 : index
  %c1 = arith.constant 1 : i32
  %c2 = arith.constant 2 : i32
  %c9 = arith.constant 9 : i32
  memref.store %c1, %m[%i0] : memref<2xi32>
  memref.store %c2, %m[%i1] : memref<2xi32>
  memref.store %c9, %m[%i0] : memref<2xi32>
  %value = memref.load %m[%i0] : memref<2xi32>
  memref.dealloc %m : memref<2xi32>
  return %value : i32
}
```

这里先写 `[1, 2]`，再把第 0 项改成 9；随后 load 取得标量 SSA 值 `%value`，释放 `%m` 的存储，然后返回已读出的标量。典型操作包括：

- `memref.alloc`：动态分配存储，常见情况下由 `memref.dealloc` 释放。
- `memref.alloca`：在栈式/局部分配作用域分配，生命周期受作用域约束。
- `memref.load` / `memref.store`：从指定索引读取或写入元素。
- `memref.dim`：查询某一维的运行时大小。
- `memref.subview`：构造一个指向部分区域的视图，通常与源 MemRef 共享存储。

Tensor 的 `insert` 表达新值；MemRef 的 `store` 表达对可变存储的写入。理解这条分界线，是后续 Bufferization（把张量式值计算落实为内存读写）和别名分析的基础。

## 4. 读懂形状、rank、动态维度与布局

类型中 `x` 分隔维度，最末尾的标量类型是元素类型：

| 类型 | 含义 |
| --- | --- |
| `tensor<2xi32>` | rank 1，形状为 `[2]`，元素 `i32` |
| `tensor<2x3xf32>` | rank 2，形状为 `[2, 3]`，元素 `f32` |
| `tensor<?x4xf32>` | rank 2，第 0 维动态，第 1 维固定为 4 |
| `memref<4x?xf32>` | rank 2，第 0 维固定为 4，第 1 维动态 |
| `memref<4x4xf32, strided<[4, 1]>>` | rank 2，并显式描述每维步长的布局示例 |

### 5.1 `strided<[4, 1]>` 到底表示什么？

`strided` 可以先直观地理解为“沿着每个维度前进一步时，在一维底层存储中跨过多少个**元素**”。它不是按字节计数，也不是数组的维度长度。对 rank 2 的 MemRef，方括号里按维度顺序给出两个 stride：

- 第一个 `4`：第 0 维（通常称行维）索引加 1，线性存储位置前进 4 个 `f32` 元素。
- 第二个 `1`：第 1 维（通常称列维）索引加 1，线性存储位置前进 1 个 `f32` 元素。

若省略 offset，这个例子的 offset 默认为 0。对索引 `[%i, %j]`，对应的线性**元素**偏移是：

```text
offset + %i * 4 + %j * 1
```

例如 `[%i = 2, %j = 1]` 对应 `2*4 + 1*1 = 9`，即从起始处数第 9 个元素（从 0 开始）。若 `f32` 占 4 字节，对应字节偏移才是 `9*4 = 36` 字节。地址计算可理解为：`base + element_offset * sizeof(f32)`。

对 `memref<4x4xf32>`，`[4,1]` 正是常见行优先连续布局：

```text
逻辑坐标       线性元素偏移
[0,0]          0*4 + 0 = 0
[0,1]          0*4 + 1 = 1
[1,0]          1*4 + 0 = 4
[3,3]          3*4 + 3 = 15
```

可以把 16 个元素排成线性内存 `[a00,a01,a02,a03, a10,a11,a12,a13, ...]`。同一行相邻元素挨着；下一行的起点比上一行起点前进 4 个元素。一般 `MxN` 的行优先连续布局为 `[N,1]`。所以对 `4x4` 是 `[4,1]`；对 `4x8` 则是 `[8,1]`。

步长也能表达非连续视图。比如 `[8,2]` 表示换行跨 8 个元素、同一行换列跨 2 个元素，因而列方向会跳过中间元素。布局中的 stride 负责“坐标到线性位置”的映射；`4x4` 的 shape 负责“每个维度允许哪些合法坐标”。二者回答不同问题。

### 5.2 哪些 IR 会显式产生或携带 strided 布局？

最直接的情况是 MemRef 类型本身显式声明布局，例如函数参数/返回值类型、分配结果类型或某个操作的结果类型：

```mlir
func.func @consume(%m: memref<4x4xf32, strided<[4, 1]>>) {
  return
}
```

这表示函数签名要求传入一个具有该形状、元素类型和步长布局的 MemRef。`memref.alloc` 也可以把明确的 MemRef 类型作为结果类型来携带布局信息；不过实际工程里，静态行优先 identity layout 通常直接写 `memref<4x4xf32>`，不必把等价的步长重复写出来。

更常见的是切片/视图操作推导出非默认步长。下面从连续的 `8x8` 矩阵中每隔一行取一行，取前四列：

```mlir
%view = memref.subview %m[0, 0][4, 4][2, 1]
  : memref<8x8xf32> to memref<4x4xf32, strided<[16, 1]>>
```

源 `%m` 的连续布局步长是 `[8,1]`。`subview` 的步进参数是 `[2,1]`，因此结果步长为逐维相乘：`[8*2, 1*1] = [16,1]`。结果逻辑上有 `4x4` 个元素，但相邻逻辑行之间隔着 16 个底层元素，所以它不是紧密连续的 `4x4` 小矩阵。`subview` 不需要复制这些数据；它创建描述原存储区域的视图。官方文档给出了相同的结果类型推导规则：结果 stride 等于源 stride 与 subview stride 的逐维乘积，offset 则由源 offset 加上各维起始位置计算。[MemRef Dialect：`memref.subview`](https://mlir.llvm.org/docs/Dialects/MemRef/#memrefsubview-memrefsubviewop)

其他会携带或推导 strided layout 的常见场景：

- `memref.subview`：切片、按步长采样，产生描述源存储子区域的结果类型。
- `memref.transpose`：交换维度顺序，产生 sizes/strides 重排后的视图。
- `memref.reinterpret_cast`：基于底层存储重新解释 offset、sizes、strides。
- 函数接口或外部 ABI：显式表达调用方传来的 MemRef 布局约束。
- Bufferization 和 Lowering：转换过程可能为新缓冲区或视图构造相应类型。

这些场景里，有的 IR 类型由用户源码直接写出，有的由操作的类型推导或编译变换生成；仅凭 `strided` 出现在文本中，不能断定它一定是手写的。

### 5.3 逗号后还有哪些类型信息？

MemRef 类型中布局是可选项。常见写法可以概括为：

```text
memref<形状 x 元素类型 [, 布局属性] [, memory-space 属性]>
```

- **不写布局**：identity layout，按形状对应的标准维度顺序映射。普通静态行优先矩阵通常省略布局。
- **`strided<[...], offset: ...>`**：用步长列表和可选 offset 表达布局；步长或 offset 未知时可写 `?`，例如 `strided<[?, 1], offset: ?>`。
- **Affine map**：直接用 Affine 映射表达坐标到线性位置，例如二维行优先映射可写成 `affine_map<(d0, d1) -> (d0 * 4 + d1)>`。`strided` 是这种映射的一种简洁形式；官方 Builtin 文档把 strided 和 affine map 都列作内建布局表示。[Builtin Dialect：MemRef layout](https://mlir.llvm.org/docs/Dialects/Builtin/#memreftype)
- **memory space**：布局后还可以附带目标相关的内存空间属性。它说的是存储位于哪类地址空间/内存区域，不是另一种 stride 布局。具体取值依目标与方言而定。
- **其他布局属性**：方言可以定义实现 MemRef layout 接口的自定义属性；使用它的转换需要能处理该布局，不能假设所有自定义布局都能直接当作普通步长数组。

因此，在 `memref<..., strided<[4,1]>>` 中，`strided` 是布局属性的语法；`4` 和 `1` 是每个维度的元素步长。它们不是可随意换成 `identity`、`layout` 等关键字的槽位。常见替代布局写法是省略布局、Affine map 或目标/方言提供的布局属性。

- **Rank** 是维度个数，不是元素个数。`tensor<2x3xf32>` 的 rank 是 2，元素数是 6。
- **静态维度**在类型里写常数；`?` 表示该维大小在运行时确定。
- **元素类型**回答每个位置存放什么类型，不代表形状或布局。
- **布局**描述逻辑坐标如何映射到底层地址。连续行主序常可由 `[4, 1]` 这类步长表示，但 MemRef 可以有其他步长、偏移或布局映射。具体布局属性属于 Builtin 类型表示的一部分。[Builtin Dialect](https://mlir.llvm.org/docs/Dialects/Builtin/)

`index` 是用于索引和维度等整数语义的类型。常量坐标经常写成 `index`；从 MemRef 取得动态大小也返回 `index`。它与 `i32` 不等价：`index` 的位宽和目标平台相关，表达索引用途；需要时使用明确的 cast 转换。

示意：

```mlir
%dim = memref.dim %m, %c0 : memref<?x4xf32>
```

`%dim` 是第 0 维在运行时的大小，类型为 `index`。若维度在类型中已静态确定，编译器通常可以直接利用该静态信息；若为 `?`，则需要运行时值或动态查询。

## 5. 切片、视图与 Tensor 到 MemRef

相似的“取一段区域”在两种表示中的语义不同：

- `tensor.extract_slice` 产生一个张量值；它按 SSA 值语义参与后续计算。
- `memref.subview` 产生一个描述既有内存子区域的视图，通常与原 MemRef 别名，共享底层写入。

不要只看形状相同就认为两者相同，也不要把 tensor 到 memref 的转换理解为改写类型名。Bufferization 必须决定张量值如何映射到内存：何时分配、是否可以复用已有缓冲区、如何处理别名和读写冲突。这个过程会在第 19 章系统展开；本章先掌握这里的语义边界。

## 6. Affine：受限但可分析的索引表达式

Affine Dialect 为规则循环和索引提供受限表达方式，便于编译器分析依赖、循环边界和数据访问。Affine map 中：

- **维度（dimensions）**通常是当前循环的迭代坐标，如 `d0`、`d1`。
- **符号（symbols）**是该区域内不随这些维度变化的值，如循环外确定的上界或步长。
- 维度写在圆括号中，符号写在方括号中。

例如：

```mlir
affine_map<(d0, d1)[s0] -> (d0 + d1, d1 * 4 + s0)>
```

这里的小括号和方括号是**输入列表的分类标记**，不是数学表达式中的分组括号：

- `(d0, d1)` 声明两个维度输入，调用这个 map 时由两个 `index` 类型 SSA 值绑定。
- `[s0]` 声明一个符号输入，同样由一个 `index` 类型 SSA 值绑定。
- `-> (...)` 是输出表达式列表；这里有两个输出。

可以把它读成函数 `f(d0, d1; s0) = (d0+d1, 4*d1+s0)`。例如绑定 `d0=2, d1=3, s0=10`，输出就是 `(5, 22)`。

**Symbol（符号）不等于“常数”**。它表示一个在当前分析区域内可以当作不变参数的量：它对 `d0`、`d1` 这些维度坐标保持不变，但运行时数值未必已知。例如函数参数 `%N` 可能运行时才传入；只要它在相关区域里不随循环迭代坐标变化，就可以作为符号输入。名称来自数学里把函数写成“关于迭代变量、并带有参数”的形式；编译器可以对任意合法参数值推理，而不必提前知道它具体是多少。编译器文档也将 symbol 说明为对所分析区域可视为常量的未知量，并允许把满足规则的 SSA 值绑定到 symbol。[Affine Dialect：Dimensions and Symbols](https://mlir.llvm.org/docs/Dialects/Affine/#dimensions-and-symbols)

例如 `%N` 作为动态循环上界：

```mlir
affine.for %i = 0 to %N {
  // %i 是随本循环迭代改变的维度；%N 是循环期间不变的上界参数。
}
```

概念上，下界/上界的 Affine map 会把 `%i` 一类迭代坐标作为 dimension，把 `%N` 这类循环期间不变的值作为 symbol。常量也能作为 symbol，但不是只有常量才能当 symbol。它也不是“符号变量”那种可在循环中反复赋新值的 mutable 变量；MLIR 的 SSA 值本身不可变，symbol 讨论的是该 SSA 值在这个 Affine 区域内相对于迭代坐标的角色。

合法表达式可以包含常数、维度和符号的加法，以及与常数相乘等仿射形式；`floordiv`、`ceildiv`、`mod` 的除数/模数也受正整数常量等约束。一般的维度变量相乘（如 `d0 * d1`）或除以运行时变量不属于该受限形式。[Affine Dialect](https://mlir.llvm.org/docs/Dialects/Affine/)

二维访问 `A[i, j]` 可由两个迭代坐标直接表示；转置访问 `A[j, i]` 则交换映射结果。Affine 不是“所有整数表达式的另一种写法”，它用限制换取静态可分析性。遇到不规则或数据依赖索引时，可能需要普通 `index` 运算与其他控制/数据表示，而不能硬塞进 Affine。

## 7. 分析真实 IR 时的顺序

拿到一段代码后，可以按下面顺序追踪：

1. 找类型：`tensor` 还是 `memref`？rank、静态/动态维度、元素类型和布局分别是什么？
2. 找来源：值由函数参数、常量、`tensor.empty`、`memref.alloc`，还是某个切片/视图操作产生？
3. 找访问：Tensor 看 `extract` / `insert` 的结果链；MemRef 看 `load` / `store` 的索引和别名关系。
4. 找形状：哪些维度静态已知，哪些用 `?`，哪些由 `dim` 获得？索引值的类型是什么？
5. 找生命周期：分配在哪里、何时释放、视图是否还引用原存储？
6. 找映射：若使用 Affine，识别维度与符号，并检查表达式是否符合受限形式。
7. 分开判断验证层次：解析/验证通过只说明相应 IR 约束被接受，不代表所有动态索引都已证明安全，也不代表程序已真实执行或性能良好。

## 8. 常见误解

| 误解 | 正确理解 |
| --- | --- |
| `tensor.insert` 就是原地写数组 | 它产生新的 Tensor SSA 结果；优化后物理复制可以消失 |
| `memref` 就是裸指针 | 它带有形状与布局等信息，表示一段可索引存储 |
| 类型里有 `?` 就没有形状信息 | rank、已知维度和元素类型仍明确，只有标记维度的 extent 动态 |
| 两个值 shape 一样就能互换 | Tensor 值、MemRef 存储及其别名/生命周期语义不同 |
| Affine 只不过是普通整数算术 | 它刻意限制表达式，以便进行规则静态分析 |
| verifier 通过代表访存一定安全 | verifier 检查已实现且可判定的 IR 约束，不等于动态边界证明或数值执行 |

## 本讲完成标准

- 能读出 Tensor/MemRef 类型的 rank、维度、元素类型和已给出的布局信息。
- 能解释 Tensor 的新值语义与 MemRef 的可变存储语义。
- 能沿 SSA use-def 链追踪 `insert` 的新结果，并区分 `subview` 的共享存储。
- 能解释动态维度、`index` 与维度查询的关系。
- 能识别 Affine map 中的维度、符号和基本合法性边界。
- 能把解析验证、Pass 变换、真实执行和性能测量分开陈述。

## 后续练习方向（本讲不要求现在作答）

练习将依照 README 第 08 章：先追踪 `tensor<2xi32>` 中替换元素前后的两个读取值；再追踪长度为 2 的 MemRef 初始化、写入、读取和释放；最后用二维循环对照 Affine 索引与一般索引表达式。工具验证和数值执行会分别标明，避免把语义推演误报为运行结果。
