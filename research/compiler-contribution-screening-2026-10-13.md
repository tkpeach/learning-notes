# 编译器贡献选题核查：2026-10-13

> 优先级已更新：以机器码后端求职为主时，LLVM 为第一主线；下文 Dynamatic 路线仅作为 HLS/EDA 备选。详见 [候选仓库统一评估](compiler-open-source-projects.md) 与 [LLVM 全量开放问题清单](llvm-open-beginner-issues-2026-10-13.md)。后者新增非标签 LLVM 候选，取代“抽查未选出”的选题结论；此前核查记录保留供追溯。

目标：从简单任务开始，提升真实编译器后段能力，形成可核验的修复、回归测试和上游贡献。用户已通过投递验证后端岗位匹配；环境为 Mac 和 WSL。实际贡献只考虑开放、未发现认领记录的问题。已解决案例仅用于学习。

## 核查边界

2026-10-13 16:24–16:30（北京时间）读取 GitHub 实时 issue 页面中的状态、指派、正文、可见评论和关联 PR；对最终候选另搜同仓库 PR 中的 issue 编号。无指派不能等同于无人认领；正文中已有修复或贡献意向也排除。搜索零结果只能说明未找到，不能排除未公开开发或没有提及编号的 PR。

本轮是选题核查，尚未构建、运行复现或证明候选仍有缺陷。源码静态检查与设备实测分开。未向维护者发布评论或认领。

## 当前贡献候选

| 候选 | 实时公开状态 | 能力与定位 | 下一步验收 |
| --- | --- | --- | --- |
| [Dynamatic #148](https://github.com/EPFL-LAP/dynamatic/issues/148)：canonicalization patterns / folders | OPEN；无指派；0 评论；无链接修复 PR；编号 PR 搜索 0 | 入门优先。将独立 HandshakeCanonicalize 中已有 pattern 接入 op 的标准 canonicalization 机制，理解 PatternRewriter、folder 和 pipeline。单独属于工程重构，简历分量有限 | 以现有变换行为为基线；测试正反例、幂等性和 pipeline 行为；不顺带实现 #152 的新优化 |
| [Dynamatic #818](https://github.com/EPFL-LAP/dynamatic/issues/818)：乘法缺少反向位宽传播 | OPEN；无指派；1 条讨论评论，无认领表述；无链接修复 PR；编号 PR 搜索 0 | 后续主案例。根据结果使用需求缩窄乘法，学习位宽分析、整数语义、合法性条件和负例。比 #148 更有优化经历价值，初步判断小到中等 | 先复现报告中的低位乘法案例；覆盖多用户、符号扩展和无法缩窄的情况；不能把 IR 位宽降低直接宣称为面积或速度改善 |
| [Dynamatic #819](https://github.com/EPFL-LAP/dynamatic/issues/819)：ori 位宽保守 | OPEN；无指派；0 评论；无链接修复 PR；编号 PR 搜索 0 | #818 后的同模块备选；涉及 sext/zext 和比较消费者，合法性可能比表面更复杂 | 用当前 main 复现；确认不同消费者要求；阅读已有 ori 正确性修复，不能简单删掉保护位 |
| [XLS #490](https://github.com/google/xls/issues/490)：select 改为 case 生成 | OPEN；无指派；0 评论；无链接修复 PR；编号 PR 搜索 0 | 另一个仓库的 RTL CodeGen 备选。学习 XLS IR 到 Verilog 的映射；条目较旧，语义与维护者需求需先确认，未判定为首项简单任务 | 先核验当前生成方式；明确 default、越界选择及未知值语义；不提前承诺 QoR 收益 |

静态源码检查：当前 main 仍有 `lib/Transforms/HandshakeCanonicalize.cpp`，且注册独立 patterns；`HandshakeOptimizeBitwidths.cpp` 中 MulIOp 的 `ArithSingleType` 注册传入固定 `true`，与 #818 所述反向优化缺失相符。此证据不能替代运行复现。

最小路线：#148 熟悉框架 → #818 建立实质优化案例 → 有必要时 #819。#652 的重复实例命名问题虽然公开无人认领，但改动可能过浅，不作为主项目；#148 也不能独自承担后端优化经历的表述。

## 学习案例：不作为自己的贡献

- [LLVM #227648](https://github.com/llvm/llvm-project/issues/227648)：AArch64 GlobalISel 中 debug use 影响乘常数生成；已由 [PR #228100](https://github.com/llvm/llvm-project/pull/228100) 解决。用于学习源码→MIR→combiner→机器码及回归测试链路。
- [Dynamatic PR #884](https://github.com/EPFL-LAP/dynamatic/pull/884)：混合符号／零扩展加法位宽修复，2026-05-02 合入。用于学习位宽优化为什么必须有反例；复现学习不计为贡献。
- [Dynamatic PR #841](https://github.com/EPFL-LAP/dynamatic/pull/841)：ori 混合扩展边界正确性修复，2026-04-20 合入。作为 #819 的前置阅读材料。

## 排除及暂缓记录

| 项目／issue | 原因 |
| --- | --- |
| LLVM #224660 | 无指派，但评论已有认领，并有引用 issue 的修复提交 |
| LLVM #122124 | 有开放修复 PR #139765 |
| LLVM #177448 | 正文已有候选 patch，评论有新的认领；另有旧 PR |
| LLVM #146564 | 调度模型测量与厂商资料存在争议，非首项低沟通成本任务 |
| XLS #751 | 评论已有认领；即使记录较旧也不主动争取接手 |
| Dynamatic #152 | 评论明确有人在做覆盖该情况的 term rewriting 工作 |
| IREE #3859 / #5547 | 已有认领或上游工作历史，不作为无认领新任务 |
| IREE #22684 | 正文作者明确愿意提交 PR，且启用 verifier 会暴露多个测试失败，不作简单首项 |
| IREE #23926 | 正文已有 PR #23927 |
| TileLang #2530 | 有开放修复 PR #2815 |
| TileLang #3225 | 有开放修复 PR #3226 |
| TileLang #2616 | 有开放修复 PR #2820 |

本轮没有从 LLVM、IREE、TileLang 抽查条目中选出同时满足简单、未认领、无修复 PR 的优先候选；这不等于这些仓库没有合适任务。

## 简历证据要求

完成后保留：精简复现、问题根因、合法性条件、前后 IR／目标代码、正反回归测试、相关测试结果、PR 链接与实际合入状态。未合入写“已提交／review 中”；学习复现不写上游贡献；没有综合或实测不填写面积、吞吐或提速百分比。

建议最终主题为“基于 MLIR 的数据流硬件编译优化与上游贡献”。这是 HLS／硬件 IR 后段经历，应准确表述，不能写成 CPU 指令选择或寄存器分配经历。若目标面试明确要求机器码后端，则继续筛 LLVM 局部任务，而不以本路线替代。
