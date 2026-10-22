# 编译器开源候选仓库：定位、现状与实际入门成本

> 统一评估日期：2026-10-14。此文是候选仓库的唯一维护入口，合并了此前两份仓库评估，并采用后续核查修正后的判断。Issue 清单与 PR 证据单独保留，不在这里重复堆积。

快速导航：[优先级与判断口径](#priority) · [机器后端/CPU](#cpu) · [EDA/HLS](#eda) · [AI/异构](#ai) · [其他编译器核心](#other) · [补充候选](#additional) · [暂缓项目](#deferred) · [选择与简历](#decision)

## 1. 你的目标与阅读方式

目标是补足已经在面试中暴露的**直接编译器后端经历**：做能独立解释、经过回归验证的真实上游贡献，写进简历。你已经通过投递验证机器后端岗位相对容易匹配；现有 C++/EDA 背景应尽量复用。环境是 Mac、WSL，必要时 Linux；起步从小题开始，实际贡献只选开放且未发现认领或关联实现的问题。

本文详细评估 **26 个主要候选**，另补充 6 个值得了解但当前靠后的候选；其他相邻项目列出后置原因。建议先读优先级表，再看相应方向的逐仓库说明。不需要把所有仓库都构建一遍。

必须区分三类技术经历：

| 路线 | 典型工作 | 直接候选 |
| --- | --- | --- |
| 机器码后端 | 指令选择、合法化、寄存器分配、调度、ABI、机器码生成 | LLVM、Cranelift、llvm-aie；AsmJit 是较聚焦的机器码/JIT 库 |
| EDA/HLS 编译后段 | 硬件 IR 优化、综合映射、位宽、硬件调度、RTL 或仿真模型生成 | Yosys、CIRCT、Verilator、XLS、Dynamatic |
| AI 编译后段 | 张量/循环变换、布局、buffer、设备映射、LLVM IR 或设备代码生成 | IREE、TVM、Triton、TileLang、Inductor 等 |

使用 LLVM、生成 C++、项目包含“backend”，都不足以证明做过机器指令后端。简历应写自己实际修改的阶段、变换和验证结果。

<a id="priority"></a>

## 2. 优先级与判断依据

这不是仓库综合实力排行榜，而是针对你的求职匹配、已有基础和第一项贡献成本的选择顺序。同组由具体岗位与可用题目决定先后。

| 优先组 | 候选 | 为什么保留 | 开始前必须满足的条件 |
| --- | --- | --- | --- |
| 第一主线 | **LLVM** | 与已验证的后端岗位最直接；普通 issue 有新人进入先例 | 精简输入在主线复现，局部后端测试可跑，当前无人占用 |
| EDA 优先组 | **Yosys / CIRCT / Verilator** | 最能复用 EDA+C++；分别对应综合、硬件 IR、仿真 CodeGen | 选优化/lowering/生成的小题；避免完整语言支持和新架构设计 |
| 便捷优化备选 | **Binaryen** | C++、无需构建 LLVM、无需专用硬件，pass 测试聚焦 | 接受 Wasm 优化与机器后端的匹配差异；仍需筛普通问题 |
| CPU/机器后端条件备选 | **ISPC / Cranelift / AsmJit** | SIMD、真正机器后端、小型机器码工程分别有价值 | ISPC 补 SPMD；Cranelift 愿意学 Rust；AsmJit 先确认具体任务和 review 通路 |
| AI 条件备选 | **IREE CPU / TileLang / Inductor CPU / ExecuTorch EXIR / Halide / TVM** | 能形成 AI 编译技术案例 | 先有明确小题与模块；设备能验证；不从完整模型部署起步 |
| 专项或观察 | **XLS / Dynamatic / llvm-aie / MLIR-AIE / Triton / XLA / 其余候选** | 特定 HLS、NPU、GPU 或语言编译需求时有价值 | JD、设备、语义背景对齐，否则第一项投入不划算 |

**对之前判断的统一修正：** Yosys 应补入 EDA 优先组；IREE 活跃且有指导证据，但 GFI 清单陈旧、近期任务已有占用，不再默认“容易开始”；Dynamatic 是有真实技术价值的学术 HLS 项目，不能凭现有证据宣称广泛工业采用；高 star 并不降低任务占用、设备或 review 门槛。

### 怎样理解“新手友好”

- **源码开发环境：** 安装工具能运行，只能帮助复现；修改源码、重建、独立跑测试才是闭环。
- **范围与背景：** 一个已有 pass 的精简错误，通常比新 dialect、新架构或完整模型支持更可控；代码行数少不表示语义简单。
- **设备与测试：** 静态 IR/生成检查和实际执行/性能验证分开。Mac/WSL 不能代替 GPU/NPU/FPGA。
- **任务与 review：** 读认领评论、关联 PR、历史方案及近期外部 review；无 assignee 和 GFI 标签都不能直接证明可做。
- **简历价值：** 实质变换、分析、CodeGen 与回归优先；文档、安装、示例可练流程，但不能承担本次核心案例。

本文没有在你的机器实际构建所有仓库。“低/中/高成本”来自官方文档、依赖结构、测试方式与公开 review，属于相对工程判断，不承诺跑通时间或合入概率。已合入 PR 仅供学习，不能当作待领取任务；除单独核查的 LLVM 等线索外，本评估不等于已经为每仓库找到开放未认领小题。

### 状态与数据的口径

项目定位与原 17 项资料读取于 2026-10-13，入门成本及新增项目于 2026-10-14 补查。star 为当时快照，本文只在已核查项目中保留约数，不作为排序分数。近期合入数量窗口为 2026-08-15 至 2026-10-14 查询时点，包括维护者、依赖与 CI，不表示外部新人容量。旧 release、旧 issue、读取失败不能独立证明项目废弃。

<a id="cpu"></a>

## 3. 机器后端与 CPU 编译候选

### 3.1 LLVM / llvm-project

**做什么。** 多组件编译基础设施。对于用户，核心是 `llvm/lib/CodeGen` 和 `llvm/lib/Target`，而不是整个 monorepo。SelectionDAG、GlobalISel 处理目标相关/无关的指令选择与合法化，后续还有寄存器分配、机器指令优化、调度、汇编/目标文件。

**现状。** 主线持续开发，发布版本与开发主线分开。本次读到最新正式 release 为 23.1.3（2026-10-06）；报告中 issue 可能针对 24.0.0git，应固定主线 revision 复现，不能用系统自带旧版行为直接判断。开放新手条目多，但“无人指派”远不等于“无人做”。

**适合进入。** 小 combine、target KnownBits/demanded-bits、一个操作或类型的 legalization、局部误编译和 crash 修复。第一项可以是一个明确边界错误；后续同模块再做优化，形成连续故事。寄存器分配算法、全新目标和大规模调度模型不适合第一项。

**环境与社区。** 编译后端可以在宿主机生成 X86/AArch64/RISC-V 代码；许多 lit/FileCheck 测试不需要运行对应硬件。执行正确性、微架构性能和硬件调度测量则需要相应条件。CMake/Ninja、assertions build 与局部测试是主要门槛。官方新手问题禁止用 AI 工具修复；搜索和学习允许，其他贡献按政策要求人类负责与披露。当前工作仅做搜索、分析和整理。

**简历价值。** 最直接匹配已验证的后端 JD。要能解释失败 IR、处理阶段、合法性和修复后的目标代码；一个拼写修复不具有同等分量。


**实际起步判断。** 构建中到高，局部验证可控。第一闭环可限定在：llc/单target；SelectionDAG/GlobalISel已有错误+lit。主要阻力是：IR/poison/合法化知识；热门GFI占用；性能题需硬件。当前已有两项具体普通候选，仍作为第一主线。

**新人进入证据。** 已核查普通后端 issue 对应的三项新贡献阶段合入 PR，涉及 vector legalization、DAG combine 和 rotate 合法性；新人并不限于 GFI。样本不能证明作者没有任何编译器背景，也不能推出个人成功率。详细过程见 [已合入 PR 分析](llvm-newcomer-merged-pr-analysis-2026-10-14.md)。此前筛出的普通候选尚未在本机复现，应按该文的核查时间和准备步骤使用。

来源：[仓库](https://github.com/llvm/llvm-project)、[贡献指南](https://llvm.org/docs/Contributing.html)、[Code Generator](https://llvm.org/docs/CodeGenerator.html)、[AI 政策](https://llvm.org/docs/AIToolPolicy.html)。

### 3.2 Cranelift（Wasmtime 仓库内）

**做什么。** Rust 实现的机器码编译后端，强调编译速度。CLIF IR、ISLE lowering、目标指令、寄存器分配/机器码发射是真正后端内容；不要与 Wasmtime 的组件模型/API 工作混在一起。

**现状。** 作为 Wasmtime 编译基础设施持续开发，不是独立教学编译器。官方贡献指南明确提供新手标签与 compiler mentoring，公开表达指导新人的意愿。

**适合进入。** 单个 ISLE rewrite、一个目标指令模式、局部 legalization、code emission 修复，先以 filetests 验证。避免把 Wasmtime 文档/接口修复当作后端证据。

**环境与社区。** CPU 即可验证许多任务，Mac/Linux 路线可用；代价是同时学 Rust 和编译器内部。官方明确不接受只改拼写的 trivial PR，因此“先随便合一个”不是合理路线。

**简历价值。** 后端经验很直接；如果 JD 明确偏 LLVM/C++，还需要解释迁移关系，所以当前放在 LLVM 之后。愿意转 Rust 时可以提高优先级。


**实际起步判断。** Rust学习+构建中。第一闭环可限定在：ISLE/target小规则、filetests。主要阻力是：Rust与CLIF、寄存器和target约束同时学习。因此当前取舍为：机器后端替代；不愿转Rust则后置。

来源：[Wasmtime 仓库](https://github.com/bytecodealliance/wasmtime)、[贡献与 mentoring](https://docs.wasmtime.dev/contributing.html)、[Cranelift 源码](https://github.com/bytecodealliance/wasmtime/tree/main/cranelift)。

### 3.3 ISPC（约 3.0k star）

**项目与现状。** C 风格 SPMD 编译器，把 uniform/varying 执行映射到 SIMD，使用 LLVM 优化与目标生成，支持 CPU 与 Intel GPU。查询窗口有 27 个合入 PR，贡献说明明确欢迎 ARM target 工作。

**开始工作是否方便。** C++ 与 LLVM 技能可复用，CPU 题可以不依赖 GPU。但需要匹配 LLVM/相关依赖与语言执行模型，开发构建成本为中到高；使用预编译 ispc 只能复现，不能验证源码修改。

**具体入口。** mask、varying pointer、向量运算 lowering 或一个目标相关 pass 的局部错误。代码生成检查用 tests/lit-tests；涉及语言行为还需 functional tests。源码范围比大型 AI 图编译框架集中。

**实际限制。** 17 个 GFI，最新创建于 2025-02，很多为教程、CMake、CI、stdlib，而非后端。一批条目的最近更新时间同日，不能因此当成重新开放的新工作。本轮未核实一个新的空闲小题，也未完成新人 merge 样本验证。

**判断。** 对 CPU/SIMD 编译岗位相关，值得继续筛普通 optimization/lowering 问题；不因 Intel 名称或 GFI 数量保证上手快。

来源：[README](https://github.com/ispc/ispc)、[贡献和 lit 要求](https://github.com/ispc/ispc/blob/main/CONTRIBUTING.md)。

### 3.4 AsmJit（约 4.6k star）

**项目。** C++ 低延迟机器码生成库，包含 x86/AArch64 emitters、instruction database、Compiler/JIT 层与测试。与底层机器码、寄存器、编码/ABI 有关系，不是完整 LLVM 优化编译器。

**方便处。** 不需构建 LLVM，不需 GPU；CMake 与项目测试可覆盖 encoding、assembler/compiler 输出。相比增加一整套模型 IR，更容易限定一个 emitter/指令信息错误。

**难处。** ISA/编码知识要求高，执行测试要匹配宿主架构。小社区可能由核心维护者直接 push；本窗口未查到已合入 PR，不能据此说停更，但也不能说外部新人 review 很活跃。文档欢迎已完成 bug fix，不保证 feature 请求被接受。

**判断。** 可作熟悉 JIT/机器码工程的备选；当前验证了低构建负担，没有验证稳定的新贡献任务供给，因此不替代 LLVM 主线。

来源：[组织与测试](https://github.com/asmjit/asmjit/blob/master/README.md)、[贡献说明](https://github.com/asmjit/asmjit/blob/master/CONTRIBUTING.md)。

### 3.5 llvm-aie / Peano

**做什么。** LLVM fork 中的 AMD AI Engine target，生成暴露流水线的 VLIW 机器指令；涉及指令选择、bundling、调度与寄存器，是这两个 AIE 仓库中更直接的机器后端。

**现状。** 当前默认分支为 aie-public，2026-10-13 有 push。支持 XDNA/XDNA2 等目标，作为 MLIR-AIE 链路的编译组件。实际 hardware 产品存在不代表所有 fork 改动都已进入 upstream LLVM。

**适合进入。** 一个明确指令模式、MIR verifier/合法化错误、目标局部修复。完整 pipeline hazard/scheduling 功能对新手风险较大。

**环境与社区。** 静态 llc/MIR 测试可以有离线空间，正确执行/性能需要设备或适当模型。ISA、专有约束和 fork 与 upstream 的关系增加背景学习。贡献指南指向 LLVM 政策，没有公开证据足以说它比 upstream 更适合新手。

**简历价值。** 对 DSP/VLIW/NPU 后端技术匹配很好，但如果目标是最小成本形成通用后端经历，仍优先 LLVM 的 AArch64/RISC-V/X86 局部问题。


**实际起步判断。** 中到高/专用知识高。第一闭环可限定在：MIR/指令模式小题。主要阻力是：VLIW/流水线约束与fork、执行验证模型。因此当前取舍为：专项备选，不比upstream LLVM默认简单。

来源：[架构与 README](https://github.com/Xilinx/llvm-aie/blob/aie-public/README.md)、[贡献说明](https://github.com/Xilinx/llvm-aie/blob/aie-public/CONTRIBUTING.md)。

<a id="eda"></a>

## 4. EDA 与 HLS 编译候选

### 4.1 Yosys（约 4.8k star）

**项目与现状。** RTL 综合框架，C++ passes 在 RTLIL 上做优化、变换与技术映射，输出网表。当前还整合 slang/sv-elab 提供 SV 支持。2026-10-13 发布 0.70，查询窗口有 118 个合入 PR。它的相关性在硬件综合后段，而不是 CPU 指令后端。

**开始工作是否方便。** 比从整套 MLIR 张量 pipeline 起步更容易围绕一个 pass 限定输入和输出；普通优化/网表正确性测试不需 FPGA。可先用 OSS CAD Suite 复现，再做源码开发。当前源码已要求 C++20、CMake>=3.28、Python>=3.11、Bison>=3.8 等，并有子模块；不再照旧教程认为随便 make 即可。开发构建成本评为中，验证闭环较聚焦。

**具体入口。** `passes/opt` 的局部边界错误、memory/cell simplification、技术映射保留错误单元等；输入为小 RTL/RTLIL，测试使用 .ys 脚本、选择断言、SAT/equivalence。第一项避开全新综合算法、new techmap 架构、SV parser。

**社区证据。** [PR #6267](https://github.com/YosysHQ/yosys/pull/6267) 修复综合后剩余 `$buf` 的问题，作者自述首次 PR，维护者要求正确修复 opt_clean 根因，最终 API 记录已合入。改动包括实现及 Xilinx/Gowin/opt 三组 .ys 回归。不是“仅修改文档才欢迎新人”，也不是维护者自动接受初始方案。此例已解决，只能学习。

**实际限制。** 复杂/core 变更建议提前讨论；长期老代码与 `z`、undef、wire/cell 语义需要学。YosysHQ 2026-08 的临时 LLM 政策原则不接收 LLM 生成代码的 PR；允许作者能承担解释责任的 AI 辅助，并禁止生成代码注释/提交信息。适合本人主导学习与实现，不按“代理批量生成 patch”理解贡献路径。

**判断。** 对 EDA 求职值得与 CIRCT、Verilator 同组优先筛题。比 Dynamatic 更贴近综合工具生态；工业岗位匹配仍看具体工作，不凭 star 推断。

来源：[README/构建](https://github.com/YosysHQ/yosys/blob/main/README.md)、[完整贡献指南](https://github.com/YosysHQ/yosys/blob/main/docs/source/yosys_internals/extending_yosys/contributing.rst)、[LLM 政策](https://blog.yosyshq.com/p/interim-yosyshq-llm-policy/)。

### 4.2 CIRCT

**做什么。** 基于 MLIR 的硬件编译基础设施，包含 FIRRTL、HW、Comb、Seq、Handshake 等表示及多类 lowering、Verilog emission。它的“后端”主要是硬件/RTL 后端。

**现状。** README 仍明确称项目为实验性，但不能由此推断所有模块都只是研究原型。firtool 有持续发布，本次读到 1.161.0（2026-10-01）；Chisel 官方说明从 v3.6 起使用 CIRCT 的 firtool 生成 Verilog，是可核验的实际集成证据。不同 dialect 的成熟度与维护者覆盖不同。

**适合进入。** Comb 局部变换、位宽/常量折叠、HW/SV emission 的具体错误、一个 lowering 的边界条件。优先已有精简 IR 和清楚期望结果的问题，不从设计新 dialect 起步。

**环境与社区。** LLVM/MLIR 子模块带来较大的构建成本，但 IR 和 emission 的许多测试无需 FPGA。沿用 LLVM 开发政策，模块维护者的意见决定变换是否放在此处。单个 op 的标准折叠比跨 dialect 的重新设计沟通成本更低。

**简历价值。** 对 EDA 编译器、硬件 IR 和 MLIR 岗位很贴近；相比 Dynamatic，有 firtool/Chisel 这条更容易说明的应用链路。仍不能写成 CPU 指令选择经历。


**实际起步判断。** 中到高。第一闭环可限定在：单dialect Comb/HW/SV局部pass与circt-opt测试。主要阻力是：LLVM/MLIR子模块；跨dialect与硬件语义。因此当前取舍为：EDA优先组；只选局部变换，不设计新dialect。

来源：[README](https://github.com/llvm/circt/blob/main/README.md)、[dialect/工具文档](https://circt.llvm.org/docs/)、[Chisel 集成说明](https://www.chisel-lang.org/chisel3/docs/appendix/versioning.html)。

### 4.3 Verilator

**做什么。** 把 Verilog/SystemVerilog 编译为 C++/SystemC 仿真模型，再由 C++ 编译器形成可执行程序。编译器自身涉及 AST、展开、优化、调度和 C++ emission；它不产生芯片实现 RTL，也不直接承担 CPU ISA 的机器后端。

**现状。** 官方 latest 文档当前为 5.052。FAQ 明确描述硅设计企业和 CERN 等用户，工业使用证据比纯学术 HLS 项目充分。本次未通过 GitHub latest-release API 获取版本，版本来源为官方文档，不能把 release API 404 当作停更。

**适合进入。** 某个已有优化 pass 的边界错误、生成 C++ 的正确性或代码质量、位宽/符号处理、一个可精简的 SV 构造。首次避免完整实现复杂 SV/UVM 功能与仿真调度架构变更。

**环境与社区。** CPU 即可运行生成模型；Linux/WSL 是稳妥路径。要补 SV 语义，而你的 C++ 与 EDA 经历可以复用。仅修 parser/诊断也可以贡献，但若为了后段简历，应主动筛优化/生成部分。

**简历价值。** 适合 EDA 仿真编译器和 C++ 优化岗位。能讲清“SV 输入→优化后表示→生成 C++→仿真回归”会比只说熟悉 Verilator 更有价值。


**实际起步判断。** 中。第一闭环可限定在：单优化pass/C++ emission与小SV仿真回归。主要阻力是：SV语义、仿真调度、完整语言功能。因此当前取舍为：EDA优先组；避开完整语言覆盖需求。

来源：[官方概述](https://verilator.org/guide/latest/overview.html)、[FAQ](https://verilator.org/guide/latest/faq.html)、[仓库](https://github.com/verilator/verilator)。

### 4.4 Google XLS

**做什么。** 高层功能描述/DSLX 到 XLS IR，再做优化、pipeline scheduling 和 Verilog/SystemVerilog CodeGen；支持纯函数与有状态 proc。属于硬件合成编译，不是 LLVM ISA 后端。

**现状。** 主线和构建产物持续更新，本次 release 是按提交生成的版本。README 仍明确实验性、非 Google 官方支持产品，DSLX 可以破坏兼容性；“Google 仓库”不能推出广泛工业采用。

**适合进入。** IR 局部优化、bit-level 分析、select/RTL emission 小问题。之前 #490 可作为候选但很旧，需要当前主线复现及确认需求。Scheduling/PPA 优化的验证比表面更重。

**环境与社区。** 建议 Linux x86-64/WSL + Bazel。需要 CLA；官方建议先 issue 讨论，XS/S 是熟悉代码者的估计，不是新人时间。声称 PPA 改善需按项目要求多 seed 综合，不能只报告一个最好看的结果。

**简历价值。** 对 HLS/EDA 后段能形成清楚的优化故事；项目来源较好解释，但不能仅靠 Google 名字。若投一般 LLVM 后端，需要另补机器代码层案例。


**实际起步判断。** 中到高。第一闭环可限定在：单IR rewrite/RTL emission和Bazel target。主要阻力是：DSLX/proc语义、CLA、事前讨论；PPA多seed综合。因此当前取舍为：明确HLS岗位与小题时选。

来源：[README](https://github.com/google/xls/blob/main/README.md)、[贡献/PPA 要求](https://github.com/google/xls/blob/main/CONTRIBUTING.md)。

### 4.5 Dynamatic

**做什么。** MLIR 驱动的动态调度 HLS，C/C++ 经多级 lowering 变为 Handshake 数据流电路与 RTL，优化方向包括内存依赖、buffer placement、位宽。

**现状。** EPFL/ETH Zurich 学术开源项目，当前主线仍更新；本次 GitHub latest 正式 release 是 2024 年的 2.0.0，但不能据此判断 2026 年代码停滞。2026 年团队有 MLIR/HLS 经验论文，科研定位清楚。这轮没有足以证明广泛工业产品采用的公开证据；与 Vivado/Modelsim 集成不等于厂商采用。

**适合进入。** #148 标准 canonicalization 接入可学工程框架，#818 backward bitwidth 是更有实质性的优化候选；之前已核查公开认领状态，但实际开始时仍需刷新。首次避免新动态调度机制、求解器/形式化框架大变更。

**环境与社区。** 建议 Linux/WSL，普通 IR/pass 测试与完整综合/QoR 流程分开。学术社区可能提供更细的项目任务，但目前没有证明 review 比 LLVM 更快；任务可切入不等于维护沟通必然轻。

**简历价值。** 做扎实的位宽正确性与 RTL 验证可以写；#148 单一重构的分量有限。面试官可能不认识项目，需说明编译链路；泛机器后端岗位不能用它替代指令选择经历。


**实际起步判断。** 中到高。第一闭环可限定在：Handshake canonicalization/局部bitwidth lit。主要阻力是：MLIR、不同编译层、完整QoR/求解器流程、学术项目解释。因此当前取舍为：有具体题是优点；不替代机器后端主线。

来源：[README](https://github.com/EPFL-LAP/dynamatic/blob/main/README.md)、[EPFL 学生项目](https://www.epfl.ch/labs/lap/available-student-projects-at-lap/)、[2026 论文](https://arxiv.org/abs/2603.19856)。

<a id="ai"></a>

## 5. AI、张量与异构编译候选

### 5.1 IREE

**做什么。** 基于 MLIR 的端到端模型编译器与运行时。包含张量/循环变换、dispatch、CPU/GPU CodeGen、HAL 和 VM/runtime。选择 LLVMCPU/CodeGen 的问题，比随意修模型导入更贴近目标。

**现状。** 持续开发，提供稳定/夜间包，属于 LF AI & Data Foundation。当前贡献指南列出了 TSC 和维护流程；README 链接 AMD 用 IREE 实现 SDXL 并提交 MLPerf 的案例，是实际使用证据，不应把它只描述成早期 Google 实验。模块与设备覆盖仍然不同。

**适合进入。** CPU lowering、向量化边界、buffer/dispatch 合法性、一个局部变换的 crash 或 miscompile。不要从“支持完整模型”开始，也不要把只修运行时接口写成 CodeGen 经历。

**环境与社区。** 官方有 macOS arm64/Linux CI，CPU 路线适合现有设备；GPU 性能题另需目标硬件。MLIR 和多阶段 pipeline 是主要学习成本。社区渠道清楚，但没有从有限样本推出新人合入速度。

**简历价值与取舍。** 能补 AI lowering、向量化与生成代码经历，但一般不涉及 LLVM 寄存器分配。当前不再作为默认容易起步的 AI 备选：先确认一个未被占用、可以在 CPU 验证的 CodeGen 小题，再投入开发环境。


**实际起步判断。** 中到高。第一闭环可限定在：CPU CodeGen 的精简MLIR和局部lit。主要阻力是：多层pipeline、标签陈旧、新题已有认领；需筛普通issue。因此当前取舍为：从默认“易启动”降为拿到具体小题后再选。

**任务与指导的实际证据。**

准确标签为 `good first issue 🌱`，不能用不带 emoji 的标签查询得到 0 后判断没有入口。完整查询得到 **27 个开放条目**，其中 **23 个创建超过一年、14 个超过三年、8 个正式指派**。创建日期与最近更新时间分开看；用户留言或自动事件更新不表示问题重新成为可领取任务。

同一窗口内有 **129 个已合入 PR**，并且有当前 Stream/CodeGen 等修改。因此不能说 IREE 整体被废弃。更准确的描述是：**技术路线活跃、具备新人指导，但入门任务清单未形成持续的小任务队列；起步需要先筛题，而非从 GFI 直接挑一个。**

几个具体检查：

| Issue | 现状与含义 |
| --- | --- |
| [#24732](https://github.com/iree-org/iree/issues/24732) LLVMCPU scalable tile selection | 2026 年新题，作者 gxyd 自述新到 IREE，维护者持续解释 pipeline、SVE/SME 前提，是真实指导证据。当前已有指派与开放 PR #24975，不能推荐用户领取；内容也不是低背景知识任务 |
| [#24688](https://github.com/iree-org/iree/issues/24688) Vulkan default target | 页面无关联 PR，但维护者评论说明已有 draft PR，并有人表示开始工作；明确提醒重复风险。按用户要求排除，而不是因为无 assignee 推荐 |
| [#23554](https://github.com/iree-org/iree/issues/23554) Kokoro-TTS 编译失败 | 需要进入 ONNX/Torch STFT 导入与模型 pipeline；不是一个简单 CPU 后端 bug 的清晰入口 |
| [#23210](https://github.com/iree-org/iree/issues/23210) gfx1100 matmul lowering | 有展开策略和实验讨论，需要 AMD 目标知识与适当执行/性能验证，不适合无相应设备时第一项 |
| [#3859](https://github.com/iree-org/iree/issues/3859) liveness 迁移 | 旧认领和历史实现/接口讨论，仍需主线重新确认；不默认为空题 |
| [#5547](https://github.com/iree-org/iree/issues/5547) loop range folding | 上游曾实现，之后遇到误编译；原小题已变成历史遗留问题。开放状态不表示原方案仍可直接做 |

**调整建议：** IREE 保留为 AI/MLIR 学习和贡献方向，但从“默认容易起步的 AI 主备选”调整为“拿到清晰 CPU CodeGen 小题之后再启动”。官方也建议 substantial work 前先沟通，以免重复与设计分歧。这种工程门槛与维护者是否友善是两回事。

来源：[README](https://github.com/iree-org/iree/blob/main/README.md)、[贡献说明](https://github.com/iree-org/iree/blob/main/CONTRIBUTING.md)、[开发文档](https://iree.dev/developers/)。

### 5.2 Halide

**做什么。** 面向图像和数组计算的 DSL，区分算法表达与 schedule，处理循环、向量化、存储和目标代码生成，支持 CPU、多类 GPU API。C++ 嵌入式接口与你的工程语言匹配。

**现状。** 成熟而持续维护，当前 README 支持 X86/ARM/RISC-V 等与 macOS/Linux；本次 GitHub latest release 返回 v21.0.0（2025-09-16），同时仓库 2026 年仍在更新，所以 release 间隔不是停更证据。

**适合进入。** Simplify、边界/范围分析、向量化、局部 CodeGen 正确性。已有 CPU reproducer 的问题较易独立验证。GPU 特定速度优化与 autoscheduler 改进不要作首项。

**环境与社区。** Mac/CPU 可以起步，CMake 工程相对聚焦。贡献指南要求新人先 issue/discussion 对齐；通常一个工作周内 review 是其公开目标而非保证。你不喜欢沟通成本，因此选择已有明确需求的 issue，避免先设计大改动。

**简历价值。** 能形成扎实的循环/向量化优化案例；对一般 LLVM 后端岗位略间接，对图像/数值/AI 编译岗位更直接。


**实际起步判断。** 中。第一闭环可限定在：Simplify/边界分析/CPU CodeGen局部测试。主要阻力是：schedule/vector/storage语义；新人需先讨论。因此当前取舍为：可控备选；采用现有需求减少沟通。

来源：[README](https://github.com/halide/Halide/blob/main/README.md)、[贡献指南](https://github.com/halide/Halide/blob/main/CONTRIBUTING.md)。

### 5.3 Apache TVM

**做什么。** 模型/张量编译框架，当前设计强调 Relax 与 TensorIR 的跨层优化和 Python-first 定制，同时有 C++ 分析/变换与目标 CodeGen。

**现状。** 本次 release 为 v0.27.0.post1（2026-09-29）。主线 README 明确已多次重构，当前设计与早期不同；不应照旧教程以 Relay 作为整个当前架构的主线。

**适合进入。** TensorIR 算术简化、边界/索引分析、具体 lowering/CodeGen 错误。Python 层贡献也可能是实质 compiler pass，但 runtime 包装/API 修复与后端相关性不同。

**环境与社区。** CPU 可起步，GPU 专项仍需硬件。框架范围大、跨 Python/C++、旧教程容易偏离主线。采用 Apache 社区模式，重设计需要讨论。没有明确小题时，搭完整模型端到端流程容易耗时且缺乏自己的技术贡献。

**简历价值。** AI 编译相关性高；对机器指令后端间接。选一个分析/变换模块持续贡献，胜过泛泛写“熟悉 TVM”。


**实际起步判断。** 中到高。第一闭环可限定在：TIR/arith/CPU CodeGen小模块。主要阻力是：Relax/TIR/Python/C++跨度，旧教程，重设计讨论。因此当前取舍为：题目驱动，不从完整模型部署开始。

来源：[当前 README](https://github.com/apache/tvm/blob/main/README.md)、[Relax 文档](https://tvm.apache.org/docs/deep_dive/relax/index.html)、[贡献指南](https://tvm.apache.org/docs/contribute/)。

### 5.4 TileLang

**做什么。** 以 tile 为抽象编写高性能 kernel，围绕 TVM 技术栈进行布局推导、循环/线程映射、同步和多设备代码生成。编译器 bug 与仅实现一个 kernel 是不同经历。

**现状。** 本次 release 为 v0.1.15（2026-09-30）。当前 README 已呈现 TileLang-X 多后端架构：CUDA 为 Primary，HIP、Ascend 950、Apple Metal 为 Supported，LLVM CPU 为 Experimental；一些国产设备适配在独立生态仓库。不能继续用早期“只支持 CUDA/AMD”的印象评估。

**适合进入。** layout inference、循环绑定、cast/guard preservation、CodeGen 的小边界错误。优先可以用一个小 kernel 和现有测试验证的题。只调 GEMM 参数或搬运示例不一定构成编译器经历。

**环境与社区。** 若你的 Mac 是 Apple silicon，Metal 路线现在有现实空间；这不意味着能在 Mac 验证 CUDA/TMA/WGMMA。CPU 后端仍实验性，不适合作为所有 GPU bug 的替代验证。贡献指南提供 `♥ help` 标签和明确测试/格式工作流；标签本身不保证未认领。

**简历价值。** 对 AI kernel/compiler 岗位贴近。如果坚持机器码后端，它通常止于生成设备源代码/IR，不能替代指令选择经验。具备匹配设备时优先级明显上升。


**实际起步判断。** 匹配设备时中。第一闭环可限定在：layout/guard/loop的小kernel和现有pytest。主要阻力是：必须验证对应CUDA/HIP/Metal；CPU后端实验性。因此当前取舍为：Apple silicon Metal题可选；不能验证CUDA专属行为。

来源：[README 与 backend 表](https://github.com/tile-ai/tilelang/blob/main/README.md)、[贡献指南](https://github.com/tile-ai/tilelang/blob/main/CONTRIBUTING.md)。

### 5.5 Triton

**做什么。** 面向深度学习 kernel 的语言与编译器，使用 MLIR/LLVM 技术，涉及 layout、共享内存、warp/线程映射、lowering 与设备代码生成。

**现状。** 主线持续发布，本次正式 release 为 3.8.0（2026-08-28）。XLA 官方架构文档也明确使用 Triton 作为部分 GPU fusion 的 CodeGen 层，实际生态关联清楚。

**适合进入。** 有精简 reproducer 的布局转换、类型/索引边界、单个 lowering 错误。第一项不要做新 GPU 架构支持或复杂 tensor-core pipeline。

**环境与社区。** IR 层测试有离线空间，但 GPU 执行与性能题需要适配设备和软件栈。贡献指南明确说维护者可优先自己的工作，外部贡献者不应预期 prompt review。对你低沟通成本、从简单开始的要求，这是实际减分项。

**简历价值。** AI GPU 编译器相关性很高；没有硬件却只完成静态路径，容易在面试追问正确性/性能时出现证据缺口。已有 GPU 和清楚小题时再上调。


**实际起步判断。** 中到高。第一闭环可限定在：编译IR/单lowering、GPU小kernel。主要阻力是：GPU与驱动、layout/warp语义；公开不承诺及时review。因此当前取舍为：有设备和具体bug才优先。

来源：[README](https://github.com/triton-lang/triton/blob/main/README.md)、[review 政策](https://github.com/triton-lang/triton/blob/main/CONTRIBUTING.md)、[XLA GPU 架构](https://openxla.org/xla/gpu_architecture)。

### 5.6 Triton-CPU

**做什么。** Triton 的长期实验 CPU 后端分支，争取把非 CPU 专属改动上推主线。支持在 CPU 上运行 Triton 程序。

**现状。** README 明确为 experimental/work in progress；本次有 v3.8.0+cpu 发布（2026-09-22）。所以不能说“没有发布/没人维护”，也不能把它当作与主线 GPU 同样成熟。

**适合进入。** CPU lowering、向量化或一个算子的局部合法性问题，先跑 CPU examples 与相关测试。分支差异/上游 API 变化也会形成额外工作。

**环境与社区。** 不依赖 GPU 是优点；先选择官方构建能覆盖的 Linux CPU 环境。不要未经核查保证所有 Mac CPU 情况都可运行。贡献说明沿用了 Triton 的流程，不能自动承诺新人更易合入。

**简历价值。** 能证明 AI 编译到 CPU 的能力；认可度需要解释“是实验后端分支，具体贡献在哪”，弱于直接 Triton 主线品牌的等同表述。


**实际起步判断。** 中到高。第一闭环可限定在：CPU lowering、向量化、CPU tests。主要阻力是：实验分支与上游变化；并非所有Mac配置都已验证。因此当前取舍为：不为回避GPU就默认容易。

来源：[README](https://github.com/triton-lang/triton-cpu/blob/main/README.md)、[贡献说明](https://github.com/triton-lang/triton-cpu/blob/main/CONTRIBUTING.md)。

### 5.7 OpenXLA / XLA

**做什么。** 对框架计算图进行 HLO 优化、fusion、layout、buffer assignment，再使用 LLVM/native emitters/Triton 等生成 CPU/GPU 可执行内容。用户应选实际 CodeGen 部分，不是随意一个模型支持问题。

**现状。** 当前 README 和官方文档说明与 JAX、TensorFlow、PyTorch/XLA 等集成；主线活跃，工业使用背景明确。本次 release API 限流，不把“没有读取到版本”写成“无正式发布”。

**适合进入。** 单个 CPU emitter、已有 HLO 模式的局部错误、clear-cost/shape 前提下的具体优化。新增完整 backend、复杂 fusion 策略不适合首项。

**环境与社区。** Bazel 与庞大依赖栈、HLO→后端多阶段上下文增加起步成本。CPU 路线有可行空间，GPU 性能另需设备。贡献点必须落在公开、能独立验证的路径上。

**简历价值。** 对 AI compiler 强相关，但“项目强”并不等于“首次贡献划算”。只有清楚的小 issue 才值得优先启动，不为品牌搭半个完整栈。


**实际起步判断。** 高。第一闭环可限定在：极小CPU emitter/HLO局部测试。主要阻力是：Bazel依赖、buffer/fusion多模块；GPU实测。因此当前取舍为：不作为首次贡献默认项目。

来源：[README](https://github.com/openxla/xla/blob/main/README.md)、[官方架构](https://openxla.org/xla/architecture)、[GPU 架构](https://openxla.org/xla/gpu_architecture)。

### 5.8 rocMLIR

**做什么。** 针对 AMD GPU 的 MLIR kernel generator，当前覆盖 GEMM、convolution、attention 等，经过 rock、amdgpu/rocdl 到 LLVM AMDGPU 后端。

**现状。** 当前 README 明确主要作为 `librockCompiler` 被 MIGraphX 使用，也可 standalone 生成/验证/调优；2026-10-09 有仓库 push。技术定位比“泛 MLIR 项目”具体，但不能把其贡献自动等同 LLVM AMDGPU 后端贡献。

**适合进入。** rock lowering、布局/索引合法性、具体 kernel 生成错误。IR 回归可以是入门，但性能主张必须执行目标 kernel。

**环境与社区。** README 把 AMD GPU/ROCm 列为前置条件。静态测试是否可不带 GPU 构建要按具体目标验证，不能提前保证。当前贡献指南很具体，要求针对 develop、回归测试与 CI；沿用 LLVM AI 政策。

**简历价值。** 若目标明确为 AMD GPU/ROCm compiler 很相关；你尚未提供对应硬件信息，因此当前后置，迁移 Linux 本身不解决 GPU 缺失。


**实际起步判断。** 高/设备条件。第一闭环可限定在：rock IR变换。主要阻力是：AMD/ROCm；实测kernel；专用布局。因此当前取舍为：暂无设备信息，后置。

来源：[README](https://github.com/ROCm/rocMLIR/blob/develop/README.md)、[贡献指南](https://github.com/ROCm/rocMLIR/blob/develop/CONTRIBUTING.md)。

### 5.9 AdaptiveCpp

**做什么。** 原 hipSYCL/Open SYCL，支持 SYCL、C++ parallelism 和实验 PCUDA，使用 LLVM 编译与异构 runtime/JIT 跨 CPU/GPU。这里同时有 compiler 和普通 runtime 工作，需仔细划分。

**现状。** 当前 develop 活跃；README 展示多厂商 CPU/GPU 与 Apple 支持，但每种编程模型/编译流成熟度不同。不能拿支持某设备概览保证某 issue 能在用户 Mac 重现。

**适合进入。** SSCP/LLVM passes、设备 IR 转换、一个编译错误或小优化。runtime scheduling、安装、API compatibility 贡献也有价值，但不能承担本次后端目标。

**环境与社区。** C++ 经历可复用，需学 SYCL 和 host/device 编译关系。CPU 可验证部分路径，设备问题按后端配置核查；项目建议不确定时先讨论。构建 LLVM 插件和多编译流容易分散注意力。

**简历价值。** 对异构/HPC compiler 相关，对传统机器指令后端较间接。明确目标公司采用 SYCL/LLVM 时上调，否则先于本项目考虑 LLVM，或已有清晰 CPU CodeGen 小题的 IREE。


**实际起步判断。** 中到高。第一闭环可限定在：CPU/SSCP compiler pass局部修复。主要阻力是：SYCL host/device、多编译流；容易落到runtime。因此当前取舍为：JD涉及异构编译时选。

来源：[README](https://github.com/AdaptiveCpp/AdaptiveCpp/blob/develop/README.md)、[贡献指南](https://github.com/AdaptiveCpp/AdaptiveCpp/blob/develop/CONTRIBUTING.md)。

### 5.10 MLIR-AIE / IRON

**做什么。** 为 AMD AI Engine 阵列表达 tile placement、ObjectFIFO、DMA 和 stream connectivity，当前对外入口强调 IRON Python API 和 Ryzen AI NPU 编程。

**现状。** AMD 维护，最新读取 release v1.4.4（2026-10-06）；README 明确与 Ryzen AI Software Platform 互补，而非替代。它通过 Peano 编译 core 程序，不能把 MLIR-AIE 本身称为全部 AIE 指令后端。

**适合进入。** ObjectFIFO lowering、buffer/DMA 合法性、tile 资源分配的局部错误、设备配置 emission。运行 notebook/示例不足以构成编译器贡献。

**环境与社区。** 部分 IR 测试可离线，端到端需支持的 Ryzen AI/Versal、驱动和 runtime。Mac/WSL/Linux 的选择不能替代硬件要求。贡献指南清楚，但特定设备语义学习与验证成本较高。

**简历价值。** 对 NPU 编译、数据搬运和空间映射岗位强，对泛 LLVM backend 需要解释差异。只有目标 JD 和设备都匹配时作为主线。


**实际起步判断。** 设备条件高。第一闭环可限定在：离线资源/DMA/IR合法性。主要阻力是：RyzenAI/Versal设备、驱动、阵列模型。因此当前取舍为：有具体设备和岗位才选。

来源：[README](https://github.com/Xilinx/mlir-aie/blob/main/README.md)、[贡献指南](https://github.com/Xilinx/mlir-aie/blob/main/CONTRIBUTING.md)。

### 5.11 PyTorch / TorchInductor（整仓库约 104.9k star）

**项目。** 不把 PyTorch 整仓库当候选，只看 `torch/_inductor` 中 FX graph lowering、scheduler、fusion、CPU C++/GPU Triton CodeGen。Dynamo capture、operator/kernel、runtime 工作不能混算。

**开始工作。** CPU 题可利用现有设备；需要 Python、PyTorch compiler 内部、源码开发环境，生成 C++ 的经验也可关联后段。PyTorch 本体编译/版本依赖很大，不能因为主体 pass 是 Python 就认定环境简单。

**实际入口。** `test/inductor` 中可复现的局部 CPU CodeGen/调度正确性；避免从完整模型、CUDA 特定 fusion 起步。GFI 与 module:inductor 交集仅 2 项，一项是长期 tracking issue，另一项还标 internal ramp-up task；不等于有两个外部新人空题。

**判断。** AI compiler 岗位值得作为模块级候选；若目标主要是 LLVM machine backend，相关性弱一些。没有精简普通 issue 前不启动整库。

来源：[仓库](https://github.com/pytorch/pytorch)、[PyTorch 2 架构论文](https://pytorch.org/assets/pytorch2-2.pdf)、[贡献说明](https://github.com/pytorch/pytorch/blob/main/CONTRIBUTING.md)。

### 5.12 ExecuTorch（约 5.1k star）

**项目与现状。** PyTorch 模型 export/lowering、memory planning、backend delegates 与 edge runtime，窗口有 1289 个合入 PR。许多工作是 vendor 内部、CI、kernel/runtime，不能用这个数量表示外部 compiler 任务特别多。

**开始工作。** 官方有 New Contributor Guide 与局部 pytest 路径；EXIR verifier/memory-planning 的 Python 题比完整 vendor delegate 更可控。修改 C++ runtime/自定义 op 需编译，delegate 还可能需要专用 SDK/设备；普通 wheel 使用不是源码开发闭环。

**社区证据。** [PR #10617](https://github.com/pytorch/executorch/pull/10617) 修改 memory-planning verifier 与测试，已合入；讨论指出测试库依赖、pytest ignore 与红 CI，耗时约 56 天。不是“两个 Python 文件所以无需环境/沟通”。release 中有 first-time contributors 是总体开放性证据，不证明他们都做 compiler。

**实际限制。** 需 CLA，贡献说明要求有 issue 时先 claim。GFI 很多属于 Android/JNI/CMake/examples；筛题要限 EXIR/partitioner/lowering，不以部署示例换编译器简历。

**判断。** AI/端侧岗位有价值，对直接 ISA backend 间接。明确 EXIR 小题时可起步，不能笼统评为“最简单”。

来源：[贡献说明](https://github.com/pytorch/executorch/blob/main/CONTRIBUTING.md)、[README](https://github.com/pytorch/executorch)。

<a id="other"></a>

## 6. 其他具有真实编译器核心的候选

### 6.1 Binaryen（约 8.7k star）

**项目与现状。** Wasm 优化器与 compiler/toolchain library，以自己的 IR 和 `wasm-opt` passes 为核心，不是机器 ISA 后端。窗口有 190 个合入 PR，最近还有 ConstraintAnalysis、subtype、global 优化修复。

**开始工作是否方便。** C++20、CMake/Ninja、Python>=3.10；不要求构建 LLVM，不需要 GPU/FPGA。小 .wat/.wast 输入可直接运行指定 pass，配合解释器/验证和 lit/FileCheck；部分套件另需 node/emcc，但不能把全部工具的依赖都算在一个普通 pass 首项上。初次构建仍需时间，依赖结构比 LLVM/MLIR 全栈轻。

**具体入口。** 局部 simplification、MemoryPacking、控制流/类型变换边界，选已有 pass 的错误或 missed optimization。不要先实现新的 Wasm proposal 或全局类型推理策略。

**社区证据。** [PR #8834](https://github.com/WebAssembly/binaryen/pull/8834) 作者明确称首次 Binaryen 贡献，维护者 tlively 给出 review 并批准；实际修改 MemoryPacking 与两份 lit 回归，2026 年合入。这证明优化代码的外部入口。此题来自旧的入门线索，说明旧日期需要确认，不能直接等于无价值。

**实际限制。** 当前 `good first bug` 只有 6 个开放条目，而且全部创建于 2023 年或更早；它没有“源源不断且没人抢的新手题”。推荐理由是环境与测试闭环，而不是标签更新更好。Wasm/GC/ref 类型语义也可能让看似几行的代码很难。

**判断。** 如果首先追求学习真实编译变换、完成可验证 C++ patch，值得保留；如果 JD 点名 LLVM ISA 后端，仍排在 LLVM 之后。简历写 Wasm IR 优化，不写寄存器分配。

来源：[README 的 build/testing](https://github.com/WebAssembly/binaryen/blob/main/README.md)。

### 6.2 Numba（约 11.2k star）

**项目与现状。** Python/NumPy JIT，通过 llvmlite 生成 LLVM IR；typing、typed IR、inlining、parallel transforms 与 lowering 分层。窗口有 67 个合入 PR。

**开始工作。** 官方推荐预编译 llvmlite/NumPy 的独立环境，再 build_ext 与局部 unittest，通常不用从头构建 LLVM。CPU 任务依赖负担较可控；版本配对和完整跨平台 CI 仍有成本。

**社区证据。** [PR #10637](https://github.com/numba/numba/pull/10637) closure inlining 的 silent miscompile 修复已合入；维护者明确祝贺作者首次贡献，并要求增加条件分支负例。可以贡献实质 IR 工作，而非只有文档。

**实际限制。** 很多 GFI 是多年前的 NumPy/CUDA 功能请求，不是现代小任务队列；官方解释有限 reviewer/CI 资源导致优先级排队。若只做 typing/NumPy overload，偏前端/库支持。应限制在 typed IR、parallel pass、LLVM emission；CUDA 路线还要检查当前独立 numba-cuda 项目分工。

**判断。** 便捷环境与真实 compiler 贡献兼顾的备选，但 Python/NumPy 领域与你既有 EDA/C++ 经历衔接弱于 LLVM/Yosys。

来源：[贡献与开发环境](https://numba.readthedocs.io/en/latest/developer/contributing.html)、[README](https://github.com/numba/numba)。

### 6.3 Shader Slang（约 5.7k star）

**项目与现状。** `shader-slang/slang` 是 shader 编译器，与 SystemVerilog 的 `MikePopoloski/slang` 完全不同。自有 IR、模块特化、自动微分，输出 SPIR-V/DXIL/CUDA/Metal/CPU 等。窗口有 339 个合入 PR。

**开始工作是否方便。** 贡献指南有完整 CMake 构建、submodules、`slang-test` 和平台配置流程。某些编译输出/IR 测试不需要运行 GPU；完整 GPU 测试需要 SDK/驱动与设备。成本为中到高，不能用“支持 CPU”代替一个 GPU 错误的执行验证。

**具体入口。** 小 IR 变换、SPIR-V/目标文本 emission、类型/布局正确性。新增自动微分机制或整套 target 支持不适合第一项。

**实际限制。** 有 CLA；`GoodFirstBug` 当前 6 个，其中 4 个正式指派，剩余也需读评论/PR；不是现成无认领任务池。项目认可度更偏 GPU/shader，不能自动等同 AI 图编译或 EDA 经历。

**判断。** 若拓展 GPU compiler，可以保留，比纯 kernel 仓库更有编译器核心；不是当前 EDA 主选。

来源：[README](https://github.com/shader-slang/slang/blob/master/README.md)、[贡献/测试](https://github.com/shader-slang/slang/blob/master/CONTRIBUTING.md)。

### 6.4 Codon（约 16.9k star）

**项目。** 面向 Python 风格程序的原生编译器，包含自己的 IR、变换和 LLVM IR 生成，可看到目标代码。当前获取到 LICENSE 为 Apache 2.0，不能沿用旧 BSL 印象。

**开始工作。** 用 release 较容易复现；修改 compiler 需源码、匹配 LLVM/依赖和 C++ 构建，成本中到高。测试为 Codon 程序，贡献说明要求必要时在 test/main.cpp 注册，PR 对 develop，而不是默认 master。

**实际限制。** 贡献指南明确 review throughput limited，本轮准确 GFI 查询为 0；未查出近期新人的局部 CodeGen 合入样本。不把高 star 当作可方便开始的证据。类型/标准库/语法修复又可能落回前端。

**判断。** 值得作为 LLVM IR/pass 路线观察项目，不在有明确空题之前投入整套构建。

来源：[README](https://github.com/exaloop/codon/blob/master/README.md)、[贡献指南](https://github.com/exaloop/codon/blob/master/CONTRIBUTING.md)、[LICENSE](https://github.com/exaloop/codon/blob/master/LICENSE)。

<a id="additional"></a>

## 7. 另外六个候选：有技术价值，但当前不优先

### 7.1 Taichi（约 28.4k star）

**定位与价值。** C++/LLVM 支撑的计算 DSL，包含 IR、优化与 CPU/GPU 后端，技术上确实可以做编译器贡献，不应归为纯 kernel 库。

**现状。** 本次近两个月窗口未查到合入 PR；按创建时间检索到的最近合入样本来自 2025-07。GFI 很多创建于 2020–2022，贡献文件还保留 LLVM 10 的旧说明。这些是当前外部贡献入口的风险信号，不足以断言整个项目废弃。

**新手友好度与取舍。** 需要源码 C++/LLVM 构建与 DSL/IR 知识，GPU 题另需设备。旧开发文档、任务清单和当前 review 状态首先需要重新确认；这会产生你希望避免的沟通成本。暂缓，除非出现近期仍受维护、可以独立验证的 compiler 小题。

来源：[官方仓库与贡献文件](https://github.com/taichi-dev/taichi)。

### 7.2 Swift（约 70.5k）

**定位与现状。** 成熟语言工具链；SIL optimizer、IRGen 和 LLVM 衔接能形成真实 compiler 经历。仓库声誉和关注度很高，但不是新人任务可用性的证明。

**新手友好度。** C++ 可复用；需要学习 Swift/SIL 语义，工具链 checkout、构建和测试涉及多个组件。应先看单个 SIL pass 的局部测试是否可以闭环，而不是尝试完整发行工具链。本轮未核实具体空闲小题或首次贡献的合入样本，因此不能据成熟文档承诺起步方便。

**取舍。** 若岗位点名 Swift 编译器可上调。当前为了补一般后端经历，没有充分理由先承担另一套语言语义与工具链成本。

来源：[官方仓库](https://github.com/swiftlang/swift)、[构建与开发入口](https://github.com/swiftlang/swift/blob/main/docs/HowToGuides/GettingStarted.md)。

### 7.3 Rust compiler / rustc（约 119.9k）

**定位与现状。** 成熟语言编译器，MIR 优化、LLVM CodeGen 等是实质编译工作；底层 ISA 后端很多仍由 LLVM 承担。不能把任何 rustc patch 都归入机器后端。

**新手友好度。** 有系统开发指南与 bootstrap 测试流程，但你同时要学 Rust、rustc 内部与构建体系。首次优先一个明确 MIR/CodeGen 错误和现有局部测试，避开 trait/type-system 与大范围 bootstrap 改造。本轮没有认证具体未认领任务，也未核查对应新人 review 样本。

**取舍。** 愿意转 Rust 或目标岗位明确时可选；想学 Rust 的直接机器后端，Cranelift 的技术范围相对更聚焦。当前 LLVM/C++ 路径更能复用已有基础。

来源：[官方仓库](https://github.com/rust-lang/rust)、[rustc 开发指南](https://rustc-dev-guide.rust-lang.org/)。

### 7.4 torch-mlir（约 1.9k）

**定位与现状。** 正确仓库为 `llvm/torch-mlir`，属于 LLVM Incubator，负责 PyTorch/ONNX 到 MLIR 的桥接与 lowering。不能用旧命名空间的 star 或官方 LLVM release 状态判断它。

**新手友好度。** 熟悉 MLIR 可以复用，但 LLVM 子模块、PyTorch/nightly 版本配对和源码构建带来中到高成本。局部 lowering 的精简 IR 测试较可控；完整模型导入不宜作为第一项。贡献内容常靠近导入/前端，需逐题区分。本轮没有核实可领取的小题与新人合入通路。

**取舍。** 目标是框架导入/MLIR lowering 时有价值；你不优先前端，因此排在 CPU CodeGen 与 EDA 后段之后。

来源：[官方仓库](https://github.com/llvm/torch-mlir)、[开发说明](https://github.com/llvm/torch-mlir/blob/main/docs/development.md)。

### 7.5 SystemVerilog slang（约 1.2k）

**定位与现状。** `MikePopoloski/slang` 是 C++ SystemVerilog parser/elaborator，与 Shader Slang 不同。已有 Yosys 集成，作为 HDL 前端有明确应用链路。

**新手友好度。** CMake 与单元测试使局部开发范围较清楚，不需 FPGA；SV 类型、展开和语言语义可能是实质门槛。贡献指南建议复杂工作先讨论，普通局部 bug 不应由此被理解为必须等待立项。本轮未核查具体新手合入样本或空题。

**取舍。** 工程入口值得了解，但主体是前端，不能直接补你最需要的后段经历。若修的是综合链路问题，也应清楚写出其发生在前端/展开阶段。

来源：[官方仓库与开发指南](https://github.com/MikePopoloski/slang)。

### 7.6 Icarus Verilog（约 3.7k）

**定位与现状。** Verilog/SystemVerilog 编译到仿真 bytecode/netlist；有真实 C++ 编译、优化与生成工作，不只是解释脚本工具。

**新手友好度。** CPU 即可做许多回归，C++/EDA 基础可复用；源码构建和已有测试的学习成本仍要验证。大量任务属于语言覆盖、解析与展开，不能从 issue 总数推断后段小题充裕。本轮未查到足够新人 review 样本，不能承诺其沟通成本更低。

**取舍。** 有明确 code generation/优化小题时可以补入 EDA 备选；目前没有理由放在已经较贴合的 Verilator/Yosys 之前。

来源：[官方仓库与构建说明](https://github.com/steveicarus/iverilog)。

<a id="deferred"></a>

## 8. 相邻项目与暂缓原因

以下项目没有被验证为当前后端贡献主线。部分十分活跃，后置主要是任务性质或贡献入口不符，而非项目质量。

| 项目 | star 快照 | 检查结果与定位 |
| --- | ---: | --- |
| [Zig（旧 GitHub repo）](https://codeberg.org/ziglang/zig) | 43.3k | README 明确迁到 Codeberg且不是镜像。旧 GitHub issue/PR/star不能表示当前贡献入口。官方仍是编译器候选，但要重新查 Codeberg 与 Zig 语言成本，本轮后置 |
| [Modular](https://github.com/modular/modular) | 29.9k | 当前 README 明确暂不接受 Mojo compiler 贡献，主要接受 stdlib/MAX kernels/pipelines。不能把在此合入一个 kernel/stdlib patch写成修改 Mojo 编译器后端 |
| [Chisel](https://github.com/chipsalliance/chisel) | 4.8k | Scala 硬件描述/生成入口；RTL compiler 后段在 CIRCT/firtool。对用户优先筛 CIRCT，不为高关注度去重学 Scala 主体 |
| [旧 FIRRTL](https://github.com/chipsalliance/firrtl) | 0.75k | GitHub已归档，README称 maintenance mode并指向CIRCT，不作为新主线 |
| [llama.cpp / ggml](https://github.com/ggml-org/llama.cpp) | 131.1k / 15.5k | 推理runtime与tensor/kernels非常活跃；多数贡献是算子、量化、设备执行，不是通用 compiler pass/ISA backend。目标改成推理优化才上调 |
| [ncnn / MNN](https://github.com/Tencent/ncnn) | 24.0k / 16.2k | 可做图优化、converter、设备kernel，但很多 backend 工作是执行实现。避免只因C++和backend名称就替代编译器经历 |
| [ONNX Runtime](https://github.com/microsoft/onnxruntime) | 22.1k | graph optimization/EP partitioning与AI部署相关，普通ExecutionProvider/kernel贡献不是机器后端。设备SDK与runtime栈另有成本 |
| [OpenROAD](https://github.com/The-OpenROAD-Project/OpenROAD) | 3.2k | 实际EDA C++工具，但重点是布局布线/物理设计算法，不是当前要补的compiler后端；若求职改成物理设计软件可重新评估 |
| [GCC / V8](https://gcc.gnu.org/contribute.html) | 未用镜像星数排名 | 后端技术价值高，但GitHub mirror不是普通GitHub PR贡献入口；邮件/其他review平台及大型工具链增加起步成本。没有理由优先于当前LLVM路径 |
| [Emscripten](https://github.com/emscripten-core/emscripten) | 27.7k | LLVM/Wasm工具链很相关，但该仓库很多是driver/link/runtime glue，核心LLVM target在LLVM，Wasm优化在Binaryen；对于编译优化优先筛后两者 |
| [Enzyme](https://github.com/EnzymeAD/Enzyme) | 1.7k | LLVM/MLIR自动微分很真实；需较强AD语义与分析背景。作为专项观察，未把它验证成第一项易启动仓库 |

来源补充：[Zig 迁移公告](https://ziglang.org/news/migrating-from-github-to-codeberg/)、[ggml](https://github.com/ggml-org/ggml)、[MNN](https://github.com/alibaba/MNN)、[V8 贡献流程](https://v8.dev/docs/contribute)。Modular 的判断针对当前是否接受 compiler 贡献，不是笼统说它没有开放编译器源码。

<a id="decision"></a>

## 9. 怎样据此做选择，并形成简历案例

先选方向，再选具体问题。对你当前的条件，默认继续 **LLVM 主线**，另从 **Yosys/CIRCT/Verilator** 选择一个 EDA 备选。若需要更轻的 C++ pass 练习，可考虑 Binaryen；不要同时投入多套 AI/GPU 工具链。只有明确 JD 或硬件条件需要时，再上调专项项目。

一个仓库真正值得开始，应通过这四项检查：

1. 问题在当前主线可用精简输入复现，有清楚期望行为。
2. 修改涉及的模块能独立重建，并运行相关测试；不必先实现整个模型或产品。
3. 初步范围是已有分析/变换/生成逻辑的局部修复，不依赖新架构设计或未具备设备。
4. 当前 issue 开放，读完认领评论与关联 PR，未发现他人正在实现；必要的简短沟通用来确认具体技术问题。

第一项小贡献用于建立工作流；第二、第三项尽量围绕同一模块，形成连续技术主题。每项保留失败输入、根因、合法性条件、正反例回归、前后 IR/生成代码和真实 PR 状态。只有完成执行或测量的结果才写正确性/性能结论；提交、review 中、已合入分别如实表达。这样的证据比“学习了 LLVM/MLIR”或单纯累计 patch 数更能回答面试追问。

## 10. 独立参考与资料边界

仓库评估只维护此文。选题和合入证据仍查独立资料：

- [LLVM 普通 issue 的新贡献者合入分析](llvm-newcomer-merged-pr-analysis-2026-10-14.md)：进入先例、review 要求与具体候选核查。
- [LLVM 开放初学者 issue 清单](llvm-open-beginner-issues-2026-10-13.md)：标签库存及额外普通候选；记录中的状态均是快照，领取前刷新。
- [较早的具体贡献线索核查](compiler-contribution-screening-2026-10-13.md)：Dynamatic 等的历史选题证据，仓库优先级以本文为准。
- [归档原始仓库证据](archive/compiler-repositories-entry-evidence-2026-10-14.json)：star、活动与代表 PR 的查询记录。

前两份仓库评估已移入 `archive/`，仅作历史追溯，不继续作为并行建议文档维护。本文是已收集资料的整合，没有重新实时查询所有仓库，也没有代你认领任务、发布 PR 或实际构建所有项目。
