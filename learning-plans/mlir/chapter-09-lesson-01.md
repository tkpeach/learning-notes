# 第 09 章讲义：用 C++ 创建、遍历与修改 IR

> 目标是把 MLIR 文本背后的 C++ 对象关系弄清楚：谁拥有 IR 节点、`Value` 指向什么、Dialect 如何进入 Context、Builder 在哪里插入 Operation，以及遍历和改写时哪些句柄会失效。本讲先系统讲解，集中练习随后进行。

## 1. 学习路线

1. MLIR 的内存结构：Operation、Region、Block、Value。
2. Context、DialectRegistry、Dialect、Location、Type 与 Attribute。
3. 解析模块和持有根 Operation 的生命周期。
4. 通用 Operation 与类型化 Op wrapper，`isa` / `dyn_cast`。
5. OpBuilder、插入点和构造顺序。
6. walk、use-def、替换和删除的约束。
7. 何时直接遍历，何时把变换交给 PatternRewriter。

本章固定参考本机 LLVM/MLIR 22.1.8。核心概念与官方 [理解 IR 结构教程](https://mlir.llvm.org/docs/Tutorials/UnderstandingTheIRStructure/)、[Language Reference](https://mlir.llvm.org/docs/LangRef/) 一致；具体头文件与构建 API 以本机安装版本为准。

## 2. 先建立对象图：树状所有权，SSA 值连接

MLIR IR 可分成两种关系：**容器的树状嵌套**与**SSA 数据流连接**。

```text
ModuleOp
└── Operation: func.func
    └── Region
        └── Block (参数也是 Block 的一部分)
            ├── Operation: arith.constant
            │   └── Result Value
            ├── Operation: arith.addi
            │   ├── Operand Values ───────┐
            │   └── Result Value          │
            └── Operation: func.return    │
                └── Operand Value ◀───────┘
```

- **Operation** 是 IR 的基本节点。它有名字、位置、operands、零个或多个 results、attributes、regions，某些控制流操作还引用 successor blocks。
- **Region** 是一组 Block 的容器。Region 本身没有 SSA 类型。
- **Block** 是有序 Operation 列表，也可有 Block arguments。控制流中的分支把值传给目标 Block arguments。
- **Value** 表示一个 SSA 值。它要么由某个 Operation result 定义，要么是 Block argument。Value 不是复制出来的值数据，而是 IR 中该定义的句柄。
- **类型化 Op**（如 `arith::AddIOp`、`func::FuncOp`）是围绕底层 Operation 的轻量类型化访问接口；底层仍是 Operation 节点。

LangRef 将 Operation/Value 描述为图结构：Operation 与 Block 组织结构，Value 表示定义及其使用之间的数据流边。[MLIR Language Reference：High Level Structure](https://mlir.llvm.org/docs/LangRef/#high-level-structure)

可以记成：

> Region/Block/Operation 决定节点放在哪里；Value 决定结果如何流向其他 Operation。

## 3. 一个最小例子如何映射到 C++ 对象

```mlir
func.func @difference(%lhs: i32, %rhs: i32) -> i32 {
  %delta = arith.subi %lhs, %rhs : i32
  return %delta : i32
}
```

对应关系：

| 文本 | IR 对象/关系 |
| --- | --- |
| `func.func @difference` | 一个 `func::FuncOp`（也是 Operation），内部含函数体 Region |
| 函数体 `{ ... }` | 函数 Region 的 entry Block |
| `%lhs: i32`、`%rhs: i32` | entry Block 的两个 Block arguments，类型都是 `i32` |
| `%delta = arith.subi` | `arith::SubIOp`；两个 Operand 分别引用 `%lhs` 和 `%rhs`；它定义 `%delta` |
| `return %delta` | `func::ReturnOp` 的 Operand 引用 `%delta` |

同一个 Value 可以被多个 Operation 使用。Operation 结果和 Block 参数都属于 SSA 定义；不要把 `%arg` 当作 C++ 局部变量，也不要把 Operation 的 Operand 当作其所有权。

## 4. MLIRContext、DialectRegistry 与类型数据

### MLIRContext

`MLIRContext` 是 IR 构造和解析的重要上下文。Dialect 会在 Context 中注册/加载；许多 Type、Attribute、Location 的底层存储由 Context 管理并可做唯一化。因此，常用的 Type/Attribute C++ 对象多数是轻量句柄，不应当自行 `delete`。

生命周期原则：Context 必须比依赖它的 IR 节点、Type、Attribute 等活得久。常见程序顺序是先创建 Context，再解析/构造模块，最后销毁模块和 Context。

### DialectRegistry 与加载

Dialect 定义一组 Operation、Type、Attribute、Interface 等规则。Registry 提供 Dialect 的注册信息；Context 可从 Registry 加载 Dialect。解析或构造 `arith.addi`、`func.func` 等已注册操作时，相关 Dialect 必须可用。程序入口必须考虑工具实际会处理哪些 Dialect；不要依赖“机器上的 mlir-opt 已经注册”来推断自己的 C++ 程序也会注册它们。

通常会采用如下流程（这是流程示意，不是完整可编译工程）：

```cpp
mlir::DialectRegistry registry;
// 将程序需要的 Builtin、func、arith 等 Dialect 加入 registry。
mlir::MLIRContext context(registry);
// 按需加载；若要解析所有注册的 Dialect，也可使用相应的全加载 API。
```

实际注册类型、头文件和加载 API 要与 LLVM/MLIR 版本匹配。后续 C++ 练习会给出完整工程骨架和依赖，不让你从空白猜 CMake 链接项。

### Location、Type、Attribute

- **Location** 给 Operation 标注来源位置。示例可用 `UnknownLoc`，真实前端通常保留文件/行列或由哪个源代码表达式产生的信息。
- **Type** 描述 SSA 值的类型，如 `i32`、`index`、`memref<...>`。
- **Attribute** 是附着在 Operation 或类型上的静态元数据/参数，例如整数常量值、符号名或字典属性。

Type、Attribute、Location 通常是与 Context 关联的不可变句柄；它们不是 Operation 的 SSA results。

## 5. 解析结果与所有权：谁负责销毁？

解析 API 的结果通常用 `OwningOpRef<ModuleOp>` 持有。它的意义类似一个 RAII 所有者：作用域结束时释放它拥有的根 Operation。Module 根节点拥有其嵌套 IR 树；遍历时取到的 `Operation *`、`Block *`、`Region *`、`Value` 或类型化 Op wrapper 通常只是**借用句柄**，不能因为拿到指针就认为自己获得了所有权。

| 对象/句柄 | 通常由谁管理 | 什么时候要特别小心 |
| --- | --- | --- |
| `OwningOpRef<ModuleOp>` | C++ RAII 所有者 | 所有者销毁后，模块树中的句柄均失效 |
| 嵌套 Operation | 父 Block/父 Operation 的 IR 树 | erase 或父节点销毁后，指向它的 `Operation *` / Op wrapper 失效 |
| Block 与 Region | 包含它们的 Operation | 所有者 Operation 被销毁、Region/Block 被移除后失效 |
| Operation result / Block argument 的 `Value` | 定义它的 Operation / Block | 定义被删除、替换或对应结构被销毁时需重新检查句柄有效性 |
| Type / Attribute / Location | 通常由关联 Context 管理底层存储 | Context 销毁后不能继续使用关联句柄 |
| OpBuilder | 通常由调用代码管理 | builder 不拥有插入点中的 Block；Block 被销毁/改动后应重设插入点 |

`Operation *` 是非拥有原始指针。`Value` 与类型化 Op 对象看着像 C++ 值对象，也不代表它们拷贝了 IR 或延长了底层对象寿命。官方 `OwningOpRef` 文档明确其用途是 RAII 持有 Operation，并说明析构时会销毁所持 Operation。[OwningOpRef](https://mlir.llvm.org/doxygen/classmlir_1_1OwningOpRef.html)

## 6. 通用 Operation 与类型化 Op：检查再访问

若遍历拿到的是通用 `Operation *`，可先判断它是否为特定操作，再取类型化包装：

```cpp
if (auto add = llvm::dyn_cast<mlir::arith::AddIOp>(op)) {
  // add 是类型化 wrapper，可通过其访问器读取 lhs/rhs/result 等信息。
}
```

- `isa<T>(x)`：回答“是不是 T”，只给布尔判断。
- `dyn_cast<T>(x)`：尝试得到类型化视图；不匹配则得到空/失败结果。
- `cast<T>(x)`：断言/假设一定匹配；不满足时会触发断言或其他失败，不适合未检查的输入。
- MLIR 常结合 LLVM 支持库使用这些转换；具体命名空间/API 按类型和版本而定。

这些 `isa` / `dyn_cast` / `cast` **不是 Dialect，也不是 Builtin 操作**。它们是 LLVM 支持库里的通用 C++ 类型转换模板，定义在 `llvm/Support/Casting.h`；MLIR 的 `mlir/Support/LLVM.h` 会把它们引入 `mlir` 命名空间，因此代码中常见 `isa<T>(x)`，也可以明确写 `llvm::isa<T>(x)`。MLIR Operation wrapper 等类型提供了配合这套机制使用的类型判别接口。

调用时，`T` 才是要检查的 MLIR 类型。例如 `T = arith::AddIOp` 指向 Arith Dialect 的具体 Op wrapper；转换机制本身仍是 LLVM 的通用 C++ 工具，不属于 Arith Dialect。类型化 Op wrapper 不是新的 IR 节点，也不是所有者。对 wrapper 取出的 Operand/Result 仍是 Value 句柄；读取前要知道操作类型约束，改写时要保证 Operation 仍合法。

## 7. OpBuilder 与插入点：创建操作就要知道“放在哪里”

`OpBuilder` 的核心状态包括 Context 和当前插入点。`builder.create<SomeOp>(...)` 不只是“构造一个 C++ 对象”：它按该操作的 builder 规则创建 IR Operation，并插入当前指定的位置。

常见步骤：

1. 创建 Context、加载所需 Dialect。
2. 创建 Module 或取得解析后的 Module。
3. 取得函数体的 Region/Block，或新建函数及 entry Block。
4. 将 Builder 插入点设在目标 Block 的开头、结尾或某个 Operation 前后。
5. 用 Type、Location、Operands、Attributes 构造 Operation；结果 Value 可供后续 Operation 使用。
6. 构造 terminator（如 `func.return`），再验证并打印模块。

示意代码：

```cpp
builder.setInsertionPointToStart(block);
auto delta = builder.create<mlir::arith::SubIOp>(loc, lhs, rhs);
builder.create<mlir::func::ReturnOp>(loc, delta);
```

这里 `delta` 是类型化 Op wrapper；它在相应 Operation 仍存在时可提供访问接口。该 Operation 的两个 Operand 引用函数 Block arguments，结果 Value 再被 `func.return` 使用。这个例子用于说明 Builder 的创建和插入流程；后续练习会换成不同的输入/操作组合。

**插入点不是语义装饰。**插入在错误 Block、terminator 之后，或依赖尚未定义的 Value，可能让 IR 无效。删除/搬移 Block 或 Operation 后，旧插入点也可能不再有效；应重新设定 Builder 插入点。Builder 的 create API 依据当前位置创建并插入 Operation。[OpBuilder API](https://mlir.llvm.org/doxygen/classmlir_1_1OpBuilder.html)

## 8. walk 与 use-def：读取 IR 的两条线索

### 结构遍历

从 Module walk 会访问它所包含的 Operation；根据 walk 范围、遍历顺序和回调形式，可选择只统计某类操作或进入嵌套 Region。练习一会对 `arith.addi` 和 `arith.muli` 计数。不要把 Block、Region 当 Operation 数入操作计数；一个 `func.return` 也是 Operation，但若题目只数算术指令，就用类型筛选。

### 数据流追踪

- `op->getOperand(i)` 取得第 `i` 个 Operand 对应的 Value。
- `op->getResult(i)` 取得 Operation 定义的第 `i` 个结果 Value。
- `block.getArgument(i)` 取得 Block 参数。
- 从一个 Value 可以查看定义者（如果它是 Operation result）和 uses；Block argument 没有普通的 defining Operation。

要回答“这个 SSA 值从哪里来、被谁使用”，沿 def-use/use-def 关系查；要回答“它嵌套在哪个函数/Region”，沿父级结构查。这两种遍历目的不同。

## 9. 修改与删除：维持 use-def 和容器不变量

删除一个 Operation 前，至少检查：

1. 它的结果是否仍有 uses？若有，直接删除会让 use-def 链和 IR 无效。
2. 若要替换结果，替换值的类型是否兼容？是否真的支配所有使用位置？
3. 被删 Operation 是否是 Block 的 terminator，或仍被控制流/Region 结构引用？
4. 当前 walk/迭代器或 Builder 插入点是否依赖这个 Operation/Block？

对于已确认可直接替换的结果，`replaceAllUsesWith` 一类接口可将所有使用改为新 Value；之后只有在原 Operation 无需保留、且其所有结果都不再被使用时，才可以安全 erase。通用 C++ 改写很容易遗漏类型、支配关系、副作用、terminator 或遍历迭代器问题，因此变换逻辑应倾向封装为合法 Rewrite Pattern。

**遍历时边走边删尤其危险。**手写遍历如果删除当前节点，当前节点的 next/parent 关系和迭代器可能失效；有时必须保存下一节点，但这不能自动解决 SSA 使用和所有 IR 语义问题。先用只读 walk 完成统计；修改/删除时根据设计使用安全的重写流程。

## 10. PatternRewriter 的边界

### 它解决什么问题？

当你在编写编译变换时，常见任务不是“无条件创建一个 Operation”，而是：**找到符合某个结构的 Operation，在满足条件时把它改写成另一种 IR**。例如：

```mlir
%zero = arith.constant 0 : i32
%sum = arith.addi %x, %zero : i32
func.return %sum : i32
```

如果确认第二个 operand 确实是整数 0，那么 `%sum` 的值等于 `%x`。期望结果是让 return 直接使用 `%x`，并移除不再需要的 `arith.addi`：

```mlir
func.return %x : i32
```

这里要做的不只是删一行文本：原 Operation 可能有多个 SSA uses；删掉它前需要把这些 uses 改接到替代值；rewrite driver 也需要知道哪些 IR 节点被新增、替换、修改或删除，以便继续处理受影响的操作。`PatternRewriter` 是 Pattern 执行时使用的改写接口，它把这些修改通知给驱动器。

### 三个角色要分开

| 角色 | 做什么 | 类比 |
| --- | --- | --- |
| **Rewrite Pattern** | 描述“匹配什么 Operation、条件是什么、怎么改写” | 一条变换规则 |
| **PatternRewriter** | 提供创建、替换、删除、原地修改等接口，并向驱动器报告变化 | 受跟踪的修改工具 |
| **Pattern driver** | 遍历 IR、挑选并应用规则；决定是否重访变化节点、何时停止 | 规则执行引擎 |

Pattern 通常实现 `matchAndRewrite(root, rewriter)`：

1. 检查 root 是否符合模式及额外条件。
2. 若不匹配，返回 `failure()`，此时不能已经改动 IR。
3. 若匹配，使用传入的 `rewriter` 修改 IR。
4. 改写完成后返回 `success()`；必须“有修改才 success”，不能无变化却报告成功。

概念伪代码（`isKnownZero` 是省略实现的示意 helper，不是可直接编译的完整 Pattern）：

```cpp
LogicalResult matchAndRewrite(arith::AddIOp op,
                              PatternRewriter &rewriter) const {
  if (!isKnownZero(op.getRhs()))
    return failure();

  rewriter.replaceOp(op, op.getLhs());
  return success();
}
```

`replaceOp(op, replacementValue)` 会把 root Operation 的结果替换为给定 Value，并移除 root。此例假定已正确证明 RHS 为 0，且替换值类型兼容。**PatternRewriter 不负责证明代数变换正确**；变换作者仍须证明语义等价，正确处理类型、副作用、溢出规则和使用关系。

### 为什么不直接 `op.erase()` 或随手改 operand？

Pattern driver 可能维护 worklist、遍历状态或其他依赖 IR 结构的状态。Pattern 内若绕开 rewriter 直接创建/删除/修改 Operation，driver 可能不知道 IR 已变化，后续处理就会漏掉新节点或继续使用失效状态。因此 MLIR 要求 Pattern 中的所有 IR 修改（包括创建）都经由传入的 `PatternRewriter`；不匹配时不能先改一部分再返回失败。[Pattern Rewriter：Pattern restrictions](https://mlir.llvm.org/docs/PatternRewriter/#matchandrewrite-implementation)

常见接口包括：

- `rewriter.create<OpTy>(...)`：创建并插入新 Operation。
- `rewriter.replaceOp(...)` / `replaceOpWithNewOp(...)`：用 Value 或新 Operation 替换原 Operation。
- `rewriter.eraseOp(...)`：删除无结果或所有结果都无 uses 的 Operation。
- `rewriter.modifyOpInPlace(...)`：通过通知框架对 Operation 做原地修改。

这些方法处理的是“如何让 IR 结构变化被正确报告和应用”的机制，不是安全性/等价性的自动证明。

### 它和 OpBuilder 的关系

`OpBuilder` 是一般的 IR 构造工具：你给它类型、Location、operands 和插入点，它创建 Operation。它适合初始化 IR、生成函数体等常规构造。

`PatternRewriter` 继承 `OpBuilder`，因此也能创建 Operation；它另外提供 rewrite 专用的替换、删除、原地修改和驱动通知接口。简单记忆：

> 造初始 IR 通常用 OpBuilder；在 Pattern 里匹配并改变已有 IR，使用传入的 PatternRewriter。

PatternRewriter 不是“另一个 Dialect”，也不是一个 pass。它是 Pattern 重写框架中的 API/对象。Pattern 集合要交给具体 driver 执行。[MLIR Pattern Rewriting](https://mlir.llvm.org/docs/PatternRewriter/)

### Driver 为什么重要？

定义 Pattern 不代表它会自动运行。需要把 Pattern 放进 `RewritePatternSet`，然后交给 driver。不同 driver 有不同遍历和重访策略：Greedy Pattern Rewrite Driver 会维护 worklist，并重复应用规则，直到达到不动点或迭代上限；它也是 canonicalization 使用的 driver。并非所有 driver 都会重新访问新建/替换的节点，所以要根据变换需求选择执行方式。[Pattern Application 与 Greedy Driver](https://mlir.llvm.org/docs/PatternRewriter/#pattern-application)

例如，给 `mlir-opt` 的 `--canonicalize` 会运行框架中已注册的 canonicalization/fold 规则；它不会凭空推导任意 C++ 变换。自定义 Pattern 则需要由自定义 Pass 或其他 driver 收集并应用。

### 什么时候不用 PatternRewriter？

- **只读统计/检查**：用 walk，不需要 PatternRewriter。
- **从空白创建 IR**：用 OpBuilder。
- **基于局部结构匹配和替换**：用 Rewrite Pattern + PatternRewriter。
- **全局分析或多阶段转换**：在 Pass 中组织分析/控制流程，需要局部改写时再调用 Pattern 机制；不要强行把整项工作塞成一个 pattern。

第 11 章会真正实现 Pattern，并逐步连接 `RewritePatternSet`、driver、fold 和 canonicalization。本章先记住：Pattern 描述规则，PatternRewriter 执行并报告修改，driver 负责调度规则；这三者不可混为一谈。

## 11. 本章的结论分层

| 检查 | 能回答什么 | 不能自动回答什么 |
| --- | --- | --- |
| C++ 构建/链接 | 代码与选定版本的 MLIR API、库能否构建链接 | 生成的 IR 是否满足操作语义 |
| `verify(module)` | 已实现的 Operation、类型、Region 等 verifier 约束是否满足 | 数值执行结果、所有动态输入行为都正确 |
| 打印并重新解析 | 文本序列化与解析是否往返成功 | 自定义变换是否语义等价 |
| 真实运行 | 特定输入下程序实际得到什么结果 | 所有输入正确或性能提升 |

## 本讲完成标准

- 能画出 `Module → Operation → Region → Block → Operation` 的容器层次，并说明 Value 不属于这条纯容器树。
- 能区分 Operation result 和 Block argument 两种 Value 定义。
- 能指出 Module 的所有者、通用指针/Value/wrapper 的非拥有属性，以及删除/Context 销毁带来的失效。
- 能说明 DialectRegistry、MLIRContext、Dialect、Type/Attribute 的基本关系。
- 能解释 OpBuilder 为什么需要插入点，以及 walk 时删除节点的风险。
- 能在修改前检查 uses、类型、支配和 terminator 约束；知道模式化变换应使用 PatternRewriter。

## 下一步练习

练习会依 README 第 09 章安排：先统计两条 `arith.addi` 和一条 `arith.muli`；再从完整 C++ 工程骨架构造 `i32` 参数加一的函数，验证并打印。答案表只要求填写关键代码位置和检查结果；工程构建若需 CMake，将提供与 LLVM/MLIR 22.1.8 匹配的完整文件和命令。
