# 第 09 章学习记录：用 C++ 创建、遍历与修改 IR

状态：学习进行中

## 学习材料

- [第 09 章讲义](chapter-09-lesson-01.md)

## 章节目标

- 用 C++ 理解并操作 MLIR IR 的层级与 SSA 数据流。
- 管理 Context、Dialect、Module 和借用句柄的生命周期。
- 用类型化 Op、OpBuilder、walk 检查或创建 IR。
- 修改 IR 时维护 use-def、类型、支配、terminator 和遍历不变量。

## 练习与验收

| 项目 | 状态 | 记录 |
| --- | --- | --- |
| 遍历并统计 `arith.addi` / `arith.muli` | 待开始 | README 第 09 章练习一 |
| Builder 生成参数加一函数 | 待开始 | README 第 09 章练习二 |
| 构建、打印、重新解析与 verifier 检查 | 待开始 | 需记录 LLVM/MLIR 22.1.8 的真实构建环境 |
| 句柄所有权与失效分析 | 待开始 | 与练习中的 Module、Block、Operation、Value 对照 |

## 小结

待学习后填写。
