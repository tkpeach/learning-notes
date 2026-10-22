# LLVM 开放新手问题：全量标签索引与实际切入评估

> 2026-10-14 补充：已按真实合入 PR 核查普通 issue 的新贡献者入口，见 [已合入 PR 分析](llvm-newcomer-merged-pr-analysis-2026-10-14.md)。#231385/#227352 保留为先复现候选；#226919 后置，不能把成本模型任务与前两项视为同等明确的小修复。本文件保留 10 月 13 日全量快照，最新三个候选状态见新分析。

核查日：2026-10-13。全量 API 搜索快照约北京时间 17:20–17:22；未指派项页面核验随后完成，最终 3 个后端候选和 2 个流程练习候选在 20:37 再次刷新。状态会变，实际开始前需再次核查。

## 覆盖范围与“全部”的边界

完整分页获取 llvm/llvm-project 中所有开放 `good first issue`：226 个；另完整获取不重复的开放 `help wanted`：17 个。两者都包括已指派项，便于看到总体空间，而不是只挑几个。API 返回未标记 incomplete，结果小于搜索 1000 上限。

另获取 50 个无指派、零评论的 SelectionDAG（26）、GlobalISel（9）、analysis（15）补充问题，建立后端相关问题入口。共 293 个不同 issue；139 个未指派项读取了实时页面中的正文、可见评论、状态、关联 PR。已指派的 148 项直接排除，未逐条读取其评论。

“所有适合新手”无法仅凭标签客观穷尽：未标签问题很多，简单与否也取决于背景。本报告完整覆盖官方两个入门入口，但补充搜索不是所有未标签后端问题的穷尽，也没有把 293 个条目都认证为适合新手。

页面对 11 个长讨论只加载了部分评论，CSV/表格标注覆盖不完整。这些条目不推荐为“无人认领”。元任务里可能有未认领子项，不能因为整题有人留言就断言所有子项都被占用，也不能在没读完/核对主线前推荐领取。

未执行 LLVM 构建、复现或补丁验证；“优先复现”表示选题候选，不是已证明主线缺陷、可直接合入或维护者已同意方案。没有发布认领评论或 PR。

## 全量搜索的主要结果

| 范围 | 数量 | 解释 |
| --- | ---: | --- |
| 开放 good first issue | 226 | 全仓库，不是 226 个机器码后端问题 |
| 正式指派的 good first issue | 148 | 按用户约束直接排除 |
| 未指派的 good first issue | 78 | 全部读取页面；仍需看评论/PR |
| 上述未指派项中有开放关联 PR | 42 | 共关联 46 个开放 PR，不能从无 assignee 推断空闲 |
| 未挂关联 PR 的 good first issue | 36 | 包含评论认领、集合任务、已有修复只待测试等；不是 36 个空题 |
| 额外 help wanted | 17 | 其中 11 个无指派；不保证小或后端相关 |
| 未标签补充问题 | 50 | 特定 3 个标签下的零评论搜索；不是整个 LLVM 后端搜索全集 |

在剩余新手条目中，#88532 是未发现补测试认领的流程练习候选，属于 Clang 前端，而且原缺陷已有别人的修复，不符合后端核心案例目标。#132614 页面没有关联 PR，但额外编号搜索发现开放补测试 PR #224798，已排除。#205000 的剩余测试需求尚有争议；多个 ClangIR/diagnostics 元任务仍可能拆子项，但需要额外协调且路线偏前端。

**判断：LLVM 仍有进入空间，但对用户更划算的路径是无标签、局部、可复现的后端问题，不是争抢已有人工作的 good first issue。**

## 最值得先验证的候选

### A. #231385：memcmp/bcmp 大尺寸被错误降低成短比较

