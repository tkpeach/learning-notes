# AI 前沿日报 Review State

> 本文件由日报任务维护。  
> 只保存增量复评所需的压缩状态，不保存网页全文、完整搜索日志或大段论文正文。  
> 日期/时间统一使用 Asia/Shanghai，建议采用 ISO 8601。

---

# Source Cursor

## 使用规则

每个固定实时扫描源独立维护：

- `last_seen_item`
- `last_seen_publish_time`
- `last_successful_scan`

只有当本次成功确认该源当前最新可见条目，并完成 `latest → old cursor` 范围内所有遗漏检查后，才推进 cursor。

如果网站访问失败、页面不完整、无法确认最新条目、仅拿到搜索摘要或日期无法可靠判断，则**不得推进 cursor**。

初次运行时，如果没有历史 cursor：

1. 对该源完成一次初始化扫描；
2. 处理当前 25h 内真实新增；
3. 如有必要向前检查一小段近期历史，避免初始化当天明显漏掉重大项目；
4. 完成后再设置 `last_seen_item`。

---

## OpenAI News

- last_seen_item: Rapidly scaling online storage to serve over 1 billion ChatGPT users
- last_seen_publish_time: 2026-09-11
- last_successful_scan: 2026-09-14T01:00:46+08:00

## OpenAI Index

- last_seen_item: Rapidly scaling online storage to serve over 1 billion ChatGPT users
- last_seen_publish_time: 2026-09-11
- last_successful_scan: 2026-09-14T01:00:46+08:00

## OpenAI Product

- last_seen_item: Now everyone can put data to work
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-14T01:00:46+08:00

## OpenAI Research

- last_seen_item: Build more natural voice experiences with GPT‑Live‑1 in the API
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-14T01:00:46+08:00

## OpenAI Engineering

- last_seen_item: Rapidly scaling online storage to serve over 1 billion ChatGPT users
- last_seen_publish_time: 2026-09-11
- last_successful_scan: 2026-09-14T01:00:46+08:00

## OpenAI Safety

- last_seen_item: Funding grants for new research into AI and teen development
- last_seen_publish_time: 2026-09-08
- last_successful_scan: 2026-09-14T01:00:46+08:00

## OpenAI Security

- last_seen_item: Daybreak for Frontline Defenders
- last_seen_publish_time: 2026-09-03
- last_successful_scan: 2026-09-14T01:00:46+08:00

## OpenAI Global Affairs

- last_seen_item: Expanding AI access across every level of US government
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Google DeepMind Blog

- last_seen_item: Introducing Gemini 3.8 Flash and 3.8 Flash Cyber
- last_seen_publish_time: 2026-09-02
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Anthropic Newsroom

- last_seen_item: Detecting and countering misuse of AI: September 2026
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Claude Blog

- last_seen_item: T. Rowe Price brings more of Claude to its investment process
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-14T01:00:46+08:00

## DeepSeek Updates

- last_seen_item: DeepSeek-V4.1-Flash Release
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-14T01:00:46+08:00

## DeepSeek Homepage

- last_seen_item: DeepSeek-V4.1-Flash 发布
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Qwen Blog

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Qwen Chinese Blog

- last_seen_item: Qwen3Guard：实时安全，逐词响应
- last_seen_publish_time: 2025-09-23
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Aliyun Model Studio New Models

- last_seen_item: qwen3.8-max-0902
- last_seen_publish_time: 2026-09-02
- last_successful_scan: 2026-09-14T01:00:46+08:00

## ModelScope Qwen

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Zhipu Research

- last_seen_item: GLM-5.3-Flash：前沿智能进入普惠时代
- last_seen_publish_time: 2026-08-26
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Kimi Blog

- last_seen_item: Kimi K3
- last_seen_publish_time: 2026-07-16
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Moonshot Platform Blog

- last_seen_item: Kimi 开放平台：新功能发布记录
- last_seen_publish_time: 2025-11-07
- last_successful_scan: 2026-09-14T01:00:46+08:00

## ByteDance Seed Blog

- last_seen_item: SeedRealtime 音视频全双工大模型发布：走向全模态自然交互
- last_seen_publish_time: 2026-08-05
- last_successful_scan: 2026-09-14T01:00:46+08:00

## MiniMax Blog

- last_seen_item: MiniMax Music 3.0：新一代开放权重、生产级全能音乐模型
- last_seen_publish_time: 2026-08-13
- last_successful_scan: 2026-09-14T01:00:46+08:00

## MiniMax News

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## MiniMax Model Release Notes

- last_seen_item: MiniMax H3
- last_seen_publish_time: 2026-07-31
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Tencent Hunyuan Research

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Tencent HY Research

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Hugging Face Official Blog

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## LLVM Blog

- last_seen_item: GSoC 2025: Advanced symbol resolution for Clang-Repl
- last_seen_publish_time: 2026-01-19
- last_successful_scan: 2026-09-14T01:00:46+08:00

## MaskRay

- last_seen_item: lld 23 ELF changes
- last_seen_publish_time: 2026-09-12
- last_successful_scan: 2026-09-14T01:00:46+08:00

