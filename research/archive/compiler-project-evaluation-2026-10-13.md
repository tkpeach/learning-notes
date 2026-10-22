> 历史归档：当前统一评估请阅读 [候选仓库总览](../compiler-open-source-projects.md)。此文件不再维护；其中后续被调整的优先级以总览为准。

# 编译器开源项目重新评估（2026-10-13）

> 2026-10-14 更新：[高关注仓库补查与实际入门成本](compiler-repositories-entry-cost-2026-10-14.md) 新增 Yosys/Binaryen/ISPC 等，细化原17项的构建、测试、设备与沟通成本；IREE仍活跃，但旧GFI与占用问题使其不宜默认视为易启动项目。

## 目标与判断口径

目标是补足面试中缺失的直接编译器经历，通过小而真实的修复、回归测试和上游贡献形成简历证据。用户已经用投递验证机器码后端岗位较易匹配；有 EDA 背景、C++ 工程经验，环境为 Mac 和 WSL，必要时可迁移 Linux。实际贡献只考虑开放、未发现认领的问题。

这份评估覆盖之前讨论的 16 个项目，另将 MLIR-AIE 实际依赖的 llvm-aie 单列，总计 17 项。核查依据是各仓库当前默认分支 README、贡献指南、公开仓库信息和官方技术文档。项目状态读取于 2026-10-13；API 限流造成部分发布信息缺失时，不推断项目停更。push 日期只能说明仓库有活动，不能证明某模块活跃或新人 review 快。下列优先级、学习门槛和面试解释成本是针对用户的判断，不是招聘统计。

必须区分三种经历：

- 机器码后端：指令选择、类型/操作合法化、寄存器、调度、ABI、目标机器码。LLVM、Cranelift、llvm-aie 最直接。
- AI 编译后段：张量/循环变换、布局、buffer、设备映射、LLVM IR 或 CUDA/PTX 生成。IREE、Triton、TVM、TileLang 等最直接。
- EDA/HLS 编译：硬件 IR、位宽、调度、RTL 生成、仿真模型生成。CIRCT、XLS、Dynamatic、Verilator 最直接。

使用 LLVM 不代表实际修改 LLVM 后端；MLIR pass 贡献也不自动等价于寄存器分配经验。

## 优先级总览

