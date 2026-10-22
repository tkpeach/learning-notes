> 历史归档：当前统一评估请阅读 [候选仓库总览](../compiler-open-source-projects.md)。此文件不再维护；其中后续被调整的优先级以总览为准。

# 高关注度编译器仓库补查与实际入门成本（2026-10-14）

## 目标与核查方式

目标仍是补足直接后端经历，产生能写入简历、能在面试解释的技术贡献。已有 C++/EDA 经历，Mac 与 WSL，可迁移 Linux；实际贡献排除已认领任务，不以文档、拼写、安装问题凑后端经历。

本轮通过 GitHub repository search 的 compiler、C++ compiler、synthesis、MLIR 四组查询扩大候选，再读取官方 README、贡献/构建/测试文档和仓库页面。星数是 2026-10-14 的 API 或实时页面快照，按约数展示；不是岗位数量、工业采用程度或新人合入概率。没有穷尽所有编译器仓库，GitLab/Codeberg 项目也不能用 GitHub star 比较。

核查了代表性外部技术 PR 的实际 merge、review 和文件，以及 IREE 新旧 issue 的讨论。近期维护活动窗口为 2026-08-15 至本次查询：统计合入 PR 数，包括依赖升级、维护者自身工作与 CI，不等同外部贡献容量；更不等于新人成功率。API 限流时用官方页面补星数，不把读不到数据解释为停更。

本轮没有在用户机器实际构建这些新仓库。下面的便捷程度是文档、依赖结构、测试和公开 review 证据支持的工程判断，不能承诺半天跑通或某个 PR 必定被接受。除已经单独核查过的 LLVM 候选外，新增仓库尚未完成开放未认领小题的逐项筛选。

## “新手友好”具体拆成什么

1. **环境能否闭环：** 修改核心源码所需环境，而不只是 pip/安装包能否运行。区分预编译工具、开发构建与全平台 CI。
2. **任务能否限定：** 一个已有 pass/target hook 的可复现错误，是否能用小输入和回归验证；有没有先设计架构的负担。
3. **能否用现有设备验证：** 编译生成检查与执行/性能检查分别需要什么。输出 GPU IR 不意味着验证了 GPU 正确执行。
4. **能否获得有用 review：** 近期实际外部技术贡献、维护者的具体反馈、贡献政策是否要求提前讨论。欢迎文字和 GFI 个数不够。
5. **能否满足简历目标：** 真实编译器变换/CodeGen，还是 API、kernel、runtime、导入和文档；“backend”字样不能代替内容。

对第一项任务，优先选择：已有精简复现 → 局部实现 → 现成局部测试 → 无新硬件 → 无全新设计。评分按具体模块，而不是给整个 PyTorch/Yosys 一个笼统“友好”。

## IREE 的重新评价

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