## John Regehr

- last_seen_item: Looking for Missed Alarm Bugs in a Formal Verification Tool
- last_seen_publish_time: 2024-09-04
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Chris Lattner

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Modular Blog

- last_seen_item: Mojo is now open source!
- last_seen_publish_time: 2026-08-18
- last_successful_scan: 2026-09-14T01:00:46+08:00

## PyTorch

- last_seen_item: Helion x 🤗 HF Kernels: Building and Shipping Out-of-the-box Performant Kernels
- last_seen_publish_time: 2026-09-11
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Triton

- last_seen_item: Triton 3.8.0
- last_seen_publish_time: 2026-08-28
- last_successful_scan: 2026-09-14T01:00:46+08:00

## MLIR / LLVM Project Updates

- last_seen_item: LLVM 23.1.1
- last_seen_publish_time: 2026-09-08
- last_successful_scan: 2026-09-13T01:00:43+08:00

## vLLM

- last_seen_item: Following the Bottleneck: Optimizing MiniMax M3 Inference on AMD MI355X
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-13T01:00:43+08:00

## SGLang

- last_seen_item: SGLang and Miles Add Day-0 Support for DeepSeek-V4.1
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-12T01:07:25+08:00

## CUDA / NVIDIA Developer Technical Updates

- last_seen_item: How Full-Stack NIM Optimizations Deliver 2.5x More Users on Nemotron 3 Ultra
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-13T01:00:43+08:00

## Lilian Weng

- last_seen_item: Harness Engineering for Self-Improvement
- last_seen_publish_time: 2026-07-04
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Sebastian Raschka

- last_seen_item: GPT-6 Astra, Looped Transformers, and Hidden Reasoning
- last_seen_publish_time: 2026-09-09
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Chip Huyen

- last_seen_item: Common pitfalls when building generative AI applications
- last_seen_publish_time: 2025-01-16
- last_successful_scan: 2026-09-14T01:00:46+08:00

## GCC Releases

- last_seen_item: GCC 13.5
- last_seen_publish_time: 2026-09-11
- last_successful_scan: 2026-09-14T01:00:46+08:00

## Linux Kernel Releases

- last_seen_item: Linux 7.2.5
- last_seen_publish_time: 2026-09-11
- last_successful_scan: 2026-09-14T01:00:46+08:00

---

# Codex Usage Monitor State

- last_successful_scan: 2026-09-14T01:00:46+08:00
- last_seen_announcement: Managing usage with GPT-6 Astra in Work and Codex
- last_seen_publish_time: 2026-09-09
- last_alerted_announcement: How banked Codex resets work — September 7 global reset and GPT-6 Astra rollout banked resets

---

# Active Papers

> 上限：30。  
> 未到 `next_review` 且无重大触发事件时，不重复深评。

<!--
推荐条目格式：

## paper-id-or-short-title

- title:
- url:
- direction:
- first_seen:
- last_review:
- next_review:
- status: active
- quality: A | B | C
- maturity: M0 | M1 | M2 | M3 | M4
- personal_value: high | medium | low
- main_evidence:
  - ...
- missing_evidence:
  - ...
- known_assets:
  - ...
- next_review_focus:
  - ...
- discovery_source:
-->

## 2609.05275

- title: Don't Drop Dropout: Scaling Layer Dropout for Efficient Language Model Training and Inference
- url: https://arxiv.org/abs/2609.05275
- direction: 基础模型 / 训练效率 / 推理效率
- first_seen: 2026-09-08
- last_review: 2026-09-12
- next_review: 2026-09-17
- status: active
- quality: A
- maturity: M0
- personal_value: high
- main_evidence:
  - 2,400 余组训练实验，覆盖 271M～8.2B 参数与最多 160B tokens，并已进入 ICML 2026。
  - 作者报告在近似验证损失下最高节省 25% 训练 FLOPs，并可支持 early exit、layer skipping 与 self-speculative decoding。
- missing_evidence:
  - 尚未确认作者代码或可直接复现的训练配置。
  - 缺少常见 GPU 训练栈、超 8.2B 规模及第三方独立复现。
- known_assets:
  - 论文
  - 规模化实验与消融
- next_review_focus:
  - 代码或训练 recipe 是否发布
  - 更大模型、非 Cerebras 硬件与第三方复现
  - 推理加速的质量退化与端到端收益
- discovery_source: Hugging Face Daily Papers / arXiv recent

## 2609.04523

- title: MaxKernel: Multi-Agent Systems for Automated High-Performance TPU Kernel Generation
- url: https://arxiv.org/abs/2609.04523
- direction: AI 系统 / 编译器 / TPU kernel agent
- first_seen: 2026-09-08
- last_review: 2026-09-13
- next_review: 2026-09-18
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 作者在 50 个 JaxBench 任务及真实模型 workload 上评估多 Agent kernel 优化闭环。
  - 官方仓库已提供 MaxKernel、JAXBench、MaxCode、文档与测试资产；本次复评可见仓库已有 305 次提交。
