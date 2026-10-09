# 第 07 章讲义：SCF、CF 与控制流

本讲先系统理解结构化和显式控制流，再集中练习。核心问题是：程序下一步会执行哪里，以及跨路径/跨迭代的 SSA 值如何传递。

## 1. 控制流的两种表示

控制流决定操作的执行路径。MLIR 中常见两层表示：

| 表示 | Dialect | 主要结构 | 阅读重点 |
| --- | --- | --- | --- |
| 结构化控制流 | `scf` | `scf.if`、`scf.for`、`scf.while` 等 Operation 与 Region | 分支/循环的形状和边界直接可见 |
| 显式控制流图 | `cf` | Block、跳转终结操作、控制流边 | 每条跳转路径、目标 Block 参数都显式列出 |

典型 lowering 会把 SCF 转成 CF，再继续降到目标相关 IR。转换后计算含义仍需保留，但显式 Region 结构会变成基本块及分支边。[SCF Dialect](https://mlir.llvm.org/docs/Dialects/SCFDialect/)、[SCF-to-CF pass](https://mlir.llvm.org/docs/Passes/#convert-scf-to-cf)

## 2. 条件分支：`scf.if`

```mlir
%chosen = scf.if %cond -> (i32) {
  %a = arith.constant 7 : i32
  scf.yield %a : i32
} else {
  %b = arith.constant 9 : i32
  scf.yield %b : i32
}
```

- `%cond` 是 `i1` 条件。运行时为真走 then Region，否则走 else Region。
- `scf.if` 可以产生零个或多个结果。这里产生一个 `i32` 结果 `%chosen`。
- 每个分支的局部值通过 `scf.yield` 交给父 `scf.if`；外部只使用 `%chosen`。
- 有结果时，then 和 else 都必须提供结果，且数量、类型与父操作的结果匹配。
- 无结果的 `scf.if` 可以不写 `else`；若有结果，就需要完整的两个分支。

这描述的是 IR 结构和语义，不代表验证器实际执行了两条分支。

## 3. 循环：`scf.for`

`scf.for` 适合已知上下界和步长的循环。标准形式的区间是**左闭右开**：包含 lower bound，不包含 upper bound。`0` 到 `5`、步长 `1` 的归纳变量依次为 `0,1,2,3,4`，总计五次。

```mlir
%sum = scf.for %iv = %c0 to %c5 step %c1
    iter_args(%sum_iter = %sum_init) -> (i32) {
  %iv_i32 = arith.index_cast %iv : index to i32
  %sum_next = arith.addi %sum_iter, %iv_i32 : i32
  scf.yield %sum_next : i32
}
```

此例中：

- `%iv` 是循环体 Region 的 Block 参数，表示当前迭代值。
- `%sum_init` 是循环开始前的初始累加值。
- `iter_args(%sum_iter = %sum_init)` 将循环携带变量的初始值绑定到循环体参数 `%sum_iter`。
- 每轮的 `scf.yield %sum_next` 把下轮的 `%sum_iter` 值传下去；最后一轮的 yield 成为整个 `scf.for` 的结果 `%sum`。
- 循环携带值每轮的静态 Type 不变；初值、Region 参数、yield 值和循环结果必须匹配。

示例选择 `index` 作为边界和归纳变量类型，因为它用于索引且宽度依目标而定。示例将 `%iv` 转为 `i32` 后参与整数累加。转换必须显式写出，不能把 `%iv` 当成 `i32` 直接相加。

### 手工追踪 0 到 4 的累加

若 `%sum_init = 0`，每轮开始时的 `%sum_iter` 与本轮结束后的 `%sum_next` 为：

| `%iv` | 进入循环体的 `%sum_iter` | `scf.yield` 的 `%sum_next` |
| ---: | ---: | ---: |
| 0 | 0 | 0 |
| 1 | 0 | 1 |
| 2 | 1 | 3 |
| 3 | 3 | 6 |
| 4 | 6 | 10 |

所以在该数学例子中循环最终结果是 `10`。这张表是手工推演，不等于运行程序或实测性能。

### 多个 `iter_args`

例如在同一个循环里同时累计和与积：

```mlir
%sum, %product = scf.for %iv = %c0 to %c5 step %c1
    iter_args(%sum_iter = %sum_init, %product_iter = %product_init)
    -> (i32, i32) {
  %iv_i32 = arith.index_cast %iv : index to i32

  %sum_next = arith.addi %sum_iter, %iv_i32 : i32
  %factor = arith.addi %iv_i32, %one_i32 : i32
  %product_next = arith.muli %product_iter, %factor : i32

  scf.yield %sum_next, %product_next : i32, i32
}
```

假设 `%sum_init = 0`、`%product_init = 1`，且 `%c0`、`%c5`、`%c1` 是 `index` 类型的 0、5、1，`%one_i32` 是 `i32` 常量 1。循环变量取 0 到 4：sum 累计 `0+1+2+3+4=10`；product 累计 `(0+1)(1+1)(2+1)(3+1)(4+1)=120`。因此结果按顺序对应 `%sum = 10`、`%product = 120`。

可把多个 `iter_args` 看成多组并行的“初始状态 → 当前状态 → 下一状态 → 最终结果”：

| 顺序 | 循环外初始值 | 循环体当前值 | 本轮 yield 的下一值 | 循环最终 Result |
| ---: | --- | --- | --- | --- |
| 1 | `%sum_init` | `%sum_iter` | `%sum_next` | `%sum` |
| 2 | `%product_init` | `%product_iter` | `%product_next` | `%product` |

各列按位置一一对应。`iter_args` 声明两个状态，结果类型也有两个，`scf.yield` 必须按相同顺序传出两个值；此例中每一项的初值、循环体参数、yield 值和结果都必须是 `i32`。若循环零次执行，循环结果保留初始状态。

### 如何从算法判断哪些变量要成为 `iter_args`

先把算法改写成递推关系，再对应到 IR：

```text
sum_0 = 0
sum_(i+1) = sum_i + i

product_0 = 1
product_(i+1) = product_i * (i + 1)
```

凡是“本轮的新值要成为下一轮的旧值”的状态，都需要循环携带。常见例子是累计和、累计积、运行中的最小/最大值、循环状态、上一项值。

这些通常不需要 `iter_args`：

- 每轮会重新计算且不依赖前一轮结果的临时值，例如 `%iv_i32`、`%factor`。
- 循环过程中保持不变的值，例如循环外的常量或输入；它们可以直接在循环体中使用，不用每轮 yield。
- 归纳变量 `%iv`：它由 `scf.for` 的边界和步长管理，是循环体自带的 Region 参数，不放进 `iter_args`。

分析时可问自己：**下一轮是否需要上一轮更新后的这个值？循环结束后是否需要它的最终值？** 前者决定它是否是循环携带状态；后者决定是否会使用 `scf.for` 对应的 Result。状态即使不在循环后使用，只要下一轮需要它，仍需携带。

### 面对一份已有用户代码的查找流程

不要只搜索 `+=`。按以下顺序看循环体的数据流：

1. **圈定循环与迭代边界**：找出进入循环前的初始状态、循环体、回到下一轮的位置，以及循环退出后继续使用的值。
2. **列出循环体会读写的变量/值**：记录循环体中被读取、被更新、在退出后仍可能使用的内容。
3. **沿回边追踪依赖**：检查某个变量的本轮新值是否会在下一轮被读取。若会，它是 loop-carried state；从首轮初值、循环体当前值、更新值一直追到退出结果。
4. **排除循环自己的归纳量**：`i`、`iv` 这类控制迭代次数的变量通常映射到 `scf.for` 的 `%iv`，由上下界和步长管理，不列入普通 `iter_args`。
5. **排除每轮临时量和循环不变量**：每轮重算的 `temp` 不携带；外部固定的 `limit` 或常量可直接引用，不携带。
6. **检查条件更新和退出使用**：如果只在某分支更新，未更新分支通常把旧状态原样传出；如果循环后要用最终状态，确认它对应 `scf.for` 的 Result。

如果输入已经是 **CF/CFG 形式**，先找到回边和循环头 Block：循环头 Block 参数中，若有参数从 entry/preheader 接收初值，又从循环体回边接收更新值，这个参数通常就是循环携带状态；回边 `cf.br` 的对应 Operand 就是下一轮更新值。归纳变量也可能以 Block 参数表示，但要结合比较、递增和退出条件识别，再决定高层重建时由 `scf.for` 的 `%iv` 表示还是作为普通状态携带。

可用一张表做第一次人工扫描：

| 源码变量 | 循环前初值 | 循环体是否读取 | 循环体是否更新 | 更新值是否流向下一轮 | 退出后是否使用 | 初步归类 |
| --- | --- | --- | --- | --- | --- | --- |
| `i` | `0` | 用作边界/索引 | `i++` | 是 | 通常不作为最终状态 | 归纳变量，映射 `%iv` |
| `sum` | `0` | 是 | `sum += i` | 是 | 可能返回 | `iter_args` |
| `temp` | 无，循环内定义 | 当轮读取 | 每轮重算 | 否 | 否 | 循环体临时值 |
| `limit` | 循环外定义 | 是 | 否 | 不适用 | 可能继续使用 | 循环不变量，直接引用 |

### 从普通源码映射到 `iter_args`

以下是函数体映射片段，省略常量定义，突出变量对应关系；它不是可独立运行的完整模块。

```c
int sum = 0;
for (int i = 0; i < 5; ++i) {
  int temp = 2 * i;
  sum = sum + temp;
}
return sum;
```

分析：`i` 只负责计数，映射为 `%iv`；`temp` 每轮根据当前 `%iv` 重新产生，不需要跨轮传递；`sum` 的初值是 `0`，每轮先读取旧 sum 再产生新 sum，新值要被下一轮读取，退出后还要返回，因此是一个 `iter_args`，并对应一个循环结果。

```mlir
%sum_final = scf.for %iv = %c0 to %c5 step %c1
    iter_args(%sum_iter = %c0_i32) -> (i32) {
  %iv_i32 = arith.index_cast %iv : index to i32
  %temp = arith.muli %iv_i32, %two_i32 : i32
  %sum_next = arith.addi %sum_iter, %temp : i32
  scf.yield %sum_next : i32
}
return %sum_final : i32
```

实际代码还要先确认 `%c0/%c5/%c1` 的 Type 为 `index`，`%c0_i32/%two_i32` 的 Type 为 `i32`。这个映射示意循环状态，不是本地运行过的验证结果。

### 需要留意的边界情况

- **条件更新**：例如只在 `if candidate > best` 时更新 `best`。下一轮仍需 `best`，所以它要携带；`scf.if` 的两个分支分别 yield 新值或旧值，再由 `scf.for` yield。
- **仅在退出后使用**：如果循环末尾算出的值只在退出后使用、不会反馈到下一轮，它不一定是 loop-carried；可以是循环结果，但要看它是否依赖循环执行路径和 IR 结构。
- **内存写入**：`memref` 元素通过内存副作用更新，通常不把整个 memref 当作 `iter_args`；如果更新的是 immutable tensor SSA 值，且新 tensor 要进入下一轮，则可能需要循环携带。
- **零次迭代**：检查循环结果在边界不满足、循环体一次也未执行时应是什么。loop-carried result 会保留其初值，这常能揭露初始化遗漏。
- **死变量**：循环体更新了变量，不代表一定要携带；若它的新值既不反馈到下一轮，也不被循环外观察，优化后可能不需要保留。

## 4. `scf.while` 与循环携带值

`scf.while` 用于条件在循环中持续判断的循环。它有“before”和“after”两个 Region：before Region 计算是否继续，并用 `scf.condition` 选择进入循环体还是结束；after Region 执行循环体，再用 `scf.yield` 把新状态传回 before Region。

可以这样对照：

- `scf.for`：循环边界直接写在 Operation 上，适合计数/范围循环。
- `scf.while`：条件需要在循环过程中计算，适合一般 while/do-while 形状。

两者都通过 Region 参数和结果传递跨迭代状态，不靠给 SSA 名称重复赋值。

## 5. 显式 CFG：Block、边与 `cf` 终结操作

结构化 if 可用 CFG 思路展开成 entry、then、else、join 等 Block。每个 Block 以终结操作结束：

- `cf.br`：无条件跳转到目标 Block。
- `cf.cond_br`：根据 `i1` 条件跳到两个目标之一。
- `func.return`：离开函数并返回值。

MLIR 用**目标 Block 参数**传递控制流合流处的值，语义上承担了传统 SSA 中 PHI 节点的一类作用：

```mlir
func.func @choose(%cond: i1) -> i32 {
  cf.cond_br %cond, ^then, ^else

^then:
  %seven = arith.constant 7 : i32
  cf.br ^join(%seven : i32)

^else:
  %nine = arith.constant 9 : i32
  cf.br ^join(%nine : i32)

^join(%chosen: i32):
  return %chosen : i32
}
```

`cf.br` 传给目标的 Operand 数量和 Type 必须匹配目标 Block 参数。对于 `cf.cond_br`，真、假两个目标分别核对其参数。CFG 中的值是否能在目标位置使用，还需满足 SSA 支配规则。

## 6. SCF 与 CF 的对应关系

| SCF 概念 | CF 展开后的常见结构 |
| --- | --- |
| then/else Region | 分离的基本块及条件跳转 |
| 循环头和循环体 | 多个 Block 与回边 |
| `scf.yield` / 循环携带值 | 跳转目标参数与 branch operands |
| `scf.if` / `scf.for` Operation | CFG 里显式的条件边、回边和合流点 |

SCF 保留“这是条件分支/范围循环”的结构信息，更便于高层分析和变换。CF 把路径表示得更明确，适合后续 CFG 分析和低层转换。lowering 不是把文本换个名字；它必须正确建立块、边、终结操作和跨边值传递。

## 7. 如何判断练习完成到哪一层

1. **结构验证**：IR 解析和 verifier 接受，说明形式及已实现约束成立。
2. **变换检查**：SCF-to-CF 后能看到预期的 Block 和边。
3. **数值执行**：程序真实运行并观察返回值，例如 `10`。
4. **性能测量**：有明确基线、正确性检查和重复测量后再比较。

这四层不能互相替代。后续已用 Homebrew LLVM 22.1.8 的 `mlir-opt --verify-each --convert-scf-to-cf` 验证并 lowering 本讲求和循环；输出出现循环头 Block 参数和回边。累加表的结果 `10` 仍是手工推演，没有真实运行函数。

## 本讲官方资料

- [SCF Dialect](https://mlir.llvm.org/docs/Dialects/SCFDialect/)
- [ControlFlow Dialect](https://mlir.llvm.org/docs/Dialects/ControlFlowDialect/)
- [MLIR Passes：`-convert-scf-to-cf`](https://mlir.llvm.org/docs/Passes/#convert-scf-to-cf)
- [MLIR Language Reference：控制流与 Region](https://mlir.llvm.org/docs/LangRef/)
