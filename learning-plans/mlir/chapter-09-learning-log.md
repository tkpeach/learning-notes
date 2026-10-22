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

集中练习与可编辑记录：[exercises/chapter-09/answers.md](exercises/chapter-09/answers.md)。C++ 工程骨架：`exercises/chapter-09/CMakeLists.txt`、`exercises/chapter-09/main.cpp`。

按学习者反馈，本章练习文档新增 22.1.8 本机 API 速查、头文件与 `rg` 查找命令，避免为推进 TODO 猜 API 名称；练习完成后新增费曼复述、导师边界追问、修正解释和迁移检验。核心计数与 IR 构造仍由学习者完成。

环境初检（2026-10-12）：本机 `llvm-config` 与 `mlir-opt` 均为 22.1.8；存在 MLIR 头文件、MLIR CMake package 和库文件，且 CMake 可用。工程尚未构建，练习代码尚未验证。

| 项目 | 状态 | 记录 |
| --- | --- | --- |
| 遍历并统计 `arith.addi` / `arith.muli` | 待回答 | 给定两个函数的输入，其中 `arith.subi` 是计数干扰项 |
| Builder 生成参数加一函数 | 待回答 | 由 TODO 骨架创建 Module、FuncOp、Block 和运算 |
| 条件变化迁移 | 待回答 | 将加一函数改为参数乘 3 的函数 |
| 构建、打印与 verifier 检查 | 待执行 | 配置命令和 `mlir-opt --verify-each` 命令写在答案文档中 |
| 句柄所有权与失效分析 | 待回答 | 对照 OwningOpRef、Op wrapper、Builder 和 walk |

## 小结

待学习后填写。