| 项目 | 对用户的定位 | 主要经历 | 入门与验证条件 | 当前建议 |
| --- | --- | --- | --- | --- |
| LLVM | 已验证岗位路线的主项目 | 机器码后端/通用优化 | C++；Mac/WSL 可做跨目标代码生成测试 | 第一优先，围绕同一个后端模块积累贡献 |
| CIRCT | EDA 编译主备选 | 硬件 IR、RTL lowering/优化 | C++/MLIR；许多 IR 测试不需 FPGA | 若优先 EDA，与 Verilator 一起优先筛 |
| Verilator | EDA + C++ 经历最容易衔接之一 | HDL 优化、仿真 C++ CodeGen | C++、SV 语义；CPU 可测试 | EDA 主备选；不要包装成指令后端 |
| IREE | AI 编译主备选 | MLIR、CPU/GPU CodeGen | CPU 路线可先不买 GPU | AI 方向优先于从零追逐特定 GPU 功能 |
| Halide | 有限范围内学习优化的备选 | 循环/向量化、LLVM IR CodeGen | C++；Mac/CPU 路线可行 | 对学习友好，但需先按指南讨论范围 |
| Cranelift | 真正后端的替代路线 | ISLE、legalization、机器码 | Rust 学习成本；CPU 可验证 | 愿意转 Rust 时上调，LLVM JD 优先时靠后 |
| TileLang | AI kernel/编译方向条件备选 | 布局、循环、GPU/Metal CodeGen | 当前已支持 Apple Metal；CPU 后端实验性 | 若 Mac 为 Apple silicon，可上调；按目标设备选问题 |
| XLS | EDA/HLS 的专门备选 | IR 优化、pipeline scheduling、RTL | 建议 Linux；Bazel、CLA、PPA 验证 | 比 Dynamatic 更容易说明来源，但并非通用机器后端 |
| Dynamatic | HLS 学习与局部贡献备选 | Handshake、位宽、数据流硬件优化 | 建议 Linux；深入 QoR 可能要综合工具 | 有可切入问题；不作为泛后端求职唯一主项目 |
| AdaptiveCpp | 异构编译备选 | LLVM passes、设备编译、JIT/runtime | C++/SYCL；设备覆盖影响验证 | 选 compiler 子模块，避免只做 runtime/API |
| TVM | AI 编译广泛路线 | Relax/TensorIR、调度、CodeGen | CPU 可起步；Python+C++ 和较大栈 | 有明确小题再选，避免从“做一个模型”起步 |
| Triton | AI 编译强相关、首次贡献成本较高 | GPU 布局、lowering、LLVM IR | GPU 后端执行/性能通常需要对应 GPU | 有硬件与小题再上调；review 无及时承诺 |
| Triton-CPU | 无 GPU 的 Triton 学习支线 | Triton 到 CPU lowering/向量化 | 实验性；优先 Linux CPU | 可做编译题，但不把它等同主线 GPU 经验 |
| XLA | 有工业使用基础的 AI 编译大项目 | HLO、fusion、buffer、LLVM/Triton emission | 大型 Bazel 栈；模块依赖多 | 有非常明确的小题才启动，首次贡献不优先 |
| rocMLIR | AMD GPU 专项 | rock lowering、GEMM/conv kernel CodeGen | ROCm/AMD GPU 对执行验证重要 | 暂无设备信息，后置；不能只靠静态 IR 宣称性能 |
| MLIR-AIE | 特定 AMD NPU 阵列编译 | placement、ObjectFIFO、DMA、连接 | 运行需匹配 NPU/驱动；IR 测试部分可离线 | 设备与岗位都对齐时选，否则后置 |
| llvm-aie / Peano | 专用 ISA 机器后端 | VLIW 指令选择、寄存器、调度 | LLVM fork、ISA/工具链学习 | 技术相关性高，生态与验证更专门；不作首选 |

没有给出看似精确的“合入概率”或新人 review 平均天数。少量近期合入 PR 可能来自核心维护者自行提交，不能代表外部新人体验。

## 逐项目说明

### 1. LLVM / llvm-project

**做什么。** 多组件编译基础设施。对于用户，核心是 `llvm/lib/CodeGen` 和 `llvm/lib/Target`，而不是整个 monorepo。SelectionDAG、GlobalISel 处理目标相关/无关的指令选择与合法化，后续还有寄存器分配、机器指令优化、调度、汇编/目标文件。

**现状。** 主线持续开发，发布版本与开发主线分开。本次读到最新正式 release 为 23.1.3（2026-10-06）；报告中 issue 可能针对 24.0.0git，应固定主线 revision 复现，不能用系统自带旧版行为直接判断。开放新手条目多，但“无人指派”远不等于“无人做”。

**适合进入。** 小 combine、target KnownBits/demanded-bits、一个操作或类型的 legalization、局部误编译和 crash 修复。第一项可以是一个明确边界错误；后续同模块再做优化，形成连续故事。寄存器分配算法、全新目标和大规模调度模型不适合第一项。

**环境与社区。** 编译后端可以在宿主机生成 X86/AArch64/RISC-V 代码；许多 lit/FileCheck 测试不需要运行对应硬件。执行正确性、微架构性能和硬件调度测量则需要相应条件。CMake/Ninja、assertions build 与局部测试是主要门槛。官方新手问题禁止用 AI 工具修复；搜索和学习允许，其他贡献按政策要求人类负责与披露。当前工作仅做搜索、分析和整理。

**简历价值。** 最直接匹配已验证的后端 JD。要能解释失败 IR、处理阶段、合法性和修复后的目标代码；一个拼写修复不具有同等分量。

