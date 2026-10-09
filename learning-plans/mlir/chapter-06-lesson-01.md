# 第 06 章讲解：基础 Dialect、类型、属性与符号

本讲先搭建整章知识地图，再学习基础函数与整数操作。练习留在讲解之后集中完成。

## 1. 读 MLIR 操作时的五个问题

看到一条操作，不要只认操作名。依次问：

1. 它属于哪个 Dialect？
2. 输入 Operand 和输出 Result 是哪些 SSA 值？
3. 这些值分别是什么 Type？
4. 有没有决定操作语义的 Attribute 或 Property？
5. 它引用的是 SSA 值，还是符号表中的 Symbol？

可以把一条 IR 看成“操作语义 + 值之间的数据流 + 类型约束 + 静态配置”。MLIR 的操作由 Dialect 提供具体语义；同样的文本形状，换一个 Dialect 或操作名，语义也可能不同。

## 2. 三个常见 Dialect 的分工

| Dialect | 本章常见内容 | 阅读重点 |
| --- | --- | --- |
| `builtin` | `module`、通用 Type/Attribute | 提供 IR 容器与通用表示基础 |
| `func` | `func.func`、`func.call`、`return` | 描述函数、参数、返回和直接调用 |
| `arith` | 常量、整数/浮点算术、比较与转换 | 描述数值运算；predicate/转换操作决定具体语义 |

前缀帮助定位语义来源：`arith.addi` 是 `arith` Dialect 的整数加法；`func.call` 是 `func` Dialect 的调用操作。Dialect 不只是命名空间，也定义操作的约束、类型规则和行为。

## 3. Type、Attribute、Property 与 SSA Value

### Type：回答“这个值是什么类型”

每个 SSA Value 都有 Type。函数参数、操作结果、Block 参数都一样。例如 `%x: i32` 中，`%x` 是值，`i32` 是它的 Type。常见类型包括整数 `i32`、浮点 `f32`、函数类型，以及用于索引的 `index`。

`index` 用于描述维度和索引等概念，其位宽与目标机器相关；不要把它等同于固定宽度的 `i32`。值的类型由具体 Dialect 操作约束，例如整数算术通常要求输入和结果类型匹配。

### Attribute：回答“操作携带了什么静态信息”

Attribute 是编译期 IR 中的常量数据，不是独立的 SSA 值。它常用于不能由运行时输入决定的操作参数，例如常量值或比较谓词：

```mlir
%one = arith.constant 1 : i32
%less = arith.cmpi slt, %lhs, %rhs : i32
```

在第一行，`1` 是常量 Attribute，`%one` 才是操作产生的 SSA Value。在第二行，`slt` 指定 signed less-than，是比较操作的静态谓词；`%lhs` 和 `%rhs` 是运行时可能变化的 Operand。

### Property：操作对象上的结构化数据

MLIR 的 Operation 还可存储 Properties。它们是 Operation 自身的属性数据成员；与传统 Attribute 字典在表示和存储方式上不同。入门阅读时先能认出三类东西即可：Value 有 Type；操作可带 Attribute；某些操作还定义 Properties。不要把 Property 当作 Operand 或 SSA Value。

### Location：来源位置

Location 描述 IR 节点的来源位置，常用于诊断和追踪。它不是普通数据流，也不一定出现在默认文本打印中。

## 4. 函数、符号与直接调用

```mlir
module {
  func.func @inc(%x: i32) -> i32 {
    %one = arith.constant 1 : i32
    %result = arith.addi %x, %one : i32
    return %result : i32
  }

  func.func @caller(%x: i32) -> i32 {
    %result = func.call @inc(%x) : (i32) -> i32
    return %result : i32
  }
}
```