- missing_evidence:
  - 缺少第三方复现、稳定版本及跨 TPU/Pallas 之外后端的验证。
  - 对 Gemini、Google Cloud TPU 与 compiler feedback 的依赖较强。
- known_assets:
  - 论文
  - 作者核心代码
  - JAXBench benchmark
  - 文档与测试
- next_review_focus:
  - 外部复现与真实 workload 的完整性能数据
  - 搜索轨迹、失败恢复与成本数据
  - 对其他 kernel DSL 或加速器的可迁移性
- discovery_source: Hugging Face Daily Papers / arXiv recent / 作者 GitHub

## 2609.05228

- title: ACE: Accurate and Calibration-Free Expert Skipping for Efficient MoE Inference
- url: https://arxiv.org/abs/2609.05228
- direction: MoE / 推理效率 / Serving
- first_seen: 2026-09-08
- last_review: 2026-09-13
- next_review: 2026-09-18
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 在三种 MoE LLM、八个 benchmark 上评估训练-free、calibration-free expert skipping。
  - 双代理一致才跳过且始终保留 top-1，机制比单一静态阈值更保守。
- missing_evidence:
  - 尚未确认作者代码、第三方复现或真实并发 serving 数据。
  - 缺少端到端延迟、吞吐、显存和硬件利用率的完整对照。
- known_assets:
  - 论文
- next_review_focus:
  - 代码发布与可复现实验
  - 真实 serving 栈的端到端收益
  - 不同 router、负载分布和 skipping 比例下的稳定性
- discovery_source: Hugging Face Daily Papers / arXiv recent

## 2609.04010

- title: Unlocking Lossless Speedups in LLMs via Discrete Diffusion
- url: https://arxiv.org/abs/2609.04010
- direction: LLM 推理 / speculative decoding / 离散扩散
- first_seen: 2026-09-09
- last_review: 2026-09-12
- next_review: 2026-09-17
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - Ψ-Spec 以离散扩散模型生成候选，并通过接受/拒绝机制保持原自回归模型的目标分布。
  - 作者已公开训练、推理、评测代码与多个 checkpoint，并在 8B 规模报告最高约 3× 加速。
- missing_evidence:
  - 缺少第三方独立复现和生产 serving 集成。
  - 不同 batch、KV-cache 压力、硬件和 sampler 下的完整端到端数据仍不足。
  - 与既有 diffusion-augmented LLM 路线的创新差异仍需进一步核对。
- known_assets:
  - 论文
  - 作者核心代码
  - 训练与评测 recipe
  - checkpoints
- next_review_focus:
  - 分布等价的独立验证
  - 真实并发 serving 的延迟、吞吐与显存数据
  - vLLM/SGLang 等生态集成和第三方复现
- discovery_source: Hugging Face Daily Papers / arXiv / 作者项目页与 GitHub

## 2609.08368

- title: Miles v0.1: A Full-Stack Infrastructure for Large-Scale LLM Post-Training
- url: https://arxiv.org/abs/2609.08368
- direction: LLM 后训练 / 分布式系统 / RL infrastructure
- first_seen: 2026-09-10
- last_review: 2026-09-14
- next_review: 2026-09-19
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 系统覆盖 SGLang rollout、Megatron-LM 或 PyTorch FSDP trainer、三种权重同步，以及 RL、LoRA RL、on-policy distillation、SFT 和 diffusion 路径。
  - 作者给出 64 台 GB300、GLM-5.2 744B-A40B 的全异步 terminal-coding RL 案例，前 30 步中位 step time 为 263 秒。
  - 本次复评确认核心仓库持续活跃，已包含 NVFP4 fake-QAT 融合 kernel 与 routed-expert 限定等后续提交。
- missing_evidence:
  - 大规模性能和稳定性主要来自作者自报，缺少第三方集群复现。
  - 安装复杂度、故障恢复、资源利用率和不同后端组合的完整对照仍不足。
- known_assets:
  - 论文
  - 成熟核心仓库
  - 训练与异步 recipe
  - 文档、测试和工具
- next_review_focus:
  - 第三方小规模与多节点复现
  - 异步 rollout 的 staleness、故障恢复和可重复性
  - 权重同步方式的通信开销及不同训练后端对照
- discovery_source: Hugging Face Daily Papers / arXiv / 作者 GitHub

## 2609.04971

- title: BeaconKV: Training-Free KV Cache Compression via Representative Beacon Queries
- url: https://arxiv.org/abs/2609.04971
- direction: LLM Serving / KV cache / 长上下文推理
- first_seen: 2026-09-10
- last_review: 2026-09-13
- next_review: 2026-09-18
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 通过代表性 beacon query 估计历史 token 被远距离重访的重要性，无需重新训练模型。
  - 作者在四个开放推理模型上报告最高 5.8× 显存压缩、超过 4.3× 吞吐提升，并已公开核心实现和评测脚本。
- missing_evidence:
  - 仓库提交和外部采用仍少，缺少第三方复现与生产 serving 集成。
  - 不同 batch、序列结构、硬件与 FlashAttention 版本下的收益稳定性未知。