来源：[仓库](https://github.com/llvm/llvm-project)、[贡献指南](https://llvm.org/docs/Contributing.html)、[Code Generator](https://llvm.org/docs/CodeGenerator.html)、[AI 政策](https://llvm.org/docs/AIToolPolicy.html)。

### 2. CIRCT

**做什么。** 基于 MLIR 的硬件编译基础设施，包含 FIRRTL、HW、Comb、Seq、Handshake 等表示及多类 lowering、Verilog emission。它的“后端”主要是硬件/RTL 后端。

**现状。** README 仍明确称项目为实验性，但不能由此推断所有模块都只是研究原型。firtool 有持续发布，本次读到 1.161.0（2026-10-01）；Chisel 官方说明从 v3.6 起使用 CIRCT 的 firtool 生成 Verilog，是可核验的实际集成证据。不同 dialect 的成熟度与维护者覆盖不同。

**适合进入。** Comb 局部变换、位宽/常量折叠、HW/SV emission 的具体错误、一个 lowering 的边界条件。优先已有精简 IR 和清楚期望结果的问题，不从设计新 dialect 起步。

**环境与社区。** LLVM/MLIR 子模块带来较大的构建成本，但 IR 和 emission 的许多测试无需 FPGA。沿用 LLVM 开发政策，模块维护者的意见决定变换是否放在此处。单个 op 的标准折叠比跨 dialect 的重新设计沟通成本更低。

**简历价值。** 对 EDA 编译器、硬件 IR 和 MLIR 岗位很贴近；相比 Dynamatic，有 firtool/Chisel 这条更容易说明的应用链路。仍不能写成 CPU 指令选择经历。

来源：[README](https://github.com/llvm/circt/blob/main/README.md)、[dialect/工具文档](https://circt.llvm.org/docs/)、[Chisel 集成说明](https://www.chisel-lang.org/chisel3/docs/appendix/versioning.html)。

### 3. Verilator

**做什么。** 把 Verilog/SystemVerilog 编译为 C++/SystemC 仿真模型，再由 C++ 编译器形成可执行程序。编译器自身涉及 AST、展开、优化、调度和 C++ emission；它不产生芯片实现 RTL，也不直接承担 CPU ISA 的机器后端。

**现状。** 官方 latest 文档当前为 5.052。FAQ 明确描述硅设计企业和 CERN 等用户，工业使用证据比纯学术 HLS 项目充分。本次未通过 GitHub latest-release API 获取版本，版本来源为官方文档，不能把 release API 404 当作停更。

**适合进入。** 某个已有优化 pass 的边界错误、生成 C++ 的正确性或代码质量、位宽/符号处理、一个可精简的 SV 构造。首次避免完整实现复杂 SV/UVM 功能与仿真调度架构变更。

**环境与社区。** CPU 即可运行生成模型；Linux/WSL 是稳妥路径。要补 SV 语义，而你的 C++ 与 EDA 经历可以复用。仅修 parser/诊断也可以贡献，但若为了后段简历，应主动筛优化/生成部分。

**简历价值。** 适合 EDA 仿真编译器和 C++ 优化岗位。能讲清“SV 输入→优化后表示→生成 C++→仿真回归”会比只说熟悉 Verilator 更有价值。

来源：[官方概述](https://verilator.org/guide/latest/overview.html)、[FAQ](https://verilator.org/guide/latest/faq.html)、[仓库](https://github.com/verilator/verilator)。

### 4. IREE

**做什么。** 基于 MLIR 的端到端模型编译器与运行时。包含张量/循环变换、dispatch、CPU/GPU CodeGen、HAL 和 VM/runtime。选择 LLVMCPU/CodeGen 的问题，比随意修模型导入更贴近目标。

**现状。** 持续开发，提供稳定/夜间包，属于 LF AI & Data Foundation。当前贡献指南列出了 TSC 和维护流程；README 链接 AMD 用 IREE 实现 SDXL 并提交 MLPerf 的案例，是实际使用证据，不应把它只描述成早期 Google 实验。模块与设备覆盖仍然不同。

**适合进入。** CPU lowering、向量化边界、buffer/dispatch 合法性、一个局部变换的 crash 或 miscompile。不要从“支持完整模型”开始，也不要把只修运行时接口写成 CodeGen 经历。

**环境与社区。** 官方有 macOS arm64/Linux CI，CPU 路线适合现有设备；GPU 性能题另需目标硬件。MLIR 和多阶段 pipeline 是主要学习成本。社区渠道清楚，但没有从有限样本推出新人合入速度。

**简历价值。** 若转 AI 编译器，这是优先备选；能补 lowering、向量化与生成代码经历，但一般仍不涉及 LLVM 的寄存器分配。

来源：[README](https://github.com/iree-org/iree/blob/main/README.md)、[贡献说明](https://github.com/iree-org/iree/blob/main/CONTRIBUTING.md)、[开发文档](https://iree.dev/developers/)。

### 5. Halide

**做什么。** 面向图像和数组计算的 DSL，区分算法表达与 schedule，处理循环、向量化、存储和目标代码生成，支持 CPU、多类 GPU API。C++ 嵌入式接口与你的工程语言匹配。

**现状。** 成熟而持续维护，当前 README 支持 X86/ARM/RISC-V 等与 macOS/Linux；本次 GitHub latest release 返回 v21.0.0（2025-09-16），同时仓库 2026 年仍在更新，所以 release 间隔不是停更证据。

**适合进入。** Simplify、边界/范围分析、向量化、局部 CodeGen 正确性。已有 CPU reproducer 的问题较易独立验证。GPU 特定速度优化与 autoscheduler 改进不要作首项。

**环境与社区。** Mac/CPU 可以起步，CMake 工程相对聚焦。贡献指南要求新人先 issue/discussion 对齐；通常一个工作周内 review 是其公开目标而非保证。你不喜欢沟通成本，因此选择已有明确需求的 issue，避免先设计大改动。

**简历价值。** 能形成扎实的循环/向量化优化案例；对一般 LLVM 后端岗位略间接，对图像/数值/AI 编译岗位更直接。

来源：[README](https://github.com/halide/Halide/blob/main/README.md)、[贡献指南](https://github.com/halide/Halide/blob/main/CONTRIBUTING.md)。

### 6. Cranelift（Wasmtime 仓库内）

**做什么。** Rust 实现的机器码编译后端，强调编译速度。CLIF IR、ISLE lowering、目标指令、寄存器分配/机器码发射是真正后端内容；不要与 Wasmtime 的组件模型/API 工作混在一起。

**现状。** 作为 Wasmtime 编译基础设施持续开发，不是独立教学编译器。官方贡献指南明确提供新手标签与 compiler mentoring，公开表达指导新人的意愿。

**适合进入。** 单个 ISLE rewrite、一个目标指令模式、局部 legalization、code emission 修复，先以 filetests 验证。避免把 Wasmtime 文档/接口修复当作后端证据。

**环境与社区。** CPU 即可验证许多任务，Mac/Linux 路线可用；代价是同时学 Rust 和编译器内部。官方明确不接受只改拼写的 trivial PR，因此“先随便合一个”不是合理路线。

**简历价值。** 后端经验很直接；如果 JD 明确偏 LLVM/C++，还需要解释迁移关系，所以当前放在 LLVM 之后。愿意转 Rust 时可以提高优先级。

来源：[Wasmtime 仓库](https://github.com/bytecodealliance/wasmtime)、[贡献与 mentoring](https://docs.wasmtime.dev/contributing.html)、[Cranelift 源码](https://github.com/bytecodealliance/wasmtime/tree/main/cranelift)。

### 7. TileLang

**做什么。** 以 tile 为抽象编写高性能 kernel，围绕 TVM 技术栈进行布局推导、循环/线程映射、同步和多设备代码生成。编译器 bug 与仅实现一个 kernel 是不同经历。

**现状。** 本次 release 为 v0.1.15（2026-09-30）。当前 README 已呈现 TileLang-X 多后端架构：CUDA 为 Primary，HIP、Ascend 950、Apple Metal 为 Supported，LLVM CPU 为 Experimental；一些国产设备适配在独立生态仓库。不能继续用早期“只支持 CUDA/AMD”的印象评估。

**适合进入。** layout inference、循环绑定、cast/guard preservation、CodeGen 的小边界错误。优先可以用一个小 kernel 和现有测试验证的题。只调 GEMM 参数或搬运示例不一定构成编译器经历。

**环境与社区。** 若你的 Mac 是 Apple silicon，Metal 路线现在有现实空间；这不意味着能在 Mac 验证 CUDA/TMA/WGMMA。CPU 后端仍实验性，不适合作为所有 GPU bug 的替代验证。贡献指南提供 `♥ help` 标签和明确测试/格式工作流；标签本身不保证未认领。

**简历价值。** 对 AI kernel/compiler 岗位贴近。如果坚持机器码后端，它通常止于生成设备源代码/IR，不能替代指令选择经验。具备匹配设备时优先级明显上升。

来源：[README 与 backend 表](https://github.com/tile-ai/tilelang/blob/main/README.md)、[贡献指南](https://github.com/tile-ai/tilelang/blob/main/CONTRIBUTING.md)。

### 8. Triton

**做什么。** 面向深度学习 kernel 的语言与编译器，使用 MLIR/LLVM 技术，涉及 layout、共享内存、warp/线程映射、lowering 与设备代码生成。

**现状。** 主线持续发布，本次正式 release 为 3.8.0（2026-08-28）。XLA 官方架构文档也明确使用 Triton 作为部分 GPU fusion 的 CodeGen 层，实际生态关联清楚。

**适合进入。** 有精简 reproducer 的布局转换、类型/索引边界、单个 lowering 错误。第一项不要做新 GPU 架构支持或复杂 tensor-core pipeline。

**环境与社区。** IR 层测试有离线空间，但 GPU 执行与性能题需要适配设备和软件栈。贡献指南明确说维护者可优先自己的工作，外部贡献者不应预期 prompt review。对你低沟通成本、从简单开始的要求，这是实际减分项。

**简历价值。** AI GPU 编译器相关性很高；没有硬件却只完成静态路径，容易在面试追问正确性/性能时出现证据缺口。已有 GPU 和清楚小题时再上调。

来源：[README](https://github.com/triton-lang/triton/blob/main/README.md)、[review 政策](https://github.com/triton-lang/triton/blob/main/CONTRIBUTING.md)、[XLA GPU 架构](https://openxla.org/xla/gpu_architecture)。

### 9. Triton-CPU

**做什么。** Triton 的长期实验 CPU 后端分支，争取把非 CPU 专属改动上推主线。支持在 CPU 上运行 Triton 程序。

**现状。** README 明确为 experimental/work in progress；本次有 v3.8.0+cpu 发布（2026-09-22）。所以不能说“没有发布/没人维护”，也不能把它当作与主线 GPU 同样成熟。

**适合进入。** CPU lowering、向量化或一个算子的局部合法性问题，先跑 CPU examples 与相关测试。分支差异/上游 API 变化也会形成额外工作。

**环境与社区。** 不依赖 GPU 是优点；先选择官方构建能覆盖的 Linux CPU 环境。不要未经核查保证所有 Mac CPU 情况都可运行。贡献说明沿用了 Triton 的流程，不能自动承诺新人更易合入。

**简历价值。** 能证明 AI 编译到 CPU 的能力；认可度需要解释“是实验后端分支，具体贡献在哪”，弱于直接 Triton 主线品牌的等同表述。

来源：[README](https://github.com/triton-lang/triton-cpu/blob/main/README.md)、[贡献说明](https://github.com/triton-lang/triton-cpu/blob/main/CONTRIBUTING.md)。

### 10. Apache TVM

**做什么。** 模型/张量编译框架，当前设计强调 Relax 与 TensorIR 的跨层优化和 Python-first 定制，同时有 C++ 分析/变换与目标 CodeGen。

**现状。** 本次 release 为 v0.27.0.post1（2026-09-29）。主线 README 明确已多次重构，当前设计与早期不同；不应照旧教程以 Relay 作为整个当前架构的主线。

**适合进入。** TensorIR 算术简化、边界/索引分析、具体 lowering/CodeGen 错误。Python 层贡献也可能是实质 compiler pass，但 runtime 包装/API 修复与后端相关性不同。

**环境与社区。** CPU 可起步，GPU 专项仍需硬件。框架范围大、跨 Python/C++、旧教程容易偏离主线。采用 Apache 社区模式，重设计需要讨论。没有明确小题时，搭完整模型端到端流程容易耗时且缺乏自己的技术贡献。

**简历价值。** AI 编译相关性高；对机器指令后端间接。选一个分析/变换模块持续贡献，胜过泛泛写“熟悉 TVM”。

来源：[当前 README](https://github.com/apache/tvm/blob/main/README.md)、[Relax 文档](https://tvm.apache.org/docs/deep_dive/relax/index.html)、[贡献指南](https://tvm.apache.org/docs/contribute/)。

### 11. rocMLIR

**做什么。** 针对 AMD GPU 的 MLIR kernel generator，当前覆盖 GEMM、convolution、attention 等，经过 rock、amdgpu/rocdl 到 LLVM AMDGPU 后端。

**现状。** 当前 README 明确主要作为 `librockCompiler` 被 MIGraphX 使用，也可 standalone 生成/验证/调优；2026-10-09 有仓库 push。技术定位比“泛 MLIR 项目”具体，但不能把其贡献自动等同 LLVM AMDGPU 后端贡献。

**适合进入。** rock lowering、布局/索引合法性、具体 kernel 生成错误。IR 回归可以是入门，但性能主张必须执行目标 kernel。

**环境与社区。** README 把 AMD GPU/ROCm 列为前置条件。静态测试是否可不带 GPU 构建要按具体目标验证，不能提前保证。当前贡献指南很具体，要求针对 develop、回归测试与 CI；沿用 LLVM AI 政策。

**简历价值。** 若目标明确为 AMD GPU/ROCm compiler 很相关；你尚未提供对应硬件信息，因此当前后置，迁移 Linux 本身不解决 GPU 缺失。

来源：[README](https://github.com/ROCm/rocMLIR/blob/develop/README.md)、[贡献指南](https://github.com/ROCm/rocMLIR/blob/develop/CONTRIBUTING.md)。

### 12. OpenXLA / XLA

**做什么。** 对框架计算图进行 HLO 优化、fusion、layout、buffer assignment，再使用 LLVM/native emitters/Triton 等生成 CPU/GPU 可执行内容。用户应选实际 CodeGen 部分，不是随意一个模型支持问题。

**现状。** 当前 README 和官方文档说明与 JAX、TensorFlow、PyTorch/XLA 等集成；主线活跃，工业使用背景明确。本次 release API 限流，不把“没有读取到版本”写成“无正式发布”。

**适合进入。** 单个 CPU emitter、已有 HLO 模式的局部错误、clear-cost/shape 前提下的具体优化。新增完整 backend、复杂 fusion 策略不适合首项。

**环境与社区。** Bazel 与庞大依赖栈、HLO→后端多阶段上下文增加起步成本。CPU 路线有可行空间，GPU 性能另需设备。贡献点必须落在公开、能独立验证的路径上。

**简历价值。** 对 AI compiler 强相关，但“项目强”并不等于“首次贡献划算”。只有清楚的小 issue 才值得优先启动，不为品牌搭半个完整栈。

来源：[README](https://github.com/openxla/xla/blob/main/README.md)、[官方架构](https://openxla.org/xla/architecture)、[GPU 架构](https://openxla.org/xla/gpu_architecture)。

### 13. Google XLS

**做什么。** 高层功能描述/DSLX 到 XLS IR，再做优化、pipeline scheduling 和 Verilog/SystemVerilog CodeGen；支持纯函数与有状态 proc。属于硬件合成编译，不是 LLVM ISA 后端。

**现状。** 主线和构建产物持续更新，本次 release 是按提交生成的版本。README 仍明确实验性、非 Google 官方支持产品，DSLX 可以破坏兼容性；“Google 仓库”不能推出广泛工业采用。

**适合进入。** IR 局部优化、bit-level 分析、select/RTL emission 小问题。之前 #490 可作为候选但很旧，需要当前主线复现及确认需求。Scheduling/PPA 优化的验证比表面更重。

**环境与社区。** 建议 Linux x86-64/WSL + Bazel。需要 CLA；官方建议先 issue 讨论，XS/S 是熟悉代码者的估计，不是新人时间。声称 PPA 改善需按项目要求多 seed 综合，不能只报告一个最好看的结果。

**简历价值。** 对 HLS/EDA 后段能形成清楚的优化故事；项目来源较好解释，但不能仅靠 Google 名字。若投一般 LLVM 后端，需要另补机器代码层案例。

来源：[README](https://github.com/google/xls/blob/main/README.md)、[贡献/PPA 要求](https://github.com/google/xls/blob/main/CONTRIBUTING.md)。

### 14. Dynamatic

**做什么。** MLIR 驱动的动态调度 HLS，C/C++ 经多级 lowering 变为 Handshake 数据流电路与 RTL，优化方向包括内存依赖、buffer placement、位宽。

**现状。** EPFL/ETH Zurich 学术开源项目，当前主线仍更新；本次 GitHub latest 正式 release 是 2024 年的 2.0.0，但不能据此判断 2026 年代码停滞。2026 年团队有 MLIR/HLS 经验论文，科研定位清楚。这轮没有足以证明广泛工业产品采用的公开证据；与 Vivado/Modelsim 集成不等于厂商采用。

**适合进入。** #148 标准 canonicalization 接入可学工程框架，#818 backward bitwidth 是更有实质性的优化候选；之前已核查公开认领状态，但实际开始时仍需刷新。首次避免新动态调度机制、求解器/形式化框架大变更。

**环境与社区。** 建议 Linux/WSL，普通 IR/pass 测试与完整综合/QoR 流程分开。学术社区可能提供更细的项目任务，但目前没有证明 review 比 LLVM 更快；任务可切入不等于维护沟通必然轻。

**简历价值。** 做扎实的位宽正确性与 RTL 验证可以写；#148 单一重构的分量有限。面试官可能不认识项目，需说明编译链路；泛机器后端岗位不能用它替代指令选择经历。

来源：[README](https://github.com/EPFL-LAP/dynamatic/blob/main/README.md)、[EPFL 学生项目](https://www.epfl.ch/labs/lap/available-student-projects-at-lap/)、[2026 论文](https://arxiv.org/abs/2603.19856)。

### 15. AdaptiveCpp

**做什么。** 原 hipSYCL/Open SYCL，支持 SYCL、C++ parallelism 和实验 PCUDA，使用 LLVM 编译与异构 runtime/JIT 跨 CPU/GPU。这里同时有 compiler 和普通 runtime 工作，需仔细划分。

**现状。** 当前 develop 活跃；README 展示多厂商 CPU/GPU 与 Apple 支持，但每种编程模型/编译流成熟度不同。不能拿支持某设备概览保证某 issue 能在用户 Mac 重现。

**适合进入。** SSCP/LLVM passes、设备 IR 转换、一个编译错误或小优化。runtime scheduling、安装、API compatibility 贡献也有价值，但不能承担本次后端目标。

**环境与社区。** C++ 经历可复用，需学 SYCL 和 host/device 编译关系。CPU 可验证部分路径，设备问题按后端配置核查；项目建议不确定时先讨论。构建 LLVM 插件和多编译流容易分散注意力。

**简历价值。** 对异构/HPC compiler 相关，对传统机器指令后端较间接。明确目标公司采用 SYCL/LLVM 时上调，否则次于更聚焦的 LLVM/IREE。

来源：[README](https://github.com/AdaptiveCpp/AdaptiveCpp/blob/develop/README.md)、[贡献指南](https://github.com/AdaptiveCpp/AdaptiveCpp/blob/develop/CONTRIBUTING.md)。

### 16. MLIR-AIE / IRON

**做什么。** 为 AMD AI Engine 阵列表达 tile placement、ObjectFIFO、DMA 和 stream connectivity，当前对外入口强调 IRON Python API 和 Ryzen AI NPU 编程。

**现状。** AMD 维护，最新读取 release v1.4.4（2026-10-06）；README 明确与 Ryzen AI Software Platform 互补，而非替代。它通过 Peano 编译 core 程序，不能把 MLIR-AIE 本身称为全部 AIE 指令后端。

**适合进入。** ObjectFIFO lowering、buffer/DMA 合法性、tile 资源分配的局部错误、设备配置 emission。运行 notebook/示例不足以构成编译器贡献。

**环境与社区。** 部分 IR 测试可离线，端到端需支持的 Ryzen AI/Versal、驱动和 runtime。Mac/WSL/Linux 的选择不能替代硬件要求。贡献指南清楚，但特定设备语义学习与验证成本较高。

**简历价值。** 对 NPU 编译、数据搬运和空间映射岗位强，对泛 LLVM backend 需要解释差异。只有目标 JD 和设备都匹配时作为主线。

来源：[README](https://github.com/Xilinx/mlir-aie/blob/main/README.md)、[贡献指南](https://github.com/Xilinx/mlir-aie/blob/main/CONTRIBUTING.md)。

### 17. llvm-aie / Peano

**做什么。** LLVM fork 中的 AMD AI Engine target，生成暴露流水线的 VLIW 机器指令；涉及指令选择、bundling、调度与寄存器，是这两个 AIE 仓库中更直接的机器后端。

**现状。** 当前默认分支为 aie-public，2026-10-13 有 push。支持 XDNA/XDNA2 等目标，作为 MLIR-AIE 链路的编译组件。实际 hardware 产品存在不代表所有 fork 改动都已进入 upstream LLVM。

**适合进入。** 一个明确指令模式、MIR verifier/合法化错误、目标局部修复。完整 pipeline hazard/scheduling 功能对新手风险较大。

**环境与社区。** 静态 llc/MIR 测试可以有离线空间，正确执行/性能需要设备或适当模型。ISA、专有约束和 fork 与 upstream 的关系增加背景学习。贡献指南指向 LLVM 政策，没有公开证据足以说它比 upstream 更适合新手。

**简历价值。** 对 DSP/VLIW/NPU 后端技术匹配很好，但如果目标是最小成本形成通用后端经历，仍优先 LLVM 的 AArch64/RISC-V/X86 局部问题。

来源：[架构与 README](https://github.com/Xilinx/llvm-aie/blob/aie-public/README.md)、[贡献说明](https://github.com/Xilinx/llvm-aie/blob/aie-public/CONTRIBUTING.md)。

## 最终选择原则

1. 若继续投已经验证匹配的机器后端岗位：LLVM 为主，Cranelift 为有条件替代，llvm-aie 为目标岗位明确时的专用选项。
2. 若强化 EDA 与既有经历的连接：先筛 CIRCT/Verilator；明确 HLS 岗位再考虑 XLS/Dynamatic。不能把 EDA 与 HLS 当成同一类岗位。
3. 若拓宽 AI compiler：先选 IREE CPU/CodeGen；TileLang 在匹配设备上可以提高优先级，Halide/TVM 作题目驱动备选。Triton/XLA 的技术与生态价值高，但首次贡献成本也高。
4. 第一项“小”用于建立工作流；第二、第三项应围绕同一模块形成主题。简历需要复现、根因、合法性、回归、前后 IR/生成代码和真实 PR 状态；不以合入个数取代技术内容。
5. 项目排序与某个 issue 的可用性分开。Dynamatic 当前有空题，不代表应该取代 LLVM 主线；LLVM 官方新手题拥挤，也不代表非标签的小问题没有空间。