- `func.func @inc` 定义名为 `inc` 的函数 Symbol。函数名处于相应 SymbolTable 的命名空间中。
- `%x` 是函数入口 Block 参数，是 SSA Value；函数参数不是 Symbol。
- `func.call @inc(%x)` 用 `@inc` 作为 callee 的 SymbolRef，用 `%x` 作为实际调用参数。`@inc` 不是 Operand，也不是 SSA Value。
- `%result` 是调用操作产生的 SSA Result。直接调用的参数和结果类型必须匹配被调函数签名。
- `return` 把函数体中的 SSA Value 交给函数调用者，返回值数量和类型要符合函数签名。

如果将 `@inc` 改成 `@missing`，问题不是“找不到某个 SSA 值”，而是符号解析无法在相应符号作用域中解析被调用函数。Symbol 使用符号表按名称查找；SSA 使用值的定义、作用域和支配规则。两种引用机制解决不同问题。

函数 Symbol 的命名、可见性和所在 SymbolTable 决定其它位置能否引用它。入门阶段先记：同一符号表内名字唯一；`func.call` 的 `@callee` 要能解析到符合签名的函数。

## 5. 整数类型与 signed/unsigned 语义

MLIR builtin 整数类型可表达 signless `iN`、signed `siN`、unsigned `uiN`。本章的 `i32` 练习使用 signless 类型：类型说明位宽，不自行指定有符号或无符号解释。具体操作可以选择解释方式。

`arith.cmpi` 通过谓词选择比较语义：

```mlir
%signed = arith.cmpi slt, %a, %b : i32
%unsigned = arith.cmpi ult, %a, %b : i32
```

若 `%a` 是 `-1 : i32`，其位模式为 `0xFFFFFFFF`：按有符号二补数解释为 `-1`；按无符号解释为 `4294967295`。因此与 `1 : i32` 比较时，`slt` 为真，`ult` 为假。位模式相同，谓词改变解释规则。

不要把所有整数操作都说成“有符号”或“无符号”。例如二进制加法主要按固定宽度位向量运算；除法、扩展、比较等操作则需要选定解释。要读具体操作定义，而不是只看 `i32`。

## 6. 常量、算术、比较与转换

- `arith.constant` 从 Attribute 构造 SSA Result。
- `arith.addi`、`arith.muli` 对整数值计算；它们的 Operand 和 Result 受操作定义中的类型约束。
- `arith.cmpi` 比较整数值，产生 `i1`（或向量/tensor 形式的布尔结果）；predicate 选定等值、signed 顺序或 unsigned 顺序比较。
- 转换操作显式改变类型或解释方式。扩宽、截断、整数转浮点等是不同语义，不能只把文本中的类型标签替换掉。

读算术 IR 时，按“常量输入 → 运算 → 比较/转换 → 返回”追踪 SSA 值，再分别确认各操作的类型和静态属性。

## 7. 逐行阅读的完整方法

1. 先认 Dialect/Operation，查清该操作语义。
2. 标出每个 Operand 的 SSA 定义来源和 Type。
3. 标出 Result、Result Type，并追踪它的后续使用。
4. 找出 Attribute/Property：哪些是静态配置，哪些是数据值。
5. 对 `@name` 检查符号定义、符号表作用域和函数签名；不要把它和 `%value` 混淆。
6. 最后检查约束：返回签名、调用签名、算术类型、比较谓词和类型转换。

解析/验证通过只能说明工具接受 IR 语法和已实现的约束；它不等于已执行得到数值。后续已用 LLVM 22.1.8 对本讲 inc/caller 与 signed/unsigned 比较 IR 运行 `mlir-opt --canonicalize`，验证器接受并将比较折叠为 `true`/`false`；未执行函数本身。

## 本讲资料

- [MLIR Language Reference](https://mlir.llvm.org/docs/LangRef/)
- [`func` Dialect](https://mlir.llvm.org/docs/Dialects/Func/)
- [`arith` Dialect](https://mlir.llvm.org/docs/Dialects/ArithOps/)
- [Builtin Dialect](https://mlir.llvm.org/docs/Dialects/Builtin/)
- [Symbols and Symbol Tables](https://mlir.llvm.org/docs/SymbolsAndSymbolTables/)