来源：[贡献政策](https://iree.dev/developers/general/contributing/)、[仓库](https://github.com/iree-org/iree)。

## 新增、值得纳入的候选

### 1. Yosys：EDA 优先补入（约 4.8k star）

**项目与现状。** RTL 综合框架，C++ passes 在 RTLIL 上做优化、变换与技术映射，输出网表。当前还整合 slang/sv-elab 提供 SV 支持。2026-10-13 发布 0.70，查询窗口有 118 个合入 PR。它的相关性在硬件综合后段，而不是 CPU 指令后端。

**开始工作是否方便。** 比从整套 MLIR 张量 pipeline 起步更容易围绕一个 pass 限定输入和输出；普通优化/网表正确性测试不需 FPGA。可先用 OSS CAD Suite 复现，再做源码开发。当前源码已要求 C++20、CMake>=3.28、Python>=3.11、Bison>=3.8 等，并有子模块；不再照旧教程认为随便 make 即可。开发构建成本评为中，验证闭环较聚焦。

**具体入口。** `passes/opt` 的局部边界错误、memory/cell simplification、技术映射保留错误单元等；输入为小 RTL/RTLIL，测试使用 .ys 脚本、选择断言、SAT/equivalence。第一项避开全新综合算法、new techmap 架构、SV parser。

**社区证据。** [PR #6267](https://github.com/YosysHQ/yosys/pull/6267) 修复综合后剩余 `$buf` 的问题，作者自述首次 PR，维护者要求正确修复 opt_clean 根因，最终 API 记录已合入。改动包括实现及 Xilinx/Gowin/opt 三组 .ys 回归。不是“仅修改文档才欢迎新人”，也不是维护者自动接受初始方案。此例已解决，只能学习。

**实际限制。** 复杂/core 变更建议提前讨论；长期老代码与 `z`、undef、wire/cell 语义需要学。YosysHQ 2026-08 的临时 LLM 政策原则不接收 LLM 生成代码的 PR；允许作者能承担解释责任的 AI 辅助，并禁止生成代码注释/提交信息。适合本人主导学习与实现，不按“代理批量生成 patch”理解贡献路径。

**判断。** 对 EDA 求职值得与 CIRCT、Verilator 同组优先筛题。比 Dynamatic 更贴近综合工具生态；工业岗位匹配仍看具体工作，不凭 star 推断。

来源：[README/构建](https://github.com/YosysHQ/yosys/blob/main/README.md)、[完整贡献指南](https://github.com/YosysHQ/yosys/blob/main/docs/source/yosys_internals/extending_yosys/contributing.rst)、[LLM 政策](https://blog.yosyshq.com/p/interim-yosyshq-llm-policy/)。

### 2. Binaryen：C++ 编译优化的便捷备选（约 8.7k）

**项目与现状。** Wasm 优化器与 compiler/toolchain library，以自己的 IR 和 `wasm-opt` passes 为核心，不是机器 ISA 后端。窗口有 190 个合入 PR，最近还有 ConstraintAnalysis、subtype、global 优化修复。

**开始工作是否方便。** C++20、CMake/Ninja、Python>=3.10；不要求构建 LLVM，不需要 GPU/FPGA。小 .wat/.wast 输入可直接运行指定 pass，配合解释器/验证和 lit/FileCheck；部分套件另需 node/emcc，但不能把全部工具的依赖都算在一个普通 pass 首项上。初次构建仍需时间，依赖结构比 LLVM/MLIR 全栈轻。

**具体入口。** 局部 simplification、MemoryPacking、控制流/类型变换边界，选已有 pass 的错误或 missed optimization。不要先实现新的 Wasm proposal 或全局类型推理策略。

**社区证据。** [PR #8834](https://github.com/WebAssembly/binaryen/pull/8834) 作者明确称首次 Binaryen 贡献，维护者 tlively 给出 review 并批准；实际修改 MemoryPacking 与两份 lit 回归，2026 年合入。这证明优化代码的外部入口。此题来自旧的入门线索，说明旧日期需要确认，不能直接等于无价值。

**实际限制。** 当前 `good first bug` 只有 6 个开放条目，而且全部创建于 2023 年或更早；它没有“源源不断且没人抢的新手题”。推荐理由是环境与测试闭环，而不是标签更新更好。Wasm/GC/ref 类型语义也可能让看似几行的代码很难。

**判断。** 如果首先追求学习真实编译变换、完成可验证 C++ patch，值得保留；如果 JD 点名 LLVM ISA 后端，仍排在 LLVM 之后。简历写 Wasm IR 优化，不写寄存器分配。

来源：[README 的 build/testing](https://github.com/WebAssembly/binaryen/blob/main/README.md)。

### 3. ISPC：CPU 向量化/LLVM 编译链补入（约 3.0k）

**项目与现状。** C 风格 SPMD 编译器，把 uniform/varying 执行映射到 SIMD，使用 LLVM 优化与目标生成，支持 CPU 与 Intel GPU。查询窗口有 27 个合入 PR，贡献说明明确欢迎 ARM target 工作。

**开始工作是否方便。** C++ 与 LLVM 技能可复用，CPU 题可以不依赖 GPU。但需要匹配 LLVM/相关依赖与语言执行模型，开发构建成本为中到高；使用预编译 ispc 只能复现，不能验证源码修改。

**具体入口。** mask、varying pointer、向量运算 lowering 或一个目标相关 pass 的局部错误。代码生成检查用 tests/lit-tests；涉及语言行为还需 functional tests。源码范围比大型 AI 图编译框架集中。

**实际限制。** 17 个 GFI，最新创建于 2025-02，很多为教程、CMake、CI、stdlib，而非后端。一批条目的最近更新时间同日，不能因此当成重新开放的新工作。本轮未核实一个新的空闲小题，也未完成新人 merge 样本验证。

**判断。** 对 CPU/SIMD 编译岗位相关，值得继续筛普通 optimization/lowering 问题；不因 Intel 名称或 GFI 数量保证上手快。

来源：[README](https://github.com/ispc/ispc)、[贡献和 lit 要求](https://github.com/ispc/ispc/blob/main/CONTRIBUTING.md)。

### 4. AsmJit：机器码工程的条件备选（约 4.6k）

**项目。** C++ 低延迟机器码生成库，包含 x86/AArch64 emitters、instruction database、Compiler/JIT 层与测试。与底层机器码、寄存器、编码/ABI 有关系，不是完整 LLVM 优化编译器。

**方便处。** 不需构建 LLVM，不需 GPU；CMake 与项目测试可覆盖 encoding、assembler/compiler 输出。相比增加一整套模型 IR，更容易限定一个 emitter/指令信息错误。

**难处。** ISA/编码知识要求高，执行测试要匹配宿主架构。小社区可能由核心维护者直接 push；本窗口未查到已合入 PR，不能据此说停更，但也不能说外部新人 review 很活跃。文档欢迎已完成 bug fix，不保证 feature 请求被接受。

**判断。** 可作熟悉 JIT/机器码工程的备选；当前验证了低构建负担，没有验证稳定的新贡献任务供给，因此不替代 LLVM 主线。

来源：[组织与测试](https://github.com/asmjit/asmjit/blob/master/README.md)、[贡献说明](https://github.com/asmjit/asmjit/blob/master/CONTRIBUTING.md)。

### 5. Shader Slang：GPU 编译方向条件备选（约 5.7k）

**项目与现状。** `shader-slang/slang` 是 shader 编译器，与 SystemVerilog 的 `MikePopoloski/slang` 完全不同。自有 IR、模块特化、自动微分，输出 SPIR-V/DXIL/CUDA/Metal/CPU 等。窗口有 339 个合入 PR。

**开始工作是否方便。** 贡献指南有完整 CMake 构建、submodules、`slang-test` 和平台配置流程。某些编译输出/IR 测试不需要运行 GPU；完整 GPU 测试需要 SDK/驱动与设备。成本为中到高，不能用“支持 CPU”代替一个 GPU 错误的执行验证。

**具体入口。** 小 IR 变换、SPIR-V/目标文本 emission、类型/布局正确性。新增自动微分机制或整套 target 支持不适合第一项。

**实际限制。** 有 CLA；`GoodFirstBug` 当前 6 个，其中 4 个正式指派，剩余也需读评论/PR；不是现成无认领任务池。项目认可度更偏 GPU/shader，不能自动等同 AI 图编译或 EDA 经历。

**判断。** 若拓展 GPU compiler，可以保留，比纯 kernel 仓库更有编译器核心；不是当前 EDA 主选。

来源：[README](https://github.com/shader-slang/slang/blob/master/README.md)、[贡献/测试](https://github.com/shader-slang/slang/blob/master/CONTRIBUTING.md)。

### 6. Codon：高星真实编译器，起步效率尚需验证（约 16.9k）

**项目。** 面向 Python 风格程序的原生编译器，包含自己的 IR、变换和 LLVM IR 生成，可看到目标代码。当前获取到 LICENSE 为 Apache 2.0，不能沿用旧 BSL 印象。

**开始工作。** 用 release 较容易复现；修改 compiler 需源码、匹配 LLVM/依赖和 C++ 构建，成本中到高。测试为 Codon 程序，贡献说明要求必要时在 test/main.cpp 注册，PR 对 develop，而不是默认 master。

**实际限制。** 贡献指南明确 review throughput limited，本轮准确 GFI 查询为 0；未查出近期新人的局部 CodeGen 合入样本。不把高 star 当作可方便开始的证据。类型/标准库/语法修复又可能落回前端。

**判断。** 值得作为 LLVM IR/pass 路线观察项目，不在有明确空题之前投入整套构建。

来源：[README](https://github.com/exaloop/codon/blob/master/README.md)、[贡献指南](https://github.com/exaloop/codon/blob/master/CONTRIBUTING.md)、[LICENSE](https://github.com/exaloop/codon/blob/master/LICENSE)。

### 7. PyTorch / TorchInductor：高认可度 AI 编译模块（约 104.9k）

**项目。** 不把 PyTorch 整仓库当候选，只看 `torch/_inductor` 中 FX graph lowering、scheduler、fusion、CPU C++/GPU Triton CodeGen。Dynamo capture、operator/kernel、runtime 工作不能混算。

**开始工作。** CPU 题可利用现有设备；需要 Python、PyTorch compiler 内部、源码开发环境，生成 C++ 的经验也可关联后段。PyTorch 本体编译/版本依赖很大，不能因为主体 pass 是 Python 就认定环境简单。

**实际入口。** `test/inductor` 中可复现的局部 CPU CodeGen/调度正确性；避免从完整模型、CUDA 特定 fusion 起步。GFI 与 module:inductor 交集仅 2 项，一项是长期 tracking issue，另一项还标 internal ramp-up task；不等于有两个外部新人空题。

**判断。** AI compiler 岗位值得作为模块级候选；若目标主要是 LLVM machine backend，相关性弱一些。没有精简普通 issue 前不启动整库。

来源：[仓库](https://github.com/pytorch/pytorch)、[PyTorch 2 架构论文](https://pytorch.org/assets/pytorch2-2.pdf)、[贡献说明](https://github.com/pytorch/pytorch/blob/main/CONTRIBUTING.md)。

### 8. ExecuTorch：edge lowering/memory planning 候选（约 5.1k）

**项目与现状。** PyTorch 模型 export/lowering、memory planning、backend delegates 与 edge runtime，窗口有 1289 个合入 PR。许多工作是 vendor 内部、CI、kernel/runtime，不能用这个数量表示外部 compiler 任务特别多。

**开始工作。** 官方有 New Contributor Guide 与局部 pytest 路径；EXIR verifier/memory-planning 的 Python 题比完整 vendor delegate 更可控。修改 C++ runtime/自定义 op 需编译，delegate 还可能需要专用 SDK/设备；普通 wheel 使用不是源码开发闭环。

**社区证据。** [PR #10617](https://github.com/pytorch/executorch/pull/10617) 修改 memory-planning verifier 与测试，已合入；讨论指出测试库依赖、pytest ignore 与红 CI，耗时约 56 天。不是“两个 Python 文件所以无需环境/沟通”。release 中有 first-time contributors 是总体开放性证据，不证明他们都做 compiler。

**实际限制。** 需 CLA，贡献说明要求有 issue 时先 claim。GFI 很多属于 Android/JNI/CMake/examples；筛题要限 EXIR/partitioner/lowering，不以部署示例换编译器简历。

**判断。** AI/端侧岗位有价值，对直接 ISA backend 间接。明确 EXIR 小题时可起步，不能笼统评为“最简单”。

来源：[贡献说明](https://github.com/pytorch/executorch/blob/main/CONTRIBUTING.md)、[README](https://github.com/pytorch/executorch)。

### 9. Numba：环境较可控、后端匹配较间接（约 11.2k）

**项目与现状。** Python/NumPy JIT，通过 llvmlite 生成 LLVM IR；typing、typed IR、inlining、parallel transforms 与 lowering 分层。窗口有 67 个合入 PR。

**开始工作。** 官方推荐预编译 llvmlite/NumPy 的独立环境，再 build_ext 与局部 unittest，通常不用从头构建 LLVM。CPU 任务依赖负担较可控；版本配对和完整跨平台 CI 仍有成本。

**社区证据。** [PR #10637](https://github.com/numba/numba/pull/10637) closure inlining 的 silent miscompile 修复已合入；维护者明确祝贺作者首次贡献，并要求增加条件分支负例。可以贡献实质 IR 工作，而非只有文档。

**实际限制。** 很多 GFI 是多年前的 NumPy/CUDA 功能请求，不是现代小任务队列；官方解释有限 reviewer/CI 资源导致优先级排队。若只做 typing/NumPy overload，偏前端/库支持。应限制在 typed IR、parallel pass、LLVM emission；CUDA 路线还要检查当前独立 numba-cuda 项目分工。

**判断。** 便捷环境与真实 compiler 贡献兼顾的备选，但 Python/NumPy 领域与你既有 EDA/C++ 经历衔接弱于 LLVM/Yosys。

来源：[贡献与开发环境](https://numba.readthedocs.io/en/latest/developer/contributing.html)、[README](https://github.com/numba/numba)。

## 其他高关注项目：为什么不直接上调

| 项目 | star 快照 | 检查结果与定位 |
| --- | ---: | --- |
| Taichi | 28.4k | 真实 C++/LLVM compiler，但近窗口 0 merged PR，按创建时间查最近合入 PR 来自 2025-07；GFI 大量为 2020–2022 年任务，贡献文件还保留 LLVM 10 的旧说明。不是据此宣判整个项目废弃，但当前 GitHub contribution/review 风险明显，暂缓 |
| Swift | 70.5k | SIL optimization/IRGen 可形成 compiler 经历，C++可复用；工具链 checkout/build/test 大，需学 SIL/Swift 语义，不能因为声誉高优先于 LLVM 已明确的小题 |
| Rust compiler | 119.9k | LLVM CodeGen/MIR 有实际意义，成熟开发文档；同时学 Rust、rustc 与 bootstrap，机器 ISA 后端仍多在 LLVM。愿意转 Rust 再选，不是零成本替代 |
| Zig（旧 GitHub repo） | 43.3k | README 明确迁到 Codeberg且不是镜像。旧 GitHub issue/PR/star不能表示当前贡献入口。官方仍是编译器候选，但要重新查 Codeberg 与 Zig 语言成本，本轮后置 |
| Modular | 29.9k | 当前 README 明确暂不接受 Mojo compiler 贡献，主要接受 stdlib/MAX kernels/pipelines。不能把在此合入一个 kernel/stdlib patch写成修改 Mojo 编译器后端 |
| torch-mlir | 1.9k | 正确仓库为 llvm/torch-mlir，主要桥接 PyTorch/ONNX→MLIR，与用户不优先前端的条件较弱；LLVM/PyTorch版本绑定和构建负担大。不把旧命名空间的 0 star 当作项目情况 |
| SystemVerilog slang | 1.2k | C++、CMake、清楚单元测试、实际 SV parser/elaborator，被 Yosys使用；主要是前端。即便开发工程较聚焦，也不能解决用户希望补直接后端经历的问题 |
| Icarus Verilog | 3.7k | SV/Verilog→仿真 bytecode/netlist，C++与CPU可复用；可选 code generation，但大量开放任务是语言覆盖/前端。没有新贡献/review 样本前不提高到 Verilator/Yosys 之上 |
| Chisel | 4.8k | Scala 硬件描述/生成入口；RTL compiler 后段在 CIRCT/firtool。对用户优先筛 CIRCT，不为高关注度去重学 Scala 主体 |
| 旧 FIRRTL | 0.75k | GitHub已归档，README称 maintenance mode并指向CIRCT，不作为新主线 |
| llama.cpp / ggml | 131.1k / 15.5k | 推理runtime与tensor/kernels非常活跃；多数贡献是算子、量化、设备执行，不是通用 compiler pass/ISA backend。目标改成推理优化才上调 |
| ncnn / MNN | 24.0k / 16.2k | 可做图优化、converter、设备kernel，但很多 backend 工作是执行实现。避免只因C++和backend名称就替代编译器经历 |
| ONNX Runtime | 22.1k | graph optimization/EP partitioning与AI部署相关，普通ExecutionProvider/kernel贡献不是机器后端。设备SDK与runtime栈另有成本 |
| OpenROAD | 3.2k | 实际EDA C++工具，但重点是布局布线/物理设计算法，不是当前要补的compiler后端；若求职改成物理设计软件可重新评估 |
| GCC / V8 | 未用镜像星数排名 | 后端技术价值高，但GitHub mirror不是普通GitHub PR贡献入口；邮件/其他review平台及大型工具链增加起步成本。没有理由优先于当前LLVM路径 |
| Emscripten | 27.7k | LLVM/Wasm工具链很相关，但该仓库很多是driver/link/runtime glue，核心LLVM target在LLVM，Wasm优化在Binaryen；对于编译优化优先筛后两者 |
| Enzyme | 1.7k | LLVM/MLIR自动微分很真实；需较强AD语义与分析背景。作为专项观察，未把它验证成第一项易启动仓库 |

来源分别为各官方 README/贡献说明；Zig迁移见 [官方公告](https://ziglang.org/news/migrating-from-github-to-codeberg/)。前端slang与shader-slang必须区分；星数不是选择新手任务的硬阈值，所以领域匹配的3k–5k仓库仍保留。

## 原有17项：实际起步成本再细化

项目目标与现状的完整说明仍见 [原评估](compiler-project-evaluation-2026-10-13.md)。下表进一步限定“怎么开始”，不承诺仓库整体对每种新手都友好。

| 项目 | 第一闭环成本判断 | 相对可控入口 | 会使起步变慢的因素 | 当前取舍 |
| --- | --- | --- | --- | --- |
| LLVM | 构建中到高，局部验证可控 | llc/单target；SelectionDAG/GlobalISel已有错误+lit | IR/poison/合法化知识；热门GFI占用；性能题需硬件 | 当前已有两项具体普通候选，仍第一主线 |
| CIRCT | 中到高 | 单dialect Comb/HW/SV局部pass与circt-opt测试 | LLVM/MLIR子模块；跨dialect与硬件语义 | EDA优先组；只选局部变换，不设计新dialect |
| Verilator | 中 | 单优化pass/C++ emission与小SV仿真回归 | SV语义、仿真调度、完整语言功能 | EDA优先组；避开完整语言覆盖需求 |
| IREE | 中到高 | CPU CodeGen 的精简MLIR和局部lit | 多层pipeline、标签陈旧、新题已有认领；需筛普通issue | 从默认“易启动”降为拿到具体小题后再选 |
| Halide | 中 | Simplify/边界分析/CPU CodeGen局部测试 | schedule/vector/storage语义；新人需先讨论 | 可控备选；采用现有需求减少沟通 |
| Cranelift | Rust学习+构建中 | ISLE/target小规则、filetests | Rust与CLIF、寄存器和target约束同时学习 | 机器后端替代；不愿转Rust则后置 |
| TileLang | 匹配设备时中 | layout/guard/loop的小kernel和现有pytest | 必须验证对应CUDA/HIP/Metal；CPU后端实验性 | Apple silicon Metal题可选；不能验证CUDA专属行为 |
| Triton | 中到高 | 编译IR/单lowering、GPU小kernel | GPU与驱动、layout/warp语义；公开不承诺及时review | 有设备和具体bug才优先 |
| Triton-CPU | 中到高 | CPU lowering、向量化、CPU tests | 实验分支与上游变化；并非所有Mac配置都已验证 | 不为回避GPU就默认容易 |
| TVM | 中到高 | TIR/arith/CPU CodeGen小模块 | Relax/TIR/Python/C++跨度，旧教程，重设计讨论 | 题目驱动，不从完整模型部署开始 |
| rocMLIR | 高/设备条件 | rock IR变换 | AMD/ROCm；实测kernel；专用布局 | 暂无设备信息，后置 |
| XLA | 高 | 极小CPU emitter/HLO局部测试 | Bazel依赖、buffer/fusion多模块；GPU实测 | 不作为首次贡献默认项目 |
| XLS | 中到高 | 单IR rewrite/RTL emission和Bazel target | DSLX/proc语义、CLA、事前讨论；PPA多seed综合 | 明确HLS岗位与小题时选 |
| Dynamatic | 中到高 | Handshake canonicalization/局部bitwidth lit | MLIR、不同编译层、完整QoR/求解器流程、学术项目解释 | 有具体题是优点；不替代机器后端主线 |
| AdaptiveCpp | 中到高 | CPU/SSCP compiler pass局部修复 | SYCL host/device、多编译流；容易落到runtime | JD涉及异构编译时选 |
| MLIR-AIE | 设备条件高 | 离线资源/DMA/IR合法性 | RyzenAI/Versal设备、驱动、阵列模型 | 有具体设备和岗位才选 |
| llvm-aie | 中到高/专用知识高 | MIR/指令模式小题 | VLIW/流水线约束与fork、执行验证模型 | 专项备选，不比upstream LLVM默认简单 |

表里的“可控”指可用精简输入与局部测试，不指已核验有空闲题。补文档可以练流程，但不能担任本次简历目标的技术主案例。

## 对当前条件的排序与决策

- **机器后端主线：LLVM。** 已经有普通issue的进入先例与具体候选。不必为了躲开GFI竞争再换一个同样只有旧标签的仓库。
- **EDA备选：Yosys、CIRCT、Verilator。** Yosys是本轮最应补入的遗漏；选综合/硬件IR/仿真CodeGen中与岗位相符的一个。
- **比较便捷的编译优化学习备选：Binaryen。** 低设备负担与聚焦测试是主要优点，Wasm岗位匹配需另判断。
- **CPU/SIMD条件备选：ISPC；小型机器码库：AsmJit。** 前者需LLVM/SPMD，后者需ISA。都还没有本轮验证过的空题，先筛题再建环境。
- **AI方向：IREE CPU / TileLang匹配设备 / Inductor CPU / ExecuTorch EXIR。** 每项都以具体模块为单位。没有哪一个仅凭star或GFI清单就已经证明最易开始。
- **观察而不先投入：Codon、Shader Slang、Numba等。** 各有真实技术入口，先确认任务与简历匹配；Taichi暂缓。

工程上建议先做一个有限的“进入性验证”：精简输入能在主线复现；相关测试能够独立运行；修复范围能定位到一个模块；检查当前认领与关联PR。这四项满足后才选主项目。若主要困难变成搭多套SDK、找专用设备或争论新设计，就换题，不把起步投入无限扩大。

本轮完成了仓库与工程入口评估，未给新增仓库发布认领/PR，也未把已合入学习样本列为自己的贡献候选。