[Issue #231385](https://github.com/llvm/llvm-project/issues/231385)。20:37 页面：OPEN、无指派、0 评论、无关联 PR；编号 PR 搜索未发现结果。报告提供 IR 与 C reproducer，定位到 SelectionDAGBuilder 的字节数转 bit 数发生 unsigned 截断。

当前主线源码静态检查仍发现该计算与 switch 路径，见 [visitMemCmpBCmpCall](https://github.com/llvm/llvm-project/blob/main/llvm/lib/CodeGen/SelectionDAG/SelectionDAGBuilder.cpp)。这支持优先复现，尚未证明本地运行行为。

为什么适合作第一项：问题范围局部、原理为整数范围/溢出、涉及真实后端 lowering；可以用 llc 的小 IR 测试，不必为了代码生成回归分配 512 MiB 内存，也不必拥有目标硬件。主要学习点是从 library call 到 SelectionDAG load/compare 的选择路径，而不是仅改变量类型。

工作验收：大尺寸应保留正确调用/合法生成方式；原有 2/4/8 等小尺寸优化继续正常；覆盖临界尺寸、不同 triple 和相关比较用途。不能随意移除整个优化作为兜底绕过主路径。第一项简历分量为“后端正确性修复”，再用同模块优化补连续性。

风险：新报告可能很快被认领；报告中有修复建议但未见作者明确认领/已有实际 patch。建议仅在当前主线复现后确定具体方案，不直接照抄报告。

### B. #227352：X86 inline asm 的 A 约束遇到 vector 崩溃

[Issue #227352](https://github.com/llvm/llvm-project/issues/227352)。20:37 页面：OPEN、无指派、0 评论、无关联 PR；编号 PR 搜索未发现结果。

报告包含 C 与 IR 最小案例，对比合法 __int128 和其他 GPR 约束，指出 X86 的 A 约束未拒绝不适合的 vector。当前主线静态检查 case A 仍直接选择寄存器类，见 [X86ISelLowering.cpp](https://github.com/llvm/llvm-project/blob/main/llvm/lib/Target/X86/X86ISelLowering.cpp)。未运行复现。

为什么适合：范围初步小到中等；学习 inline-asm constraints、MVT、寄存器类与 SelectionDAG operand lowering，岗位相关性直接。Mac/WSL 上生成 X86 代码即可，不依赖 AMD/NVIDIA GPU。

工作验收：错误输入产生合理诊断，不 crash；合法整数输入维持原行为；输入/输出/读写约束与 32/64-bit 情况区别验证。实现可能在 target constraint 路径或通用复制路径，需要选择最恰当位置，不能只关闭 assertion 让错误代码通过。

简历分量：有 target lowering 正确性经历，但主要是非法输入处理，不宣称性能优化或新增指令支持。

### C. #226919：补 PDEP/PEXT 的默认展开成本

[Issue #226919](https://github.com/llvm/llvm-project/issues/226919)。20:37 页面：OPEN、无指派、0 评论、无关联 PR；编号 PR 搜索未发现结果。

源码中已有 PDEP/PEXT intrinsic；BasicTTI 的 clmul expansion cost 可作邻近参考，静态检查未找到该文件中显式 PDEP/PEXT 成本处理。应进一步结合 TargetLowering expansion 和具体 target overrides 判断实际缺失。

为什么放第二阶段：学习 TTI、cost model、合法化及软件展开，技术分量较 A/B 更偏优化判断；正文只有短提示，期望精度和范围不够完整，不属于可以直接“填几个数字”的任务。

工作验收：对 native 支持和 software expansion 分开；覆盖 scalar/vector 与代表性 bit width、cost kind；证明数值依据并测试 cost 输出。不能凭成本降低声称运行速度提升。部分目标已覆写时，不要改坏已有主路径。

### 后续备选，暂不作为第一项

- [#51715](https://github.com/llvm/llvm-project/issues/51715)：DAG load 合并丢失 debug value；公开无指派/0 评论/无关联 PR，编号搜索未见结果。但案例来自 2021 年，typed pointer/debug intrinsic 需迁移，先确认新主线仍有问题。难度中等，不把旧题视为新手标签。
- [#164961](https://github.com/llvm/llvm-project/issues/164961)：GlobalISel TableGen combine 不匹配交换操作数的写法。无指派/0 评论/无页面关联 PR；尚未做独立 PR 编号搜索和当前源码核验。限定单个 pattern 与改通用 matcher 的风险差别大。
- [#230890](https://github.com/llvm/llvm-project/issues/230890)：strict FP/half/bfloat legalization 缺口。公开无认领，但涉及多个 operation/type/target 和相关前置 PR，不适合整题作为首项；若拆一个子项需重新核查作者/维护者工作边界。
- [#30255](https://github.com/llvm/llvm-project/issues/30255)：常量乘法展开/合并。老问题、目标成本权衡，先确认当前还存在；编号 PR 搜索命中 #176518 的标题与此题无关，不能将这一命中直接判为占用。

### 官方新手题的流程练习检查结果

- [#88532](https://github.com/llvm/llvm-project/issues/88532)：Clang crash 已由既有修复消除，维护者要求补 regression。未发现补测试认领/关联 PR；编号搜索命中 #163019 的 LoadStoreVectorizer 标题与此题无关，未当作占用证据。只可把自己新增测试写成贡献，不写成修复原缺陷。
- [#132614](https://github.com/llvm/llvm-project/issues/132614)：invalid static friend 声明的 crash 已消失；评论要求给原修复测试文件补此案例。虽然页面无关联 PR，但编号搜索发现开放 [PR #224798](https://github.com/llvm/llvm-project/pull/224798)，不推荐接手。

编号搜索即使零结果也不能排除未公开的工作或未提 issue 编号的 PR；所有候选仍需在实际启动时刷新。GFI 的 AI 修复限制见 [官方政策](https://llvm.org/docs/AIToolPolicy.html)，当前只做搜索/学习整理。

## 如何把这份清单变成后端简历证据

先只复现 A；若当前主线确认且状态仍空闲，则选一项开始。保留主线 revision、最小 IR、调试时发现的节点/类型/控制条件、正反回归、相关 lit 结果与 PR 状态。第一项之后在 SelectionDAG 或同一 target 附近做一个优化，形成共同主题，不必为了凑履历换多个仓库。

“合入小 patch”是起步证据，不等于完整后端工作经历。面试能解释该问题所在阶段、为什么改这里、为什么负例不变，比罗列项目名字更有说服力。

## 全量索引

CSV/JSON 同目录保存结构化字段：scope、area、state、assignees、全部 labels、公开证据、评论覆盖、关联 PR、额外编号搜索和核查时间。下面的全量表保留原标题，避免用我自己的总结替代 issue 名称。


### 官方 good first issue：机器码后端（60）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#230893 [X86] opt in expandFrexp for vector frexp instead of scalarization by libcall](https://github.com/llvm/llvm-project/issues/230893) | 排除：正式指派 | 指派给 Popie52；已指派项未逐条读取评论 |
| [#230886 [X86] opt in expandModf instead of libcall](https://github.com/llvm/llvm-project/issues/230886) | 排除：正式指派 | 指派给 Popie52；已指派项未逐条读取评论 |
| [#229307 [AArch64] DBG_VALUE at successor entry prevents post-index store formation](https://github.com/llvm/llvm-project/issues/229307) | 排除：正式指派 | 指派给 anandkvinu；已指派项未逐条读取评论 |
| [#227927 [AArch64][GlobalISel] Debug instructions break carry-producer adjacency](https://github.com/llvm/llvm-project/issues/227927) | 排除：正式指派 | 指派给 mihaizegheru；已指派项未逐条读取评论 |
| [#227438 [CodeGen][PowerPC] `atan2(double)` is incorrectly recognized as `atan2(double, double)`](https://github.com/llvm/llvm-project/issues/227438) | 排除：正式指派 | 指派给 sangam151；已指派项未逐条读取评论 |
| [#224660 [GlobalISel] Ignore debug instructions in the trunc-store search budget](https://github.com/llvm/llvm-project/issues/224660) | 排除/核实剩余：开放关联 PR | 页面关联 #229492(OPEN) |
| [#206289 [DAG] computeKnownBits - add support for ISD::VECREDUCE_ADD](https://github.com/llvm/llvm-project/issues/206289) | 排除：正式指派 | 指派给 sabonaoabdi；已指派项未逐条读取评论 |
| [#205569 AMDGPU/GlobalISel: use fewer store instructions](https://github.com/llvm/llvm-project/issues/205569) | 排除：正式指派 | 指派给 heturing；已指派项未逐条读取评论 |
| [#202035 [X86] failed to lower llround llroundf lround lroundf to native instruction](https://github.com/llvm/llvm-project/issues/202035) | 排除：正式指派 | 指派给 SunilKumarPradhan；已指派项未逐条读取评论 |
| [#201900 [HLSL][SPIRV] Remove unecessary `STI.isShader()` check that avoid `OpConstantNull`](https://github.com/llvm/llvm-project/issues/201900) | 排除：正式指派 | 指派给 samriddb；已指派项未逐条读取评论 |
| [#200795 [AMDGPU][GlobalIsel] ICE: unable to lower arguments: void (i32)](https://github.com/llvm/llvm-project/issues/200795) | 排除：正式指派 | 指派给 keshavvinayak01；已指派项未逐条读取评论 |
| [#195462 [AVX-512] `splat(u64 & 255) -\| u64s_that_fit_in_bytes` should lower to `vpsubusb`](https://github.com/llvm/llvm-project/issues/195462) | 排除：正式指派 | 指派给 sipher-01；已指派项未逐条读取评论 |
| [#190520 [X86] computeKnownBitsForTargetNode - add X86ISD::GF2P8AFFINEQB handling](https://github.com/llvm/llvm-project/issues/190520) | 排除：正式指派 | 指派给 asadium；已指派项未逐条读取评论 |
| [#189764 [MIRSampleProfile] nullptr deref crash when profile sample use file not found](https://github.com/llvm/llvm-project/issues/189764) | 排除/核实剩余：开放关联 PR | 页面关联 #190186(OPEN) |
| [#189694 [DAG] computeKnownFPClass - add ISD::MAXNUM/MINNUM handling + test coverage](https://github.com/llvm/llvm-project/issues/189694) | 排除：正式指派 | 指派给 Ko496-glitch；已指派项未逐条读取评论 |
| [#189583 [DAG] computeKnownFPClass - add ISD::SQRT handling + test coverage](https://github.com/llvm/llvm-project/issues/189583) | 排除：正式指派 | 指派给 varadk27；已指派项未逐条读取评论 |
| [#189479 [DAG] computeKnownFPClass - add ISD::SINT_TO_FP/UINT_TO_FP handling](https://github.com/llvm/llvm-project/issues/189479) | 排除：正式指派 | 指派给 pau-sum；已指派项未逐条读取评论 |
| [#177448 getNegatedExpression should handle FP16_TO_FP and FP_TO_FP16](https://github.com/llvm/llvm-project/issues/177448) | 暂排除：认领/已有工作线索 | HalfBloodPrince010 2026-07-31T04:30:07Z Hi, I'd like to pick this up, I have the changes, I'll raise the PR.  |
| [#177369 [X86] SimplifyDemandedBitsForTargetNode - add X86ISD::BZHI handling](https://github.com/llvm/llvm-project/issues/177369) | 排除：正式指派 | 指派给 qiongsiwu, SainaDaneshmandjahromi；已指派项未逐条读取评论 |
| [#174584 [DAG] Add MVT:changeVectorElementCount and EVT::changeVectorElementCount](https://github.com/llvm/llvm-project/issues/174584) | 排除：正式指派 | 指派给 ckoparkar；已指派项未逐条读取评论 |
| [#174214 Improving performance of 2xi64 icmp slt/sgt/ult/ugt on SSE2 using 2xi64 sub](https://github.com/llvm/llvm-project/issues/174214) | 排除：正式指派 | 指派给 karouzakisp；已指派项未逐条读取评论 |
| [#168828 [x86] Eliminate `movzx` when upper part of register is irrelevant or overwritten](https://github.com/llvm/llvm-project/issues/168828) | 排除：正式指派 | 指派给 stomfaig；已指派项未逐条读取评论 |
| [#167314 [DAG] MatchLoadCombine - match swapped loads](https://github.com/llvm/llvm-project/issues/167314) | 排除：正式指派 | 指派给 GrumpyPigSkin；已指派项未逐条读取评论 |
| [#164161 [X86] Failure to fold or disjoint nodes into a AVX512 predicated add instruction](https://github.com/llvm/llvm-project/issues/164161) | 排除：正式指派 | 指派给 xyz-harshal；已指派项未逐条读取评论 |
| [#161746 Implement `clz` using floating point math if `clz` instruction is not available](https://github.com/llvm/llvm-project/issues/161746) | 排除：正式指派 | 指派给 def3r；已指派项未逐条读取评论 |
| [#161036 [x86][armv8] Failure to use flag in unsigned underflow compare idiom](https://github.com/llvm/llvm-project/issues/161036) | 排除：正式指派 | 指派给 ckoparkar；已指派项未逐条读取评论 |
| [#153787 [X86] Recognise VPMADD52L/H patterns on AVX512IFMA/AVXIFMA targets](https://github.com/llvm/llvm-project/issues/153787) | 排除：正式指派 | 指派给 Arghnews, sangam151；已指派项未逐条读取评论 |
| [#153543 Wrong types checked at DAGCombiner::visitSRA(SDNode *N)](https://github.com/llvm/llvm-project/issues/153543) | 排除：正式指派 | 指派给 sai18022001；已指派项未逐条读取评论 |
| [#149276 [ARM] computeKnownBitsForTargetNode - add handling for ARMISD::VMOVIMM\VMVNIMM](https://github.com/llvm/llvm-project/issues/149276) | 排除：正式指派 | 指派给 medhatiwari；已指派项未逐条读取评论 |
| [#146564 Zen3 scheduler model for the latency of VEXTRACTF128rri is probably incorrect](https://github.com/llvm/llvm-project/issues/146564) | 暂排除：认领/已有工作线索 | TiborGY 2026-02-11T18:08:35Z 3 hardware, so I will try to take more measurements when I find the time for it, hopefully soon. |
| [#142308 [X86] Failure to reduce extended i64 add/sub/mul arithmetic to i32 with known zeros in the upper 32-bits](https://github.com/llvm/llvm-project/issues/142308) | 排除：正式指派 | 指派给 2elliti；已指派项未逐条读取评论 |
| [#138831 [CodeGen] llc silently ignores -{start\|stop}-{after\|before} options](https://github.com/llvm/llvm-project/issues/138831) | 排除：正式指派 | 指派给 arthur3336；已指派项未逐条读取评论 |
| [#137028 [NVPTX] Test SM Versions via `ptxas`](https://github.com/llvm/llvm-project/issues/137028) | 暂排除：认领/已有工作线索 | AnkitDubeycs25 2026-05-09T18:06:11Z Hi, I'd like to work on this issue. Could this be assigned to me? |
| [#131740 AMDGPU GlobalISel fails on select of G_UBSANTRAP](https://github.com/llvm/llvm-project/issues/131740) | 排除：正式指派 | 指派给 Filip-Nachov；已指派项未逐条读取评论 |
| [#131734 AMDGPU should handle SimplifyDemandedVectorElts for more trivial intrinsics](https://github.com/llvm/llvm-project/issues/131734) | 排除：正式指派 | 指派给 DiviyamPathak；已指派项未逐条读取评论 |
| [#129401 Improve `llvm.ucmp.iN.i1` codegen (specifically the 1-bit inputs case)](https://github.com/llvm/llvm-project/issues/129401) | 排除：正式指派 | 指派给 dipeshs809；已指派项未逐条读取评论 |
| [#128390 AMDGPU is missing simplify demanded bits optimizations of readfirstlane and similar operations](https://github.com/llvm/llvm-project/issues/128390) | 排除：正式指派 | 指派给 ethan0150, donneypr, rdez13；已指派项未逐条读取评论 |
| [#127486 GlobalISel should have G_POISON](https://github.com/llvm/llvm-project/issues/127486) | 排除：正式指派 | 指派给 mtsokol；已指派项未逐条读取评论 |
| [#125950 AMDGPU: can optimize away v_readfirstlane_b32 on implicit_def input](https://github.com/llvm/llvm-project/issues/125950) | 排除：正式指派 | 指派给 JoshHuttonCode；已指派项未逐条读取评论 |
| [#122937 llvm/lib/CodeGen/LiveRangeUtils.h:40: Iterators applied to wrong data structure ?](https://github.com/llvm/llvm-project/issues/122937) | 排除：正式指派 | 指派给 arrowten, souvik150；已指派项未逐条读取评论 |
| [#122124 [AArch64] Correct scheduling information for flag manipulation instructions in Neoverse-V2](https://github.com/llvm/llvm-project/issues/122124) | 排除/核实剩余：开放关联 PR | 页面关联 #139765(OPEN) |
| [#118085 [AArch64][GlobalISel] ABD operations and combines](https://github.com/llvm/llvm-project/issues/118085) | 排除/核实剩余：开放关联 PR | 页面关联 #179437(OPEN) |
| [#116695 [NVPTX] Port code to `llvm/lib/CodeGen/SelectionDAG/*`](https://github.com/llvm/llvm-project/issues/116695) | 排除/核实剩余：开放关联 PR | 页面关联 #167147(OPEN) |
| [#112550 AMDGPU should implement TargetLowering::hasAndNot](https://github.com/llvm/llvm-project/issues/112550) | 排除：正式指派 | 指派给 harrisonGPU；已指派项未逐条读取评论 |
| [#112488 [DAG][X86] Use shrdq to insert into a bitfield](https://github.com/llvm/llvm-project/issues/112488) | 排除：正式指派 | 指派给 pratyaypande, levi42x；已指派项未逐条读取评论 |
| [#108751 AMDGPU should implement IR version of isFMAFasterThanFMulAndFAdd](https://github.com/llvm/llvm-project/issues/108751) | 排除：正式指派 | 指派给 chinmaydd；已指派项未逐条读取评论 |
| [#90714 SelectionDAG store merging default implementations are unreasonable](https://github.com/llvm/llvm-project/issues/90714) | 排除：正式指派 | 指派给 TRIGON01, dev-the-desai；已指派项未逐条读取评论 |
| [#87938 [AMDGPU] generates v_cndmask/lshlrev for uniform select between 0 and a power of 2](https://github.com/llvm/llvm-project/issues/87938) | 排除：正式指派 | 指派给 doraeneko；已指派项未逐条读取评论 |
| [#87497 [AArch64] Add SimplifyDemandedVectorEltsForTargetNode support for AArch64ISD::DUPLANE nodes](https://github.com/llvm/llvm-project/issues/87497) | 排除：正式指派 | 指派给 shivam-dhir；已指派项未逐条读取评论 |
| [#85268 missed fold, sext(fptosi x to i32) =&gt; fptosi x to i64](https://github.com/llvm/llvm-project/issues/85268) | 排除：正式指派 | 指派给 miguelraz；已指派项未逐条读取评论 |
| [#84940 [DAG] SDPatternMatch - add m_BinOp/m_c_BinOp variants driven by TLI.isBinOp/isCommutativeBinOp](https://github.com/llvm/llvm-project/issues/84940) | 排除：正式指派 | 指派给 RKSimon；已指派项未逐条读取评论 |
| [#72640 Loading/storing an 8 aligned i128 uses two `movq` instead of a single `movups`](https://github.com/llvm/llvm-project/issues/72640) | 排除：正式指派 | 指派给 Gonzalosilvalde；已指派项未逐条读取评论 |
| [#64677 Enable exp10 libcall recognition on linux](https://github.com/llvm/llvm-project/issues/64677) | 排除：正式指派 | 指派给 salekinsirajus, Sh0g0-1758；已指派项未逐条读取评论 |
| [#51923 [X86][SSE] Improve ISD::FP_TO_*INT_SAT vector lowering](https://github.com/llvm/llvm-project/issues/51923) | 排除：正式指派 | 指派给 Panadulek；已指派项未逐条读取评论 |
| [#38501 [X86] Add ComputeKnownBits support for BEXTR](https://github.com/llvm/llvm-project/issues/38501) | 排除：正式指派 | 指派给 ArihantChawla；已指派项未逐条读取评论 |
| [#37146 [X86] Add support for X86ISD float2int constant folding](https://github.com/llvm/llvm-project/issues/37146) | 排除：正式指派 | 指派给 Samhitha1212；已指派项未逐条读取评论 |
| [#33874 Improve bitfield arithmetic](https://github.com/llvm/llvm-project/issues/33874) | 排除：正式指派 | 指派给 bhanuponguru, Manojcs47；已指派项未逐条读取评论 |
| [#33870 [DWARF] Line 0 should not have is_stmt set](https://github.com/llvm/llvm-project/issues/33870) | 暂排除：认领/已有工作线索 | OCHyams 2026-03-09T09:25:29Z or it, https://github.com/llvm/llvm-project/pull/166627, I've pinged the author there. Probably best to wait a bit and see if they respond. |
| [#32961 [X86][SSE] Recognise v2i64 comparison patterns](https://github.com/llvm/llvm-project/issues/32961) | 排除：正式指派 | 指派给 fuad1502；已指派项未逐条读取评论 |
| [#104 Calling convention differs from MSVC for member functions returning SIMD types](https://github.com/llvm/llvm-project/issues/104) | 排除：正式指派 | 指派给 henrybw；已指派项未逐条读取评论 |



### 官方 good first issue：分析/中端/LLVM核心（28）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#229536 [KnownFPClass] Teach KnownFPClass that `sinh(non-positive) = non-positive`](https://github.com/llvm/llvm-project/issues/229536) | 排除：正式指派 | 指派给 siddhp1；已指派项未逐条读取评论 |
| [#229532 [KnownFPClass] Teach KnownFPClass that `asin(non-positive) = non-positive`](https://github.com/llvm/llvm-project/issues/229532) | 排除：正式指派 | 指派给 printf-komano；已指派项未逐条读取评论 |
| [#229529 [KnownFPClass] Teach KnownFPClass that `atan(non-positive) = non-positive`](https://github.com/llvm/llvm-project/issues/229529) | 排除：正式指派 | 指派给 Wael-06；已指派项未逐条读取评论 |
| [#226865 [InstCombine] `log(exp10(y))` -&gt; `y*log(10)` missing for `llvm.exp10` intrinsic argument](https://github.com/llvm/llvm-project/issues/226865) | 排除：正式指派 | 指派给 eator；已指派项未逐条读取评论 |
| [#226284 [KnownBits] Tighten division bounds if the division is exact](https://github.com/llvm/llvm-project/issues/226284) | 排除：正式指派 | 指派给 Talb057；已指派项未逐条读取评论 |
| [#216127 [InstCombine] Add folds like UCmp(a ±ⁿᵘʷ n, b ±ⁿᵘʷ n) → UCmp(a, b)](https://github.com/llvm/llvm-project/issues/216127) | 排除/核实剩余：开放关联 PR | 页面关联 #222978(OPEN) |
| [#204945 `pext(x & m, m)` -&gt; `pext(x, m)`](https://github.com/llvm/llvm-project/issues/204945) | 排除：正式指派 | 指派给 aadanen；已指派项未逐条读取评论 |
| [#201328 missed optimization of and + csel + sub](https://github.com/llvm/llvm-project/issues/201328) | 排除：正式指派 | 指派给 iamaayushrivastava；已指派项未逐条读取评论 |
| [#191975 [opt] -passes="place-safepoints" causes Assertion `F && "gc.safepoint_poll function is missing"'](https://github.com/llvm/llvm-project/issues/191975) | 排除/核实剩余：开放关联 PR | 页面关联 #205520(OPEN) |
| [#174143 [InstCombine] SimplifyDemandedFPClass - add DemandedElts demanded vector elements argument](https://github.com/llvm/llvm-project/issues/174143) | 排除：正式指派 | 指派给 kevinlim17；已指派项未逐条读取评论 |
| [#173780 [InstCombine] SimplifyDemandedBits - add basic bitcast handling](https://github.com/llvm/llvm-project/issues/173780) | 排除：正式指派 | 指派给 Xinlong-Chen, varadk27；已指派项未逐条读取评论 |
| [#141479 Missed optimization: (%1 &lt;= ~%0) && (%0 &gt; ~%1) ==&gt; false](https://github.com/llvm/llvm-project/issues/141479) | 排除：正式指派 | 指派给 bobby-b-song；已指派项未逐条读取评论 |
| [#139786 Missed Optimization: max(max(x, c1) &lt;&lt; c2, c3) —&gt; max(x &lt;&lt; c2, c3) when c3 &gt;= c1 * 2 ^ c2](https://github.com/llvm/llvm-project/issues/139786) | 排除：正式指派 | 指派给 ameliajochna, Charukesh827；已指派项未逐条读取评论 |
| [#138334 Funnel shift in 64-bit doesn't get matched to an intrinsic](https://github.com/llvm/llvm-project/issues/138334) | 排除：正式指派 | 指派给 sallto；已指派项未逐条读取评论 |
| [#133875 MetaRenamer command line options should be replaced with pass parameters](https://github.com/llvm/llvm-project/issues/133875) | 排除：正式指派 | 指派给 egorshamshura；已指派项未逐条读取评论 |
| [#131601 Auto-vectorize saturating addition](https://github.com/llvm/llvm-project/issues/131601) | 排除：正式指派 | 指派给 gbMattN；已指派项未逐条读取评论 |
| [#130088 Failure to recognise unnecessary sext for add+cmp](https://github.com/llvm/llvm-project/issues/130088) | 排除：正式指派 | 指派给 sreedivyakottilingal；已指派项未逐条读取评论 |
| [#112631 scalbln(x, n), scalbn(x, n), ldexp(x, n) are not folded at the compilation time when (x, n) is constant](https://github.com/llvm/llvm-project/issues/112631) | 排除：正式指派 | 指派给 fawdlstty, ashwinagrl；已指派项未逐条读取评论 |
| [#92433 [InstCombine] Failure to factorize `add`/`sub` and `max`/`min` using distributivity](https://github.com/llvm/llvm-project/issues/92433) | 排除：正式指派 | 指派给 jf-botto；已指派项未逐条读取评论 |
| [#86161 [InstCombine] Missed optimization : fold `switch(rol(a, c))`](https://github.com/llvm/llvm-project/issues/86161) | 排除：正式指派 | 指派给 YanWQ-monad；已指派项未逐条读取评论 |
| [#85241 missed fold: (X * 0.0) * constant =&gt; X * 0.0](https://github.com/llvm/llvm-project/issues/85241) | 排除：正式指派 | 指派给 SahilPatidar；已指派项未逐条读取评论 |
| [#84213 [Support] Investigate making KnownBits saturated add/sub implementations optimal ](https://github.com/llvm/llvm-project/issues/84213) | 排除：正式指派 | 指派给 Mabwas；已指派项未逐条读取评论 |
| [#83430 [InstCombine] Missed optimization: fail to fold `(A &gt;&gt; C1) Pred C2` if `shr` is used multiple times](https://github.com/llvm/llvm-project/issues/83430) | 排除：正式指派 | 指派给 SahilPatidar；已指派项未逐条读取评论 |
| [#76438 basic properties of floor and ceiling function](https://github.com/llvm/llvm-project/issues/76438) | 排除：正式指派 | 指派给 Ayushpdx05；已指派项未逐条读取评论 |
| [#57255 Suboptimal instruction sequence when operands are reordered](https://github.com/llvm/llvm-project/issues/57255) | 排除：正式指派 | 指派给 gxyd；已指派项未逐条读取评论 |
| [#50308 Trivial memset optimization not applied to loops under -Oz (LoopIdiomRecognize)](https://github.com/llvm/llvm-project/issues/50308) | 暂排除：认领/已有工作线索 | amordo 2025-04-17T16:54:50Z op-rotate,loop-idiom"` eventually works, but they are not seen in `-help` anymore https://llvm.godbolt.org/z/49j7WhaPq  upd2: TIL the order in `-passes` ma；评论未全部加载，不能确认剩余子任务无人认领 |
| [#29043 Unnecessary vector type produces wrong ll parser error](https://github.com/llvm/llvm-project/issues/29043) | 排除/核实剩余：开放关联 PR | 页面关联 #216253(OPEN) |
| [#175 [Attributor] Make use of analysis in the MustBeExecutedExplorer ](https://github.com/llvm/llvm-project/issues/175) | 暂排除：认领/已有工作线索 | Sammy-code04092006 2026-02-01T18:54:21Z of GSoC 2026.  I’m new to the Attributor framework and would like to work on this issue. Could you please confirm whether this issue is still relevant and  |



### 官方 good first issue：MLIR（11）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#115989 [MLIR][affine] Proper handling of vector load / stores in Affine dialect and transformations](https://github.com/llvm/llvm-project/issues/115989) | 排除/核实剩余：开放关联 PR | 页面关联 #167229(OPEN) |
| [#115849 [MLIR][affine] Illegal affine loop fusion with vector types](https://github.com/llvm/llvm-project/issues/115849) | 排除：正式指派 | 指派给 rhanqtl；已指派项未逐条读取评论 |
| [#112913 [mlir][Vector] Improve support for 0-d vectors in vector dialect lowerings](https://github.com/llvm/llvm-project/issues/112913) | 排除：正式指派 | 指派给 harrisonGPU；已指派项未逐条读取评论 |
| [#104593 [mlir] Auto generate docs for dialect op interfaces](https://github.com/llvm/llvm-project/issues/104593) | 排除：正式指派 | 指派给 ammar2199；已指派项未逐条读取评论 |
| [#94968 [mlir][transform] ApplyToEachResultList does not define STL convenience methods](https://github.com/llvm/llvm-project/issues/94968) | 排除：正式指派 | 指派给 Groverkss；已指派项未逐条读取评论 |
| [#76839 Implement `insertVar` having `Identifier` parameter](https://github.com/llvm/llvm-project/issues/76839) | 排除：正式指派 | 指派给 zjaffal；已指派项未逐条读取评论 |
| [#51660 Implement non-unit stride dense vectorization (difficult starter)](https://github.com/llvm/llvm-project/issues/51660) | 排除：正式指派 | 指派给 aartbik；已指派项未逐条读取评论 |
| [#51657 Implement more Python DSL-based "exhaustive" sparse kernel generators (easy starter)](https://github.com/llvm/llvm-project/issues/51657) | 排除：正式指派 | 指派给 aartbik；已指派项未逐条读取评论 |
| [#51651 Implement strategy for loop ordering choice (true compiler starter)](https://github.com/llvm/llvm-project/issues/51651) | 排除：正式指派 | 指派给 aartbik；已指派项未逐条读取评论 |
| [#51650 Implement sparse kernel benchmarks (moderate level, independent, starter)](https://github.com/llvm/llvm-project/issues/51650) | 排除：正式指派 | 指派给 solo-daemon；已指派项未逐条读取评论 |
| [#51649 Enhance our tests for sparse kernels (medium level, independent, starter)](https://github.com/llvm/llvm-project/issues/51649) | 排除：正式指派 | 指派给 aartbik, pranav-kumar-hex；已指派项未逐条读取评论 |



### 官方 good first issue：JIT/链接（3）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#213425 clang-repl: Objective-C message sends abort ("unrecognized selector") because JIT ObjC selrefs are not registered](https://github.com/llvm/llvm-project/issues/213425) | 排除/核实剩余：开放关联 PR | 页面关联 #217988(OPEN) |
| [#63236 orc::InProcessMemoryMapper makes too many memory mappings](https://github.com/llvm/llvm-project/issues/63236) | 排除/核实剩余：开放关联 PR | 页面关联 #61418(OPEN)；评论未全部加载，不能确认剩余子任务无人认领 |
| [#55681 Check for `__unw_add_dynamic_eh_frame_section` in non-ORC-runtime exception registration paths.](https://github.com/llvm/llvm-project/issues/55681) | 暂排除：认领/已有工作线索 | shivam-dhir 2026-01-22T06:36:35Z Hi, I would love to work on this issue |



### 官方 good first issue：前端/ClangIR（60）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#229300 [clang] Missing diagnostic location for ext_vector_type in templates](https://github.com/llvm/llvm-project/issues/229300) | 排除/核实剩余：开放关联 PR | 页面关联 #229328(OPEN) |
| [#223064 constant evaluator loses track of most-derived array information when reconstructing `LValue` from `APValue`](https://github.com/llvm/llvm-project/issues/223064) | 排除/核实剩余：开放关联 PR | 页面关联 #230599(OPEN) |
| [#219531 `__builtin_bit_cast` of an ext_vector element yields lane 0 at run time, disagreeing with constant evaluation](https://github.com/llvm/llvm-project/issues/219531) | 排除/核实剩余：开放关联 PR | 页面关联 #219646(OPEN) |
| [#211770 [clang] Add thousands-separator to "cannot allocate array; evaluated array bound [...] exceeds the limit" diagnostic](https://github.com/llvm/llvm-project/issues/211770) | 排除/核实剩余：开放关联 PR | 页面关联 #211785(OPEN) |
| [#205000 crash building with reflect-cpp and c++26](https://github.com/llvm/llvm-project/issues/205000) | 暂缓：已修复，测试覆盖有争议 | 评论指向已有修复，是否需要独立回归仍待核查 |
| [#187675 -Wdangling-field detects view members initalized from a by-value owner parameter](https://github.com/llvm/llvm-project/issues/187675) | 排除/核实剩余：开放关联 PR | 页面关联 #195981(OPEN) |
| [#186274 performance optimization: special-case deduction for variables of type `auto`](https://github.com/llvm/llvm-project/issues/186274) | 排除/核实剩余：开放关联 PR | 页面关联 #188196(OPEN) |
| [#185382 [CIR] Upstream handling of AArch64 (Arm) Neon builtins](https://github.com/llvm/llvm-project/issues/185382) | 子任务空间待查：不作无人认领整题 | 集合/元任务，已有多人认领或工作线索；需单独核查子项；评论未全部加载，不能确认剩余子任务无人认领 |
| [#184672 [clang] warn on operator in macro expansion whose operand doesn't lie entirely within the same macro expansion](https://github.com/llvm/llvm-project/issues/184672) | 排除/核实剩余：开放关联 PR | 页面关联 #184924(OPEN) |
| [#180046 Clang elides the wrong part of the template type in error message.](https://github.com/llvm/llvm-project/issues/180046) | 排除/核实剩余：开放关联 PR | 页面关联 #180175(OPEN) |
| [#176468 Refactor `CodeGenFunction::EmitStoreThroughLValue` in `CGExpr.cpp` to consolidate HLSL-specific behavior into helper functions](https://github.com/llvm/llvm-project/issues/176468) | 排除：正式指派 | 指派给 emias11；已指派项未逐条读取评论 |
| [#175934 [clang]Crash in `getASTRecordLayout` when a class template has a field of type `decltype(&static data member)`](https://github.com/llvm/llvm-project/issues/175934) | 排除/核实剩余：开放关联 PR | 页面关联 #227288(OPEN), #227936(OPEN) |
| [#167765 [CIR] Implement missing X86 builtins](https://github.com/llvm/llvm-project/issues/167765) | 子任务空间待查：不作无人认领整题 | 集合/元任务，已有多人认领或工作线索；需单独核查子项；评论未全部加载，不能确认剩余子任务无人认领 |
| [#167752 [CIR] Upstream handling of X86 builtins](https://github.com/llvm/llvm-project/issues/167752) | 子任务空间待查：不作无人认领整题 | 集合/元任务，已有多人认领或工作线索；需单独核查子项；评论未全部加载，不能确认剩余子任务无人认领 |
| [#166623 Missing changes for WG14 N3622](https://github.com/llvm/llvm-project/issues/166623) | 排除/核实剩余：开放关联 PR | 页面关联 #167086(OPEN) |
| [#163601 Complete VTable class name for types](https://github.com/llvm/llvm-project/issues/163601) | 子任务空间待查：不作无人认领整题 | 集合/元任务，已有多人认领或工作线索；需单独核查子项；评论未全部加载，不能确认剩余子任务无人认领 |
| [#160556 [Headers][X86] Allow AVX512 masked bitlogic intrinsics to be used in constexpr](https://github.com/llvm/llvm-project/issues/160556) | 排除：正式指派 | 指派给 benedekaibas；已指派项未逐条读取评论 |
| [#160516 [Clang] VectorExprEvaluator::VisitCallExpr / InterpretBuiltin - allow SSE/AVX/AVX512 square root intrinsics to be used in constexpr](https://github.com/llvm/llvm-project/issues/160516) | 排除：正式指派 | 指派给 bojle；已指派项未逐条读取评论 |
| [#160473 [X86][Clang] VectorExprEvaluator::VisitCallExpr / InterpretBuiltin - allow SSE/AVX COMI/UCOMI/CMPS/CMPP fp comparison intrinsics to be used in constexpr](https://github.com/llvm/llvm-project/issues/160473) | 排除：正式指派 | 指派给 ZakyHermawan；已指派项未逐条读取评论 |
| [#159905 [clang] Bitcasts from vectors to integers not supported at compile time](https://github.com/llvm/llvm-project/issues/159905) | 排除/核实剩余：开放关联 PR | 页面关联 #231331(OPEN) |
| [#158116 guarded_by attributes not supported using c++11 style](https://github.com/llvm/llvm-project/issues/158116) | 排除/核实剩余：开放关联 PR | 页面关联 #167048(OPEN) |
| [#156747 [CIR] Upstream missing tests from the ClangIR incubator](https://github.com/llvm/llvm-project/issues/156747) | 子任务空间待查：不作无人认领整题 | 集合/元任务，已有多人认领或工作线索；需单独核查子项；评论未全部加载，不能确认剩余子任务无人认领 |
| [#154747 [Clang] Allow __builtin_fma/fmaf/fmal to be used in a constant expression](https://github.com/llvm/llvm-project/issues/154747) | 排除：正式指派 | 指派给 ckoparkar；已指派项未逐条读取评论 |
| [#148938 #pragma init_seg(section-specifier, func-name) not supported](https://github.com/llvm/llvm-project/issues/148938) | 排除/核实剩余：开放关联 PR | 页面关联 #203769(OPEN) |
| [#141911 [Clang] Explain satisfaction failure for more type traits](https://github.com/llvm/llvm-project/issues/141911) | 子任务空间待查：不作无人认领整题 | 集合/元任务，已有多人认领或工作线索；需单独核查子项；评论未全部加载，不能确认剩余子任务无人认领 |
| [#141797 `[[gnu::weak]]` disables constant evaluation of constexpr variables in C++14](https://github.com/llvm/llvm-project/issues/141797) | 暂排除：认领/已有工作线索 | sangam151 2026-09-03T18:41:55Z ting the issue I’m currently working on. |
| [#139268 [OpenMP] Assertion `llvm::isUIntN(BitWidth, val) && "Value is not an N-bit unsigned value"' failed.](https://github.com/llvm/llvm-project/issues/139268) | 排除：正式指派 | 指派给 albus-droid；已指派项未逐条读取评论 |
| [#134049 Specific structure name can cause shadowing of globally defined lambda, causing "struct::operator()" to be called instead of "lambda::operator()"](https://github.com/llvm/llvm-project/issues/134049) | 暂排除：认领/已有工作线索 | shivam-dhir 2026-01-22T06:26:02Z Hi, I would love to work on this issue |
| [#132614 [clang] Assertion `DS.getStorageClassSpec() == DeclSpec::SCS_unspecified` fails with invalid static friend function declaration](https://github.com/llvm/llvm-project/issues/132614) | 排除：编号搜索发现开放补测试 PR | PR #224798；页面无关联 PR 但额外编号搜索发现具体补测试工作 |
| [#132604 [clang++] operator==(vector of long, vector of long) -&gt; vector of long long](https://github.com/llvm/llvm-project/issues/132604) | 排除：正式指派 | 指派给 ImpleLee；已指派项未逐条读取评论 |
| [#123121 Audit/Update `select` uses in DiagnosticXKinds.td to use `enum_select`.](https://github.com/llvm/llvm-project/issues/123121) | 排除：正式指派 | 指派给 amansharma612；已指派项未逐条读取评论 |
| [#121952 Stack-overflow as a result of stack exhaustion in function `assign()`](https://github.com/llvm/llvm-project/issues/121952) | 暂排除：认领/已有工作线索 | sangam151 2026-09-03T14:05:18Z Hi, I’d like to work on this issue. Please assign it to me. |
| [#119190 [Clang][Driver][Test] No negative tests for unsupported options in different drivers](https://github.com/llvm/llvm-project/issues/119190) | 排除：正式指派 | 指派给 GeorgeKA；已指派项未逐条读取评论 |
| [#112909 [clang] Assertion `(!needsOverloadResolutionForCopyConstructor() \|\| (data().DeclaredSpecialMembers & SMF_CopyConstructor)) && "this property has not yet been computed by Sema"' failed.](https://github.com/llvm/llvm-project/issues/112909) | 排除：正式指派 | 指派给 njriasan, vortex73；已指派项未逐条读取评论 |
| [#104770 Unnecessary return statement in unreachable block generated by EmitFunctionEpilog in musttail cases. ](https://github.com/llvm/llvm-project/issues/104770) | 排除：正式指派 | 指派给 chfast, kiran-isaac；已指派项未逐条读取评论 |
| [#103038 [clang-analyzer-security.insecureAPI.strcpy] extend list of unsafe functions](https://github.com/llvm/llvm-project/issues/103038) | 暂排除：认领/已有工作线索 | shivam-dhir 2026-01-22T06:30:04Z Hi, I would love to work on this issue |
| [#97087 [clang] [C++20] Defaulted `operator==` doesn't lookup in using-directive properly](https://github.com/llvm/llvm-project/issues/97087) | 排除/核实剩余：开放关联 PR | 页面关联 #99542(OPEN), #166996(OPEN) |
| [#96638 Optimize `decltype(T{})` to `T` in compiler error messages](https://github.com/llvm/llvm-project/issues/96638) | 暂排除：认领/已有工作线索 | shivam-dhir 2026-01-22T06:31:17Z Hi, I would love to work on this issue |
| [#93288 Addressing `-Wimplicit-float-conversion` warning might lead to precision loss](https://github.com/llvm/llvm-project/issues/93288) | 暂排除：认领/已有工作线索 | shivam-dhir 2026-01-22T06:32:28Z Hi, I would love to work on this issue |
| [#92224 [clang] Deduplicate `FinishTemplateArgumentDeduction` helper function in `SemaTemplateDeduction.cpp`.](https://github.com/llvm/llvm-project/issues/92224) | 暂排除：认领/已有工作线索 | Thibault-Monnier 2026-02-28T19:10:59Z @hokein I've been trying to work on this, but from what I can tell there is not much duplication between the three implementations, except from this |
| [#91564 [clang][C++] Bad error recovery when classes are defined inside template aliases](https://github.com/llvm/llvm-project/issues/91564) | 排除/核实剩余：开放关联 PR | 页面关联 #142278(OPEN) |
| [#89400 Clang crash on template friend function definition](https://github.com/llvm/llvm-project/issues/89400) | 排除/核实剩余：开放关联 PR | 页面关联 #231022(OPEN) |
| [#88532 Access violation at instantiating variable definition 'std::_Is_ranges_input_iter_v...'](https://github.com/llvm/llvm-project/issues/88532) | 流程练习备选：前端补测试 | 评论说明 crash 已修复，维护者要求补回归；不算自己的缺陷修复 |
| [#82754 [OpenMP] Metadirective uses default for non-const user condition](https://github.com/llvm/llvm-project/issues/82754) | 排除/核实剩余：开放关联 PR | 页面关联 #86457(OPEN) |
| [#75754 hasAnyArgument() spuriously ignores match](https://github.com/llvm/llvm-project/issues/75754) | 排除：正式指派 | 指派给 komalverma04；已指派项未逐条读取评论 |
| [#73399 Simplify initialisation diagnostic when types are cv-qualified](https://github.com/llvm/llvm-project/issues/73399) | 排除：正式指派 | 指派给 cjdb, NoumanAmir657；已指派项未逐条读取评论 |
| [#71675 [clang] Avoid printing overly large integer/_BitInt numbers in static assertion failure diagnostics](https://github.com/llvm/llvm-project/issues/71675) | 排除：正式指派 | 指派给 maramatias；已指派项未逐条读取评论 |
| [#61157 [clang][ExtractAPI] Declaration fragments should show types as shown in the source code.](https://github.com/llvm/llvm-project/issues/61157) | 暂排除：认领/已有工作线索 | shivam-dhir 2026-01-22T06:35:55Z Hi, I would love to work on this issue |
| [#58276 Unrelated errors introduce additional runtime diagnostics by skipping CFG construction](https://github.com/llvm/llvm-project/issues/58276) | 暂排除：认领/已有工作线索 | shafik 2026-09-03T17:30:18Z uncing you are working on it can prevent duplicative work.  |
| [#53049 clang: `std::sort` with `std::ref(comparator)` using recent libstdc++ fails compilation with `exception specification uses itself`](https://github.com/llvm/llvm-project/issues/53049) | 暂排除：认领/已有工作线索 | awayzjj 2026-10-12T11:02:30Z @zyn0217 Hi, I'd like to work on this! I will add a regression test. Please assign it to me. |
| [#51787 [Clang] Support elementwise/reduction builtins in constexpr contexts.](https://github.com/llvm/llvm-project/issues/51787) | 暂排除：认领/已有工作线索 | saideepaksana 2025-11-04T18:47:55Z mma @fhahn @RKSimon @EugeneZelenko @Endilll I would like to work on this issue, would someone assign it to me?；评论未全部加载，不能确认剩余子任务无人认领 |
| [#48977 We should probably warn at how 'static inline' variables are odd at namespace scope.](https://github.com/llvm/llvm-project/issues/48977) | 排除：正式指派 | 指派给 serberoth；已指派项未逐条读取评论 |
| [#47285 "this requires expression will only be checked for syntactic validity" suggests bad fixit, is not emitted on equally dangerous code](https://github.com/llvm/llvm-project/issues/47285) | 暂排除：认领/已有工作线索 | shivam-dhir 2026-01-22T06:39:08Z Hi, I would love to work on this issue |
| [#46331 Clang crashed in clang/include/clang/AST/Type.h:676: const clang::ExtQualsTypeCommonBase *clang::QualType::getCommonPtr() const: Assertion '!isNull() && "Cannot retrieve a NULL type pointer"' failed](https://github.com/llvm/llvm-project/issues/46331) | 排除/核实剩余：开放关联 PR | 页面关联 #226722(OPEN) |
| [#43453 Create a check that warns about using %p printf specifier](https://github.com/llvm/llvm-project/issues/43453) | 排除/核实剩余：开放关联 PR | 页面关联 #75472(OPEN) |
| [#39524 c11: Accepts ill-formed program with inline function definition containing modifiable variable with static storage duration.](https://github.com/llvm/llvm-project/issues/39524) | 排除：正式指派 | 指派给 Susikrishna；已指派项未逐条读取评论 |
| [#34652 include/clang/Tooling/Refactoring/Rename/RenamingAction.h:79]: (performance)](https://github.com/llvm/llvm-project/issues/34652) | 排除/核实剩余：开放关联 PR | 页面关联 #69848(OPEN) |
| [#33528 Improve -Wparentheses for arbitrary bool contexts](https://github.com/llvm/llvm-project/issues/33528) | 排除：正式指派 | 指派给 seranu；已指派项未逐条读取评论 |
| [#28406 clang crashes on x86_64-linux-gnu with Assertion `power &lt;= maxExponent' failed](https://github.com/llvm/llvm-project/issues/28406) | 排除/核实剩余：开放关联 PR | 页面关联 #102051(OPEN) |
| [#15522 Can not use C99 function names as variable names in C89](https://github.com/llvm/llvm-project/issues/15522) | 排除/核实剩余：开放关联 PR | 页面关联 #190244(OPEN), #129979(OPEN) |



### 官方 good first issue：库/运行时/OpenMP（17）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#230110 [libc] printf functions assume %s argument points to a null terminated string even when precision is specified.](https://github.com/llvm/llvm-project/issues/230110) | 排除：正式指派 | 指派给 cornaud；已指派项未逐条读取评论 |
| [#227265 [flang][OpenMP] Segfault in OmpStructureChecker::Enter(parser::Module) when modules form a USE cycle](https://github.com/llvm/llvm-project/issues/227265) | 排除：正式指派 | 指派给 mihaizegheru；已指派项未逐条读取评论 |
| [#223717 [libc][bazel] Add targets for long double functions/tests to bazel files](https://github.com/llvm/llvm-project/issues/223717) | 暂排除：认领/已有工作线索 | KaustAbhinand 2026-10-12T15:03:08Z  someone still working on this? If not, I would like to take it up :) |
| [#223714 [libc][bazel] Add targets for Double functions/tests to bazel files](https://github.com/llvm/llvm-project/issues/223714) | 暂排除：认领/已有工作线索 | s4chinjha 2026-09-25T14:57:25Z ishbhandari11t i'm working on it |
| [#223664 [libc][bazel] Add targets for float functions/tests to bazel files](https://github.com/llvm/llvm-project/issues/223664) | 排除：正式指派 | 指派给 Popie52；已指派项未逐条读取评论 |
| [#221801 [libc][bazel] Add missing targets for math functions/tests to bazel files](https://github.com/llvm/llvm-project/issues/221801) | 子任务空间待查：不作无人认领整题 | 集合/元任务，已有多人认领或工作线索；需单独核查子项 |
| [#221574 [libc] Modify NaN/Payload related functions for emulated float128 type](https://github.com/llvm/llvm-project/issues/221574) | 排除：正式指派 | 指派给 Popie52；已指派项未逐条读取评论 |
| [#221569 [libc] Modify modff128, remquof128 and canonicalizef128 for emulated Float128](https://github.com/llvm/llvm-project/issues/221569) | 排除：正式指派 | 指派给 goyaladitya05；已指派项未逐条读取评论 |
| [#219759 [libc] Modify Exponent scaling functions to work with emulated Float128](https://github.com/llvm/llvm-project/issues/219759) | 排除：正式指派 | 指派给 rigalis；已指派项未逐条读取评论 |
| [#219757 [libc] Modify Exponent decomposition functions to work with emulated Float128](https://github.com/llvm/llvm-project/issues/219757) | 排除/核实剩余：开放关联 PR | 页面关联 #221540(OPEN), #229855(OPEN) |
| [#195620 [libc] Check the ordering of the *at syscalls](https://github.com/llvm/llvm-project/issues/195620) | 排除：正式指派 | 指派给 udaykiriti；已指派项未逐条读取评论 |
| [#195400 [libc][math] Add missing isnan variants for float16, bfloat16, and float128](https://github.com/llvm/llvm-project/issues/195400) | 排除：正式指派 | 指派给 TarunAkash, iamaayushrivastava, 0bVdnt；已指派项未逐条读取评论 |
| [#195276 [libc] Request for Annex K via `__STDC_WANT_LIB_EXT1__` doesn't work as expected](https://github.com/llvm/llvm-project/issues/195276) | 排除/核实剩余：开放关联 PR | 页面关联 #229587(OPEN) |
| [#133505 [libc] Clean up copt naming](https://github.com/llvm/llvm-project/issues/133505) | 排除：正式指派 | 指派给 hulxv；已指派项未逐条读取评论 |
| [#129123 Implement fixed point mulifx functions in llvm-libc](https://github.com/llvm/llvm-project/issues/129123) | 排除：正式指派 | 指派给 naveen106；已指派项未逐条读取评论 |
| [#122006 [libc][docs][POSIX] flush out documentation for the POSIX defined headers](https://github.com/llvm/llvm-project/issues/122006) | 排除：正式指派 | 指派给 StarOne01, siya100, marcury122；已指派项未逐条读取评论 |
| [#77170 `std::filesystem::canonical("")` should throw](https://github.com/llvm/llvm-project/issues/77170) | 排除：正式指派 | 指派给 Yuki-cpp；已指派项未逐条读取评论 |



### 官方 good first issue：工具/调试器/BOLT（29）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#217375 Crash running clang-tidy, in "bugprone-unique-ptr-array-mismatch"](https://github.com/llvm/llvm-project/issues/217375) | 排除/核实剩余：开放关联 PR | 页面关联 #219050(OPEN) |
| [#189672 [clang-tidy] Add `readability-use-rethrow` check](https://github.com/llvm/llvm-project/issues/189672) | 排除：正式指派 | 指派给 tharunvk；已指派项未逐条读取评论 |
| [#177466 [clangd] crashes with a SIGSEGV when receiving a textDocument/didOpen request where the URI points to a directory instead of a file.](https://github.com/llvm/llvm-project/issues/177466) | 排除/核实剩余：开放关联 PR | 页面关联 #177834(OPEN) |
| [#168920 [LLDB] Swig python extensions are missing test coverage](https://github.com/llvm/llvm-project/issues/168920) | 子任务空间待查：不作无人认领整题 | 集合/元任务，已有多人认领或工作线索；需单独核查子项 |
| [#166750 [clang-tidy] llvm-header-guard suggest invalid ifdef macros name](https://github.com/llvm/llvm-project/issues/166750) | 排除：正式指派 | 指派给 sathvikreddy853；已指派项未逐条读取评论 |
| [#117431 move `AST_MATCHER(VarDecl, isLocal) { return Node.isLocalVarDecl(); }` to ast-matcher](https://github.com/llvm/llvm-project/issues/117431) | 排除：正式指派 | 指派给 phychee；已指派项未逐条读取评论 |
| [#90661 [BOLT] Evaluate and speedup discoverFileObjects](https://github.com/llvm/llvm-project/issues/90661) | 暂排除：认领/已有工作线索 | shivam-dhir 2026-01-22T06:33:32Z Hi, I would love to work on this issue |
| [#75685 `bugprone-dangling-handle.HandleClasses` should update its defaults](https://github.com/llvm/llvm-project/issues/75685) | 排除：正式指派 | 指派给 maxjtwelftree；已指派项未逐条读取评论 |
| [#68213 clang-include-cleaner - replaces chrono with bits/chrono](https://github.com/llvm/llvm-project/issues/68213) | 排除/核实剩余：开放关联 PR | 页面关联 #205719(OPEN) |
| [#64441 clang-tidy: fully qualify names from a given namespace (e.g. clean up `using namespace std;`)](https://github.com/llvm/llvm-project/issues/64441) | 排除：正式指派 | 指派给 oyiekeallen；已指派项未逐条读取评论 |
| [#58710 Feature Request: Add clang-format setting to disable "*" being added when ReflowComments is used with /* */ comments](https://github.com/llvm/llvm-project/issues/58710) | 排除：正式指派 | 指派给 bhanuponguru；已指派项未逐条读取评论 |
| [#56009 clang-tidy: readability-implicit-bool-conversion not working with std::optional](https://github.com/llvm/llvm-project/issues/56009) | 排除：正式指派 | 指派给 huangperry；已指派项未逐条读取评论 |
| [#55026 clang-tidy check readability-container-data-pointer fix isn't configurable to use std::string::c_str() instead of data()](https://github.com/llvm/llvm-project/issues/55026) | 排除/核实剩余：开放关联 PR | 页面关联 #190590(OPEN) |
| [#53740 Add equivalent of LambdaBodyIndentation for ObjC blocks](https://github.com/llvm/llvm-project/issues/53740) | 排除：正式指派 | 指派给 shivam-dhir；已指派项未逐条读取评论 |
| [#52935 JavaScriptWrapImports:false doesn't work with ColumnLimit:0](https://github.com/llvm/llvm-project/issues/52935) | 排除/核实剩余：开放关联 PR | 页面关联 #211347(OPEN) |
| [#42113 recognize aligned case statements](https://github.com/llvm/llvm-project/issues/42113) | 暂排除：认领/已有工作线索 | hdsatam 2026-07-04T02:29:05Z i if no one is working on this can I be assigned to it? |
| [#42112 add newline between include and namespace](https://github.com/llvm/llvm-project/issues/42112) | 排除：正式指派 | 指派给 seranu；已指派项未逐条读取评论 |
| [#40511 Create bugprone-printf-array check](https://github.com/llvm/llvm-project/issues/40511) | 排除/核实剩余：开放关联 PR | 页面关联 #182823(OPEN) |
| [#39145 DWARF parser: &lt;DW_OP_piece for offset 4 but top of stack is of size 8&gt;](https://github.com/llvm/llvm-project/issues/39145) | 排除：正式指派 | 指派给 curiouserrandy；已指派项未逐条读取评论 |
| [#38995 SortIncludes should support "@import" lines in Objective-C](https://github.com/llvm/llvm-project/issues/38995) | 排除：正式指派 | 指派给 shivam-dhir；已指派项未逐条读取评论 |
| [#38089 bugprone check for delete this](https://github.com/llvm/llvm-project/issues/38089) | 排除：正式指派 | 指派给 cd578596-8da0-4f5b-aaae-5d286920841a；已指派项未逐条读取评论 |
| [#37751 Macros on access specifiers not formatted correctly](https://github.com/llvm/llvm-project/issues/37751) | 排除：正式指派 | 指派给 eoan-ermine；已指派项未逐条读取评论 |
| [#36323 Add option to readability-implicit-bool-conversion check to allow implicit conversion *to bool*](https://github.com/llvm/llvm-project/issues/36323) | 排除：正式指派 | 指派给 saideepaksana；已指派项未逐条读取评论 |
| [#35414 modernize-use-digit-separator](https://github.com/llvm/llvm-project/issues/35414) | 排除：正式指派 | 指派给 IvanArkhipov1999；已指派项未逐条读取评论 |
| [#34434 readability check to convert numerical constants to std::numeric_limits](https://github.com/llvm/llvm-project/issues/34434) | 排除：正式指派 | 指派给 divvelarakesh1；已指派项未逐条读取评论 |
| [#31860 Readability check for position of constant operand in binary operators](https://github.com/llvm/llvm-project/issues/31860) | 排除：正式指派 | 指派给 saideepaksana；已指派项未逐条读取评论 |
| [#31744 [X86] update_llc_test_checks.py fails on win32 triples](https://github.com/llvm/llvm-project/issues/31744) | 暂排除：认领/已有工作线索 | Unique-Usman 2024-03-26T12:25:50Z Can this be assigned to me also, thank you.  |
| [#24841 Replace /* ... */ single-line comments with // ... comments](https://github.com/llvm/llvm-project/issues/24841) | 排除：正式指派 | 指派给 4m4n-x-B4w4ne；已指派项未逐条读取评论 |
| [#22583 Replace memcpy with std::copy](https://github.com/llvm/llvm-project/issues/22583) | 排除：正式指派 | 指派给 kidq330；已指派项未逐条读取评论 |



### 官方 good first issue：其他/需定位（18）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#229729 [flang] CDEFINED not allowed on this kind of symbol at flang/lib/Semantics/symbol.cpp](https://github.com/llvm/llvm-project/issues/229729) | 排除：正式指派 | 指派给 Anastasia-Artemova；已指派项未逐条读取评论 |
| [#227460 [flang] `-ffixed-line-length=&lt;n&gt;` silently truncates values larger than INT_MAX](https://github.com/llvm/llvm-project/issues/227460) | 排除：正式指派 | 指派给 Popie52；已指派项未逐条读取评论 |
| [#227340 [flang] A module that USEs itself directly in its specification part is not diagnosed](https://github.com/llvm/llvm-project/issues/227340) | 排除：正式指派 | 指派给 ErickTejaxun；已指派项未逐条读取评论 |
| [#219453 [flang] semantic errors involving mismatched types could be more useful](https://github.com/llvm/llvm-project/issues/219453) | 排除：正式指派 | 指派给 hizyyo；已指派项未逐条读取评论 |
| [#212675 Codegen for type-aware allocation attempts to compute the size of an incomplete type when building in c++17 mode](https://github.com/llvm/llvm-project/issues/212675) | 排除/核实剩余：开放关联 PR | 页面关联 #213455(OPEN) |
| [#198106 OCUDU benchmarks notably slower on clang22 than gcc16 on avx512 target](https://github.com/llvm/llvm-project/issues/198106) | 排除：正式指派 | 指派给 pechy；已指派项未逐条读取评论 |
| [#171877 [ConstantFolding] Move `LibCallSimplifier::optimizeFdim` into ConstantFolding](https://github.com/llvm/llvm-project/issues/171877) | 排除：正式指派 | 指派给 Ronxvier；已指派项未逐条读取评论 |
| [#166155 [llvm] Document non-trivial `llvm::DenseMapBase` member functions](https://github.com/llvm/llvm-project/issues/166155) | 排除：正式指派 | 指派给 TarunAkash, Priyanshi-dixit1；已指派项未逐条读取评论 |
| [#147850 Port JSON output format for llvm-dwarfdump](https://github.com/llvm/llvm-project/issues/147850) | 排除：正式指派 | 指派给 arrowten；已指派项未逐条读取评论 |
| [#139512 Doxygen links to wrong implementation file](https://github.com/llvm/llvm-project/issues/139512) | 排除：正式指派 | 指派给 TheShubhendra；已指派项未逐条读取评论 |
| [#123756 [llvm-mca][FeatureRequest] In timeline graph, note source of delay for each instruction](https://github.com/llvm/llvm-project/issues/123756) | 排除：正式指派 | 指派给 sommersun；已指派项未逐条读取评论 |
| [#123041 Add a `--verbose` option for `llvm-strip`](https://github.com/llvm/llvm-project/issues/123041) | 排除：正式指派 | 指派给 iamaayushrivastava；已指派项未逐条读取评论 |
| [#114711 Are the tutorials up-to-date? (Clang version is 20.0.0git)](https://github.com/llvm/llvm-project/issues/114711) | 排除：正式指派 | 指派给 siya100；已指派项未逐条读取评论 |
| [#108469 [feature][riscv] handle target address calculation in llvm-objdump disassembly for riscv](https://github.com/llvm/llvm-project/issues/108469) | 排除：正式指派 | 指派给 arjunUpatel；已指派项未逐条读取评论 |
| [#63178 llvm-symbolizer  --markup-filter does not adjust addresses without debug info](https://github.com/llvm/llvm-project/issues/63178) | 排除：正式指派 | 指派给 maximeplante；已指派项未逐条读取评论 |
| [#59471 a missing `type` field in `DISubprogram` does not give a warning but a Segmentation fault](https://github.com/llvm/llvm-project/issues/59471) | 排除：正式指派 | 指派给 epilk, kzhuravl；已指派项未逐条读取评论 |
| [#50033 Finish / clean up MapFile implementation](https://github.com/llvm/llvm-project/issues/50033) | 排除：正式指派 | 指派给 511f4a7d-587a-442f-a387-2e7710d2d094；已指派项未逐条读取评论 |
| [#37301 [meta] [debugify] fix -check-debugify failures](https://github.com/llvm/llvm-project/issues/37301) | 子任务空间待查：不作无人认领整题 | 集合/元任务，已有多人认领或工作线索；需单独核查子项；评论未全部加载，不能确认剩余子任务无人认领 |



### 额外官方 help wanted（17）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#195661 [C++20] [Modules] Duplicate-mangled-name codegen error for SSE intrinsics when two module partitions both `#include &lt;emmintrin.h&gt;` in their global module fragment](https://github.com/llvm/llvm-project/issues/195661) | 排除/核实剩余：开放关联 PR | 页面关联 #219238(OPEN) |
| [#174067 [C++20] [Modules] [Windows] Collections for C++20 Modules for windows in clang](https://github.com/llvm/llvm-project/issues/174067) | 待专门评估：非小型后端首项 | help wanted 不等于 easy；范围、认领与现状见正文/评论 |
| [#174065 [C++20] [Modules] Not proper module initializer](https://github.com/llvm/llvm-project/issues/174065) | 待专门评估：非小型后端首项 | help wanted 不等于 easy；范围、认领与现状见正文/评论 |
| [#174064 [C++20] [Modules] Not properly mangling for entities in named modules for MSVC ABI](https://github.com/llvm/llvm-project/issues/174064) | 排除/核实剩余：开放关联 PR | 页面关联 #220820(OPEN) |
| [#173997 [clang] [windows] [modules] undefined symbol when exporting variable from shared library](https://github.com/llvm/llvm-project/issues/173997) | 排除：正式指派 | 指派给 ChuanqiXu9；已指派项未逐条读取评论 |
| [#167638 C++ Member pointer with module causing clang crash](https://github.com/llvm/llvm-project/issues/167638) | 排除：正式指派 | 指派给 ChuanqiXu9；已指派项未逐条读取评论 |
| [#167624 [libc] Better implementation of Strlen for SVE targets](https://github.com/llvm/llvm-project/issues/167624) | 待专门评估：非小型后端首项 | help wanted 不等于 easy；范围、认领与现状见正文/评论 |
| [#159225 [C++20] [Modules] Support attributes on module declarations](https://github.com/llvm/llvm-project/issues/159225) | 排除：正式指派 | 指派给 yronglin；已指派项未逐条读取评论 |
| [#120215 `libc++.modules.json` resource does not exist](https://github.com/llvm/llvm-project/issues/120215) | 待专门评估：非小型后端首项 | help wanted 不等于 easy；范围、认领与现状见正文/评论 |
| [#110751 Clang 19 crashes when exporting an inline struct or class in a module in windows](https://github.com/llvm/llvm-project/issues/110751) | 待专门评估：非小型后端首项 | help wanted 不等于 easy；范围、认领与现状见正文/评论 |
| [#110016 [mlir][spirv] Update the spirv dialect scripts to accept the updated spirv json schema](https://github.com/llvm/llvm-project/issues/110016) | 待专门评估：非小型后端首项 | help wanted 不等于 easy；范围、认领与现状见正文/评论 |
| [#109895 [modules] -print-file-name=libc++.modules.json does not work in mac m1](https://github.com/llvm/llvm-project/issues/109895) | 待专门评估：非小型后端首项 | help wanted 不等于 easy；范围、认领与现状见正文/评论；评论未全部加载，不能确认剩余子任务无人认领 |
| [#62268 [flang] Feature request: support for -Os/-Oz](https://github.com/llvm/llvm-project/issues/62268) | 排除：正式指派 | 指派给 tarunprabhu；已指派项未逐条读取评论 |
| [#180 [OpenMP] Memory transfer optimizations](https://github.com/llvm/llvm-project/issues/180) | 待专门评估：非小型后端首项 | help wanted 不等于 easy；范围、认领与现状见正文/评论 |
| [#179 [Attributor] Cleanup and upstream `Attribute::MaxObjectSize`](https://github.com/llvm/llvm-project/issues/179) | 待专门评估：非小型后端首项 | help wanted 不等于 easy；范围、认领与现状见正文/评论 |
| [#174 [OpenMP][Opt] Track internal control variables (ICVs) and optimize accordingly](https://github.com/llvm/llvm-project/issues/174) | 排除：正式指派 | 指派给 jdoerfert, sstefan1；已指派项未逐条读取评论 |
| [#172 [Attributor] IPO across non-amenable call edges](https://github.com/llvm/llvm-project/issues/172) | 排除：正式指派 | 指派给 jdoerfert；已指派项未逐条读取评论 |



### 未标签补充搜索：SelectionDAG（26）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#231385 [SelectionDAG] memcmp/bcmp of 2^29+2 bytes is lowered to a 2-byte compare](https://github.com/llvm/llvm-project/issues/231385) | 优先复现：小型后端正确性修复 | 当前源码仍有字节数转 bit 数的 unsigned 截断路径；未运行复现 |
| [#231378 [SelectionDAG] SimplifyDemandedBits drops exact when narrowing SRL](https://github.com/llvm/llvm-project/issues/231378) | 排除：正文已有实现 | 报告者明确在本地 downstream build 验证了候选 patch |
| [#230890 [SelectionDAG] Strict FP operations on soft-promoted half and bfloat crash](https://github.com/llvm/llvm-project/issues/230890) | 后续备选：不作首项 | 多种 strict FP/half/bfloat legalization 缺口，相关前置修复已有人做 |
| [#230786 [SelectionDAG] Strict fptosi/fptoui from half crashes on soft-float targets](https://github.com/llvm/llvm-project/issues/230786) | 排除/核实剩余：开放关联 PR | 页面关联 #230889(OPEN) |
| [#229646 [DAGCombiner] Select of FP constants on a poison condition becomes an out-of-bounds constant-pool load](https://github.com/llvm/llvm-project/issues/229646) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#227352 [X86] Vector input for inline-asm constraint "A" asserts "lossy conversion of vector to scalar type"; missing diagnostic](https://github.com/llvm/llvm-project/issues/227352) | 优先复现：局部 X86 约束修复 | 当前 case A 未像其他 GPR 约束一样排除 vector；未运行复现 |
| [#226962 Implement ctz using floating point math if clz instruction is not available](https://github.com/llvm/llvm-project/issues/226962) | 排除/核实剩余：开放关联 PR | 页面关联 #227210(OPEN) |
| [#223152 [SelectionDAG] ScheduleDAGFast crashes on a node blocked by two live physical registers](https://github.com/llvm/llvm-project/issues/223152) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#222231 [SelectionDAG] mergeTruncStores merges into an illegal i16 after type legalization ("Unexpected illegal type!" / "Cannot select")](https://github.com/llvm/llvm-project/issues/222231) | 排除/核实剩余：开放关联 PR | 页面关联 #222245(OPEN) |
| [#221433 [SelectionDAG][DAGCombiner] Compile time blows up in TokenFactor inlining for a basic block with a few thousand strided stores](https://github.com/llvm/llvm-project/issues/221433) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#217613 [DAG] vector cond ? x / C1: x / C2 should avoid twice division](https://github.com/llvm/llvm-project/issues/217613) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#200653 [SelectionDAG] General case expansion for CLMUL is bad](https://github.com/llvm/llvm-project/issues/200653) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#172100 [SDAG] Masking vector lanes instead of truncating](https://github.com/llvm/llvm-project/issues/172100) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#171909 [SDAG] Scalarization as an option in `LegalizeAction`](https://github.com/llvm/llvm-project/issues/171909) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#161977 Clang taking a long time when compiling with O2 O3 optimisation levels](https://github.com/llvm/llvm-project/issues/161977) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#149820 [DAG] Is load(constant_pool) guaranteed not to be poison/undef?](https://github.com/llvm/llvm-project/issues/149820) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#118812 [ISel type legalization] Unprocessed value in a map! PromotedIntegers](https://github.com/llvm/llvm-project/issues/118812) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#98379 Segfault compiling inline asm for wrong arch: `llc  …/X86/callbr-asm-outputs.ll` “couldn't allocate output register for constraint” after `SelectionDAGBuilder::visitCallBrLandingPad`](https://github.com/llvm/llvm-project/issues/98379) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#76331 [llc] llvm-isel-fuzzer--aarch64-O2: Timeout in llvm-isel-fuzzer--aarch64-O2](https://github.com/llvm/llvm-project/issues/76331) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#73010 ISel fails on Glue-edges with TableGen data](https://github.com/llvm/llvm-project/issues/73010) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#52864 llc 13.0.0 *** Scheduling failed! *** ](https://github.com/llvm/llvm-project/issues/52864) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#52863 ResourcePriorityQueue.cpp:56: llvm::ResourcePriorityQueue::ResourcePriorityQueue(llvm::SelectionDAGISel *):Assertion `ResourcesModel && "Unimplemented CreateTargetScheduleState."' failed.](https://github.com/llvm/llvm-project/issues/52863) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#51715 [DAGCombiner] SDDbgValue is set as invalid by tryToFoldExtOfLoad()](https://github.com/llvm/llvm-project/issues/51715) | 老问题备选：先迁移并复现 | 2021 年 typed-pointer/debug intrinsic reproducer，调试信息路径已演进 |
| [#45213 Missed optimization: unnecessary move with division-by-multiplication](https://github.com/llvm/llvm-project/issues/45213) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#30255 Expression can be expanded to fold two constant integer multiplies into one.](https://github.com/llvm/llvm-project/issues/30255) | 老问题备选：先确认仍缺失 | 2016 年 missed optimization，有成本权衡；编号搜索结果 #176518 标题无关，不当作修复证据 |
| [#23964 Division/modulo by constant can be optimized to take bounds of the dividend into account](https://github.com/llvm/llvm-project/issues/23964) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |



### 未标签补充搜索：GlobalISel（9）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#220807 [GlobalISel] unreachable hit on an 80-bit ANY_SCALAR (x86_fp80) at `getFltSemanticForLLT`](https://github.com/llvm/llvm-project/issues/220807) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#220802 [GlobalISel] legalizer aborts on a plain vector ctpop](https://github.com/llvm/llvm-project/issues/220802) | 排除/核实剩余：开放关联 PR | 页面关联 #223945(OPEN) |
| [#204182 [GlobalISel] Miscompilation where an i31 no-wrap negation inside a min chain is lowered incorrectly](https://github.com/llvm/llvm-project/issues/204182) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#164961 [GlobalISel] Tablegen combines are not commutative](https://github.com/llvm/llvm-project/issues/164961) | 后续备选：范围需确认 | TableGen combine 的 commutativity；修单条 pattern 与改通用 matcher 是不同范围 |
| [#150875 [GlobalIsel] Assertion when generating code for ptrtoint with vector operands](https://github.com/llvm/llvm-project/issues/150875) | 排除/核实剩余：开放关联 PR | 页面关联 #175270(OPEN) |
| [#139078 [GlobalISel] Indirectify memory inputs for inline assembly](https://github.com/llvm/llvm-project/issues/139078) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#119667 [GlobalISel] Add Floating Point Type to LLT](https://github.com/llvm/llvm-project/issues/119667) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#113668 [GlobalISel] Divide multiple values by the same value.](https://github.com/llvm/llvm-project/issues/113668) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#112513 Discussion/Analysis Issue for PR112370](https://github.com/llvm/llvm-project/issues/112513) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |



### 未标签补充搜索：analysis（15）


| Issue / 原标题 | 状态判断 | 公开证据 / 限制 |
| --- | --- | --- |
| [#229383 [LAA] Retry with runtime checks adds checks that always fail](https://github.com/llvm/llvm-project/issues/229383) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#226919 [CostModel] Add default expansion costs for Intrinsic::PDEP/PEXT](https://github.com/llvm/llvm-project/issues/226919) | 第二阶段：成本模型 | 默认 expansion cost 缺失；需核对不同类型/目标的实际展开，不能只填常数 |
| [#225516 Compute known mantissa/fraction bits for `SIToFP`/`UIToFP`](https://github.com/llvm/llvm-project/issues/225516) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#223345 [ValueTracking] A strict range on x - y does not establish x != y](https://github.com/llvm/llvm-project/issues/223345) | 排除：开放修复 PR | PR #225200 |
| [#212497 clang crashes on valid code at -O1 and above on x86_64-linux-gnu: fatal error: error in backend: Found 1 machine code errors](https://github.com/llvm/llvm-project/issues/212497) | 排除/核实剩余：开放关联 PR | 页面关联 #213093(OPEN) |
| [#212019 clang, Floating point exception in distributeIrrLoopHeaderMass in BlockFrequencyInfoImpl.cpp with PGO profile](https://github.com/llvm/llvm-project/issues/212019) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#207926 missed fold for bitop(x) \| x in bool context](https://github.com/llvm/llvm-project/issues/207926) | 暂缓：已有关闭修复 PR | PR #207938 被关闭且有设计反馈；不当作从未认领任务 |
| [#207131 [ValueTracking] Dead branch on smin(a,b) &gt; K not eliminated under bounded operand guards](https://github.com/llvm/llvm-project/issues/207131) | 排除/核实剩余：开放关联 PR | 页面关联 #227205(OPEN) |
| [#188944 InlineCost::get() relies on asserts to reject sentinel costs, causing debug/release inconsistency with inline-cost testing attributes](https://github.com/llvm/llvm-project/issues/188944) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#156940 A `separate_storage` assume shouldn't capture pointers](https://github.com/llvm/llvm-project/issues/156940) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#134367 StackSafetyLocalAnalysis Assertion failed with ASAN](https://github.com/llvm/llvm-project/issues/134367) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#96454 [LICM] TSVC s113: LICM doesn't work for a load for an array with the constant index](https://github.com/llvm/llvm-project/issues/96454) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#78756 llvm/unittests/Analysis/ConstraintSystemTest.cpp crashes in debug mode](https://github.com/llvm/llvm-project/issues/78756) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#39872 dependence analysis degradations due to removal of GEP analysis in D35430](https://github.com/llvm/llvm-project/issues/39872) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |
| [#25836 Alias analysis on function with noalias arguments inferior to inlined function with scoped-noalias](https://github.com/llvm/llvm-project/issues/25836) | 待评估：未判定新手适合 | 无指派、页面无关联 PR；未做完整源码/运行验证 |



## 可复查的搜索条件


- `repo:llvm/llvm-project is:issue is:open label:"good first issue"`

- `repo:llvm/llvm-project is:issue is:open label:"help wanted" -label:"good first issue"`

- `repo:llvm/llvm-project is:issue is:open no:assignee label:"llvm:SelectionDAG" comments:0`

- `repo:llvm/llvm-project is:issue is:open no:assignee label:"llvm:globalisel" comments:0`

- `repo:llvm/llvm-project is:issue is:open no:assignee label:"llvm:analysis" comments:0`