- known_assets:
  - 论文
  - 作者核心代码
  - 评测脚本
- next_review_focus:
  - 独立长上下文与推理任务复现
  - 真实 serving 的延迟、吞吐、显存和质量 Pareto
  - vLLM/SGLang 集成及多种注意力后端兼容性
- discovery_source: Hugging Face Daily Papers / arXiv / 作者 GitHub

## 2609.10226

- title: Φ-Bench: Can Large Language Models Engineer the Infrastructure That Powers Them?
- url: https://arxiv.org/abs/2609.10226
- direction: AI 系统 / Coding Agent / Kernel / Runtime / Benchmark
- first_seen: 2026-09-11
- last_review: 2026-09-11
- next_review: 2026-09-15
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 85 个任务覆盖 55 个 kernel function completion、20 个长周期仓库实现和 10 个端到端系统优化。
  - 官方仓库提供自包含 Dockerfile、离线求解与评分、统一 runner、任务索引；75 个任务包含待修改仓库，83 个有参考解。
- missing_evidence:
  - 刚发布，缺少第三方跨硬件复现、独立基准结果和长期防污染验证。
  - 部分性能 anchor 绑定 NVIDIA H20 或 Intel Sapphire Rapids，换硬件需要重新校准。
- known_assets:
  - 论文
  - benchmark tasks
  - Docker environments
  - task runner
  - scoring and oracle assets
- next_review_focus:
  - Codex、Claude Code 等 Agent 的独立复跑结果
  - 跨 GPU/CPU 的 anchor 校准与可重复性
  - 测试泄漏、污染和任务维护机制
- discovery_source: Hugging Face Daily Papers / arXiv recent / 作者 GitHub

## 2609.08149

- title: SWE-Bench Pro Verified: A Reliable Benchmark for Software Engineering Agents
- url: https://arxiv.org/abs/2609.08149
- direction: Coding Agent / Evaluation / Benchmark Safety
- first_seen: 2026-09-11
- last_review: 2026-09-11
- next_review: 2026-09-15
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 系统识别金标准解答与隐藏评测信息泄漏造成的 reward hacking，以及错误题目描述和测试范围问题。
  - 提供 anti-hacking 与最小任务修正后的 Verified 数据，重新评测显示部分模型明显低于既有报告。
- missing_evidence:
  - 需要外部团队独立复跑并审计任务修订准则和隔离设计。
  - 尚缺长期 leaderboard 采用、污染监控和不同 harness 的系统对照。
- known_assets:
  - 论文
  - verified dataset
  - 使用文档
- next_review_focus:
  - 第三方复现与 leaderboard 迁移
  - 防泄漏机制是否影响正常 Agent 功能
  - 修订任务的一致性和持续维护流程
- discovery_source: arXiv recent / Hugging Face Daily Papers / AgentCompass

## 2609.09134

- title: Co-Evolving Harnesses and Models: On-Policy Correction Helps Weaker Models Catch Up Where Imitation Fails
- url: https://arxiv.org/abs/2609.09134
- direction: Agent / Harness / Fine-tuning / On-policy correction
- first_seen: 2026-09-11
- last_review: 2026-09-11
- next_review: 2026-09-16
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 七类企业 Agent 任务中，直接模仿专家完整轨迹让 Qwen3-Coder 和 Gemma 4 在全部任务上倒退 4～30 分。
  - 只重写较弱模型 on-policy rollout 的失败回合，可在保留原生规划风格的同时结合 harness 演化与模型适配。
- missing_evidence:
  - 尚未确认公开代码、数据或可复现 harness 配置。
  - 缺少更多模型、任务、第三方复现及总训练和推理成本数据。
- known_assets:
  - 论文
- next_review_focus:
  - 代码、任务与训练 recipe 是否发布
  - 模型—harness 不匹配的独立复现
  - 与 DAgger、局部蒸馏等 on-policy 方法的系统对照
- discovery_source: arXiv recent

## 2609.10715

- title: NCP-ArchPreview Technical Report: Moving towards Latent Space Language Models through Next Concept Prediction
- url: https://arxiv.org/abs/2609.10715
- direction: 基础模型 / 预训练 / Latent Language Model
- first_seen: 2026-09-12
- last_review: 2026-09-12
- next_review: 2026-09-16
- status: active
- quality: B
- maturity: M1
- personal_value: medium
- main_evidence:
  - 8.9B 参数模型在 5.73T Dolma-3 tokens 上联合训练 NTP 与离散 next-concept prediction，并提供参数对齐消融。
  - 作者报告以 51.3% 的 token 达到 OLMo-3-7B 最终预训练 loss，完整训练下游宏平均提升 2.45 分，并已公开模型 checkpoints。
- missing_evidence:
  - 缺少独立复现、完整训练代码和端到端训练成本审计。
  - NCP 目标、额外参数与训练数据处理各自贡献仍需外部拆分验证。
- known_assets:
  - 论文
  - 模型 checkpoints
  - 架构与消融结果
