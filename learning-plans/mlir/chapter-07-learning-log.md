# 第 07 章：SCF、CF 与控制流

状态：学习进行中。

## 本章路线

1. 用结构化的 `scf.if`、`scf.for`、`scf.while` 表达分支与循环。
2. 理解 `scf.yield`、循环携带值、Block 参数及半开区间。
3. 用 `cf.br`、`cf.cond_br` 和基本块参数表达显式 CFG。
4. 对照 SCF 到 CF 的 lowering，说明结构信息如何变得更显式。
5. 完成条件选择和 0 到 4 求和练习，再进行综合验收。

## 工具与版本

- 2026-10-09 配置了已有 Homebrew LLVM 22.1.8 的 PATH。本章已使用 `mlir-opt` 做解析、验证与 SCF-to-CF 变换，并用 `mlir-runner` 执行求和函数。
- 参考官方 [SCF Dialect](https://mlir.llvm.org/docs/Dialects/SCFDialect/)、[ControlFlow Dialect](https://mlir.llvm.org/docs/Dialects/ControlFlowDialect/) 与 [Passes](https://mlir.llvm.org/docs/Passes/)。

## 第 1 讲：结构化控制流与显式 CFG

- 讲义：[chapter-07-lesson-01.md](chapter-07-lesson-01.md)
- 集中练习：[answers.md](exercises/chapter-07/answers.md)，结构验证、SCF-to-CF 观察与求和函数数值执行已完成
- 可编辑 MLIR 起始文件：[01_choose.mlir](exercises/chapter-07/01_choose.mlir)、[02_sum.mlir](exercises/chapter-07/02_sum.mlir)
- 学习者反馈与验收：`iter_args` 识别方法与多状态传递已通过追问澄清；集中练习的验证/转换/求和执行结果已记录。

### `iter_args` 追问补充

- 学习者提出：多个 loop-carried values 的写法、哪些算法变量要成为 `iter_args`、如何识别。
- 已在讲义增加双状态求和/求积示例、位置对应表、类型/顺序约束及由递推式识别循环状态的方法。
- 后续追问：从用户已有代码中如何发现候选 `iter_args`。已补充逐步回边追踪表、普通 C 示例映射，以及条件更新、内存副作用、零次迭代等边界情况。
- 学习者回答与反馈：待填写

### 环境补齐后的验证记录

- `mlir-opt --version`：Homebrew LLVM 22.1.8。
- `mlir-opt --verify-each --convert-scf-to-cf` 成功处理本讲的 0 到 4 求和循环；输出显式 CFG，循环状态 `%sum_iter` 对应循环头 Block 参数，回边传回更新值。
- 此操作验证 IR 并检查 SCF-to-CF 结果，本身不执行函数；随后另行使用 LLVM lowering 与 runner 验证了数值 `10`。

### 集中练习 01 初次检查

- `01_choose.mlir`：`mlir-opt --verify-each` 通过；只完成结构验证，未执行函数。
- `02_sum.mlir`：手工追踪表正确；首次解析因 `iter_args` 类型写法不符合语法而失败。补充反馈：类型写在 `-> (i32)`，两个加法 Operand 之间补逗号；`%iv` 为 `index` 并通过 `arith.index_cast` 转为 `i32`。
- 后续处理：学习者按反馈修正语法，并完成复验和转换观察。

### 集中练习 01 复验

- `01_choose.mlir`：`mlir-opt --verify-each` 通过，退出码 0。
- `02_sum.mlir`：修正 `iter_args` 结果类型位置及 `arith.addi` Operand 分隔符后，`mlir-opt --verify-each` 通过，退出码 0。
- `--convert-scf-to-cf` 成功。输出循环头 `^bb1(%0: index, %1: i32)` 分别承接归纳变量和累加状态；回边传入递增后的 index 与更新后的 sum；退出块返回最后的 `%1`。
- 手工求和结果为 10。后续经 LLVM dialect lowering 后由 `mlir-runner` 执行，输出也为 `10`；本练习完成结构验证、转换检查与真实数值执行。
