# 第 07 章答题表：SCF 与 CF

请编辑答案栏写关键词和观察结果。代码请直接改同目录的两个 `.mlir` 起始文件。

## 练习一：条件选择

目标：`%cond` 为真返回 7，为假返回 9。

- then 分支 yield 的值和类型：`%seven : i32`
- else 分支 yield 的值和类型：`%nine : i32`
- 两个分支值如何成为函数外可用的 `%chosen`：被选择分支的 `scf.yield` 把值交给父 `scf.if`，其 Result 为 `%chosen : i32`
- `mlir-opt --verify-each` 结果：通过，退出码 0
- 验收层级：结构验证已完成；未做变换检查或数值执行

## 练习二：循环求和

目标：计算 `0 + 1 + 2 + 3 + 4`，使用循环携带值。

| `%iv` | 本轮 `%sum_it` | 本轮更新值 |
| ---: | ---: | ---: |
| 0 | 0 | 0 |
| 1 | 0 | 1 |
| 2 | 1 | 3 |
| 3 | 3 | 6 |
| 4 | 6 | 10 |

- `%iv` 的类型及其转换：`index`，通过 `arith.index_cast` 转为 `i32`
- `iter_args` 初值、循环体参数、yield 值、最终 Result 的对应关系：`%sum_init` → `%sum_it` → `%sum_next` → `%sum`
- 手工推演结果：10
- `mlir-opt --verify-each` 结果：通过，退出码 0
- `--convert-scf-to-cf` 后看到的循环头参数/回边传值：循环头 `^bb1` 参数 `%0: index`（归纳变量）、`%1: i32`（累加状态）；前驱传入 `%c0` 与 `%c0_i32`；回边传入更新后的 `%5: index` 与 `%4: i32`；退出块返回 `%1`
- 数值执行：将 SCF/Arith/CF/Func lowering 到 LLVM dialect 后，由 `mlir-runner -e=sum_five --entry-point-result=i32` 执行，输出 `10`
- 已完成层级：结构验证、SCF-to-CF 变换、数值执行

## 自我检查

- 为什么 `%iv` 不放进这次练习的 `iter_args`？是循环变量，不属于`iter_args`
- 如果循环零次执行，最终累加值应是什么？0

## 检查记录（2026-10-09）

- 练习一：结构验证通过（`mlir-opt --verify-each`，退出码 0）。未实际运行带输入参数的函数，所以只完成结构验证，没有分别执行两个分支。
- 练习二：首次工具解析曾因语法错误失败，现已修正。`mlir-opt --verify-each`、`--convert-scf-to-cf` 和 `mlir-runner` 数值执行均完成。
- 语法应为 `iter_args(%sum_it = %sum_init) -> (i32) {`：初值绑定里不写 `: i32`，结果类型列在 `-> (i32)`。
- 算术行的两个 Operand 之间需逗号：`arith.addi %sum_it, %iv_i32 : i32`。
- `%iv` 的类型与转换应完整写成：`index`，通过 `arith.index_cast` 转为 `i32`。
- 数值执行命令：

  ```sh
  zsh -lc 'mlir-opt learning-plans/mlir/exercises/chapter-07/02_sum.mlir --convert-scf-to-cf --convert-arith-to-llvm --convert-cf-to-llvm --convert-func-to-llvm --reconcile-unrealized-casts -o /private/tmp/mlir_ch07_sum_llvm.mlir'
  zsh -lc 'mlir-runner /private/tmp/mlir_ch07_sum_llvm.mlir -e=sum_five --entry-point-result=i32'
  ```

  输出：`10`。因此练习二完成结构验证、SCF-to-CF 变换和真实数值执行。