- next_review_focus:
  - 完整训练 recipe 与代码是否发布
  - 参数对齐的第三方复现
  - latent space 在领域适配和 speculative decoding 中的实际收益
- discovery_source: Hugging Face Daily Papers / arXiv recent / 官方模型资产

## 2609.05903

- title: EvoSafeHarness: Evolving Model- and Domain-Specific Harnesses for Securing Agents
- url: https://arxiv.org/abs/2609.05903
- direction: Agent / Safety / Harness / Tool Use
- first_seen: 2026-09-12
- last_review: 2026-09-12
- next_review: 2026-09-17
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 对冻结 victim model 联合搜索自然语言 policy 与三个可执行 tool-call hook，并用 fresh-context adversary 抑制 benchmark 字面过拟合。
  - 作者在四类 Agent benchmark 上报告更好的安全—效用前沿；官方仓库提供三类领域、冻结划分、评测平台和可运行 bundle。
- missing_evidence:
  - 结果仍以作者自报为主，缺少第三方复现和跨更多真实业务域验证。
  - 搜索依赖外部模型、judge、Docker 与 DecodingTrust-Agent，成本和可移植性尚不清晰。
- known_assets:
  - 论文
  - 作者核心代码
  - domain specs 与冻结 splits
  - evaluation platform
- next_review_focus:
  - 第三方复现与自适应攻击下的稳定性
  - harness 搜索成本、误拒绝与迁移性
  - 在生产 Agent 权限系统中的集成
- discovery_source: Hugging Face Daily Papers / arXiv / 作者 GitHub

## 2608.27875

- title: HyQuant: Hybrid-Precision Quantization for LLM Attention
- url: https://arxiv.org/abs/2608.27875
- direction: LLM Serving / Attention / KV cache / 低比特量化
- first_seen: 2026-09-12
- last_review: 2026-09-12
- next_review: 2026-09-17
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 保留 top-5% 垂直线 token 与局部窗口为高精度，其余 attention/KV cache 低比特化，并以 Triton 融合反量化和 attention。
  - 作者在多种 8B～32B 模型上报告近全精度质量、1.32～3.58 倍 decode kernel 加速和 1.04～1.17 倍端到端 decode 加速。
- missing_evidence:
  - 所有论文实验均在单张 H100 80GB 上完成，缺少第三方、跨硬件和并发 serving 复现。
  - 仓库提交历史很短，尚无 vLLM/SGLang 等生产框架集成。
- known_assets:
  - 论文
  - Triton kernels
  - model patches 与 hybrid KV cache
  - evaluation scripts 与 smoke test
- next_review_focus:
  - 独立质量—显存—延迟复现
  - 并发与 batch 场景的端到端收益
  - vLLM/SGLang 集成和跨 GPU 支持
- discovery_source: Hugging Face Daily Papers / arXiv / 作者 GitHub

## 2609.11917

- title: Data Scarcity and Model Sparsity: Mixtures-of-Experts Overfit More to Repeated Data
- url: https://arxiv.org/abs/2609.11917
- direction: 基础模型 / MoE / 数据效率 / 训练稳定性
- first_seen: 2026-09-13
- last_review: 2026-09-13
- next_review: 2026-09-17
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 对约 80M～1B active parameters、最高 8.5B total parameters 的 dense 与 MoE 模型进行重复数据对照。
  - 作者发现 MoE 在约 4 次重复后即明显受损，重复 32 次后基本丧失相对 dense 的优势；强 masking 可缓解但不能替代独特数据。
- missing_evidence:
  - 尚未确认公开代码、训练 recipe 或第三方独立复现。
  - 需要在更多 router、数据组成、模型规模和训练预算下验证结论边界。
- known_assets:
  - 论文
  - 多规模实验与消融
- next_review_focus:
  - 代码和训练配置是否发布
  - 路由固化、专家专门化与泛化退化的独立验证
  - 数据去重、masking 与其他正则方法的系统对照
- discovery_source: arXiv recent

## 2609.11294

- title: Memory Compression for High-Fanout Agent Sandboxes
- url: https://arxiv.org/abs/2609.11294
- direction: Agent Infrastructure / Sandbox / Operating Systems / Memory
- first_seen: 2026-09-13
- last_review: 2026-09-13
- next_review: 2026-09-17
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 利用模板内、模板间和沙箱间的页冗余，并把压缩安排到 LLM 等待阶段、在恢复路径预取。
  - 作者报告沙箱内存容量最高提升 8.7 倍，Linux 基线为 2.1 倍，并把激进压缩 slowdown 从 3.1 倍降至 1.40 倍。
- missing_evidence:
  - 尚未确认公开实现、可复现 workload 或第三方验证。
  - 页共享边界、尾延迟、压缩 CPU 成本和多租户隔离影响仍需审计。
- known_assets:
  - 论文
  - 系统设计与作者评测
- next_review_focus:
  - 代码、工作负载和复现脚本是否发布
  - 与写时复制、快照和常规内存压缩的完整对照
  - 高并发下的恢复尾延迟、CPU 成本与隔离安全
- discovery_source: arXiv recent

---

# Active GitHub

> 上限：20。  
> 未到 `next_review` 且无重大触发事件时，不重复深评。

<!--
推荐条目格式：

## owner/repo

- repo:
- url:
- direction:
- first_seen:
- last_review:
- next_review:
- status: active
- quality: A | B | C
- personal_value: high | medium | low
- last_release:
- last_commit_or_major_delta:
- main_evidence:
  - ...
- missing_evidence:
  - ...
- known_assets:
  - core code
  - demo
  - benchmark
- next_review_focus:
  - ...
- discovery_source:
-->

## tenstorrent/vllm-tt-plugin

- repo: tenstorrent/vllm-tt-plugin
- url: https://github.com/tenstorrent/vllm-tt-plugin
- direction: LLM Serving / 异构加速器 / vLLM plugin
- first_seen: 2026-09-08
- last_review: 2026-09-12
- next_review: 2026-09-17
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-09-07 vLLM 官方发布 TT Plugin 技术介绍，仓库已有可运行实现
- main_evidence:
  - 以 out-of-tree plugin 接入 Tenstorrent，覆盖平台发现、模型注册、worker、scheduler 与执行桥。
  - 公开代码、文档、示例与测试，明确实现 phase-only scheduling、片上采样回退、异步 readback 和单进程 lane-DP。
- missing_evidence:
  - 官方文章未提供统一、可审计的端到端性能表，且硬件验证门槛较高。
  - 暂不支持 speculative decoding、LoRA 与多机 serving，混合模型数据并行尚未完成硬件验证。
- known_assets:
  - core code
  - docs
  - examples
  - tests
- next_review_focus:
  - 首个稳定 release 与 vLLM 版本兼容性
  - 可复现吞吐、延迟和成本 benchmark
  - speculative decoding、LoRA、多机与 hybrid DP 支持
- discovery_source: vLLM 官方博客 / GitHub

## AI-Hypercomputer/accelerator-agents

- repo: AI-Hypercomputer/accelerator-agents
- url: https://github.com/AI-Hypercomputer/accelerator-agents
- direction: AI 系统 / 编译器 / 自动 kernel 优化
- first_seen: 2026-09-08
- last_review: 2026-09-13
- next_review: 2026-09-18
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-09-03 MaxKernel 论文与对应代码公开
- main_evidence:
  - 仓库包含 MaxKernel、JAXBench、MaxCode、文档、CI 与测试，不是仅有论文说明；本次复评可见 305 次提交。
  - 将生成、编译、正确性测试、profiling 和迭代改写组成可测量的多 Agent 闭环。
- missing_evidence:
  - 缺少独立复现、稳定 release 与 TPU/Pallas 之外的可迁移性证据。
  - 作者结果尚未给出足以判断总搜索成本与失败率的完整外部验证。
- known_assets:
  - core code
  - benchmark
  - docs
  - tests
- next_review_focus:
  - 第三方复现与真实模型 workload 结果
  - 完整搜索轨迹、成本、失败恢复和可重复性
  - 对 CUDA/Triton 或其他 kernel DSL 的扩展
- discovery_source: Hugging Face Daily Papers / arXiv / GitHub

## NVlabs/cuda-oxide

- repo: NVlabs/cuda-oxide
- url: https://github.com/NVlabs/cuda-oxide
- direction: GPU 编译器 / Rust / CUDA SIMT kernel
- first_seen: 2026-09-09
- last_review: 2026-09-13
- next_review: 2026-09-18
- status: active
- quality: B
- personal_value: high
- last_release: v0.2.1（2026-06-10）
- last_commit_or_major_delta: 2026-09-11 修复 CUDA-GDB full-debug 状态并更新文档
- main_evidence:
  - 仓库包含 rustc codegen backend、host runtime、device intrinsics、文档、示例和测试。
  - 编译流水线可追到 Rust MIR → Pliron IR → LLVM IR → PTX，并提供类型化 launch 与内存安全约束。
- missing_evidence:
  - 仍属 experimental，依赖 pinned nightly Rust，平台与硬件兼容范围有限。
  - 缺少跨 workload、跨硬件的独立性能与稳定性验证。
- known_assets:
  - core code
  - runtime
  - book/docs
  - examples
  - tests
- next_review_focus:
  - 稳定 release、Rust 版本与 CUDA 兼容性
  - 编译质量和真实 kernel benchmark
  - 跨语言互操作与生产采用
- discovery_source: NVIDIA Developer Blog / GitHub

## NVlabs/cutile-rs

- repo: NVlabs/cutile-rs
- url: https://github.com/NVlabs/cutile-rs
- direction: GPU 编程 / Rust / tile-level DSL
- first_seen: 2026-09-09
- last_review: 2026-09-13
- next_review: 2026-09-18
- status: active
- quality: B
- personal_value: high
- last_release: v0.3.1（2026-09-06）
- last_commit_or_major_delta: 2026-09-08 NVIDIA 官方发布 CUDA Rust 双路线技术介绍
- main_evidence:
  - 仓库提供稳定 Rust 上的 tile DSL、CUDA Tile IR JIT、host-side ownership API、示例与文档。
  - NVIDIA 官方文章确认 Hugging Face Grout 与 mistral.rs 已采用。
- missing_evidence:
  - 仍处早期阶段，API 会变化且当前要求 CUDA 13.3。
  - 缺少独立的综合 benchmark 和生产稳定性证据。
- known_assets:
  - core code
  - crate
  - docs
  - examples
- next_review_focus:
  - API 稳定性与 CUDA 版本兼容性
  - 和 Triton/CUDA C++ 的可复现性能对照
  - 生态采用与跨语言互操作
- discovery_source: NVIDIA Developer Blog / GitHub

## ifm-ai/uno

- repo: ifm-ai/uno
- url: https://github.com/ifm-ai/uno
- direction: LLM 推理 / speculative decoding / 离散扩散
- first_seen: 2026-09-09
- last_review: 2026-09-12
- next_review: 2026-09-17
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-09-03 论文、代码与 checkpoint 公开，本期按成熟证据补充纳入
- main_evidence:
  - 仓库包含 nano_vllm_uno 推理引擎、linear/tree sampler、conditional-LoRA 训练、评测脚本与示例。
  - 已发布多个 checkpoint，可直接核对采样正确性和作者性能主张。
- missing_evidence:
  - 缺少第三方复现、稳定 release 与生产 serving 集成。
  - 对真实 batch、KV-cache 压力、不同硬件和依赖版本的完整验证不足。
- known_assets:
  - core code
  - training recipe
  - evaluation
  - examples
  - checkpoints
- next_review_focus:
  - 分布等价与速度收益的独立复现
  - 真实并发 serving 的延迟—吞吐 Pareto
  - vLLM/SGLang 集成、依赖兼容性与稳定 release
- discovery_source: Hugging Face Daily Papers / arXiv / 作者项目页与 GitHub

## openai/NavierStokesAndEuler

- repo: openai/NavierStokesAndEuler
- url: https://github.com/openai/NavierStokesAndEuler
- direction: AI Scientist / 形式化验证 / 数学
- first_seen: 2026-09-10
- last_review: 2026-09-13
- next_review: 2026-09-18
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-09-10 新增第二次公开提交，未见可确认的外部审查结论
- main_evidence:
  - 仓库包含 Lean 4.34.0-rc2 工程，按 NavierStokes、Euler 与 ComparatorChallenges 组织核心形式化内容。
  - 提供 Mathlib 缓存和完整构建路径，可由外部研究者独立运行 proof kernel 检查。
- missing_evidence:
  - 目前仅有两次公开提交，尚无独立数学审查或社区验证记录。
  - Lean 证明项通过不能自动保证形式化陈述完整对应千禧年问题的预期语义。
- known_assets:
  - core formalization
  - build instructions
  - accompanying paper
- next_review_focus:
  - 流体力学专家与 Lean 社区的独立审查
  - 自然语言论文和 Lean 定理在定义、假设、结论上的逐项对应
  - 后续修订、issue 与可重复构建结果
- discovery_source: OpenAI 官方研究发布 / GitHub

## radixark/miles

- repo: radixark/miles
- url: https://github.com/radixark/miles
- direction: LLM 后训练 / 分布式系统 / RL infrastructure
- first_seen: 2026-09-10
- last_review: 2026-09-14
- next_review: 2026-09-19
- status: active
- quality: B
- personal_value: high
- last_release: Miles v0.1（2026-08）
- last_commit_or_major_delta: 2026-09-11 新增 fused NVFP4 fake-QAT QDQ kernels，并将 NVFP4 RL 限定到 routed experts
- main_evidence:
  - 包含训练入口、同步与异步执行、SGLang rollout、Megatron-LM/FSDP trainer、三种权重同步、文档和测试。
  - 作者展示 64 台 GB300 上 GLM-5.2 744B-A40B 的全异步 terminal-coding RL 案例。
  - 本次复评可见 2,175 次提交，近期仍在补充低精度训练 kernel、真实沙箱 CI 和硬件测试矩阵。
- missing_evidence:
  - 超大规模性能、可靠性和资源效率仍主要来自作者自报。
  - 缺少第三方跨集群复现、稳定性报告及不同后端组合的系统对照。
- known_assets:
  - core code
  - training recipes
  - async runtime
  - docs
  - tests
- next_review_focus:
  - 小规模可复现 recipe 与多节点第三方结果
  - rollout staleness、容错和权重同步开销
  - SGLang、Megatron-LM 与 FSDP 版本兼容性
- discovery_source: Hugging Face Daily Papers / arXiv / GitHub

## openai/codex

- repo: openai/codex
- url: https://github.com/openai/codex
- direction: Coding Agent / Harness / Sandbox / Developer Infrastructure
- first_seen: 2026-09-11
- last_review: 2026-09-11
- next_review: 2026-09-16
- status: active
- quality: A
- personal_value: high
- last_release: 本期触发来自 Agents API 集成，不以普通版本 release 为依据
- last_commit_or_major_delta: 2026-09-10 OpenAI 宣布 Agents API 由开源 Codex harness 驱动
- main_evidence:
  - 成熟 Rust 主体仓库，包含 codex-rs、CLI、SDK、文档、工具、测试与长期提交历史。
  - 官方将其定位为 Agents API 的开源 harness 基础，可对照托管服务理解模型、工具、上下文和 sandbox 的边界。
- missing_evidence:
  - 托管 API 与公开仓库不完全等价，服务端调度、隔离和运维实现并未全部开源。
  - 仍需核对具体 Agents API harness 版本与仓库 revision 的对应关系。
- known_assets:
  - core code
  - CLI
  - SDK
  - docs
  - tests
- next_review_focus:
  - Agents API 与开源 harness 的版本映射
  - session、compaction、tool search 与 sandbox 行为差异
  - 托管和自建路径的可靠性、成本及可观测性
- discovery_source: OpenAI Agents API 官方发布 / GitHub

## one2piece2hello/faibench_Frontier_InfraBench

- repo: one2piece2hello/faibench_Frontier_InfraBench
- url: https://github.com/one2piece2hello/faibench_Frontier_InfraBench
- direction: AI 系统 / Coding Agent / Kernel / Runtime / Benchmark
- first_seen: 2026-09-11
- last_review: 2026-09-11
- next_review: 2026-09-15
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-09-09 论文与 85 项可运行 benchmark 资产公开
- main_evidence:
  - 提供 85 个基础设施工程任务、自包含 Dockerfile、离线评分、统一 runner、任务索引和参考解。
  - 任务跨 kernel 补全、长周期仓库实现和端到端优化，runner 可直接接入 Codex 或 Claude Code。
- missing_evidence:
  - 仓库和论文刚发布，缺少第三方复跑、跨硬件校准和稳定维护历史。
  - 部分性能任务的硬件 anchor 可迁移性有限，公开评分面也需要持续防污染。
- known_assets:
  - benchmark
  - Docker environments
  - task runner
  - scoring
  - oracle solutions
- next_review_focus:
  - 独立 Agent 评测结果与失败分类
  - Docker 可复现性及硬件重新校准
  - 任务修订、污染检测和稳定 release
- discovery_source: Hugging Face Daily Papers / arXiv / GitHub

## jerrysfls/HyQuant

- repo: jerrysfls/HyQuant
- url: https://github.com/jerrysfls/HyQuant
- direction: LLM Serving / Attention / KV cache / Triton
- first_seen: 2026-09-12
- last_review: 2026-09-12
- next_review: 2026-09-17
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-09-11 论文官方实现公开并进入 Hugging Face Daily Papers 发现面
- main_evidence:
  - 提供 Qwen3、Llama 3 与 GLM-4 patch、融合 Triton attention、混合低比特 KV cache、评测脚本和 smoke test。
  - 作者把 kernel 加速与端到端 decode 收益分开报告，并明确垂直线检测和高精度保留的额外开销。
- missing_evidence:
  - 仓库仅有少量提交，未发现稳定 release、第三方复现或生产采用。
  - 论文实验限定单张 H100，尚缺并发 serving、跨 GPU 和框架集成验证。
- known_assets:
  - core code
  - Triton kernels
  - model patches
  - evaluation
  - smoke test
- next_review_focus:
  - 第三方端到端复现
  - vLLM/SGLang integration
  - batch、并发与跨硬件性能
- discovery_source: Hugging Face Daily Papers / arXiv / GitHub

---

# Long-term Watchlist

> 上限：20。  
> 保存长期值得观察，但当前不需要频繁复评的项目、论文或方向。

<!--
## item-id

- type: paper | github | project | ecosystem
- title:
- url:
- direction:
- last_review:
- next_review:
- watch_reason:
- trigger_events:
  - major release
  - code release
  - benchmark
  - third-party reproduction
-->

---

# Recent High-value Archive

> 上限：20。  
> 保存近期已经完成重点分析、短期内不需要重复介绍的高价值项目。

<!--
## item-id

- type:
- title:
- url:
- archived_at:
- quality:
- maturity:
- personal_value:
- key_conclusion:
- reconsider_if:
-->

---

# Low-value / Deferred

> 低价值或当前证据不足的条目只保留最小状态，避免重复扫描和重复深评。

<!--
- id:
  reason:
  reconsider_after:
-->

---

# Maintenance Notes

## 可提前触发复评的事件

- code release
- model release
- checkpoint release
- dataset release
- major revision
- 新 benchmark
- 第三方 reproduction
- 重要 adoption
- major release
- 显著性能变化
- 显著架构变化
- Transformers / vLLM / SGLang 等关键生态正式支持

## 状态规模约束

- Active Paper ≤ 30
- Active GitHub ≤ 20
- Long-term Watchlist ≤ 20
- Recent High-value Archive ≤ 20

## Evidence Maturity

- M0：刚发布
- M1：作者代码 / 数据 / checkpoint
- M2：外部使用反馈
- M3：独立验证
- M4：生态影响
