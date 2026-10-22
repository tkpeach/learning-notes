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

- last_seen_item: Introducing the Australian Youth Safety Blueprint
- last_seen_publish_time: 2026-09-18
- last_successful_scan: 2026-09-22T01:07:00+08:00

## OpenAI Index

- last_seen_item: Introducing the Australian Youth Safety Blueprint
- last_seen_publish_time: 2026-09-18
- last_successful_scan: 2026-09-22T01:07:00+08:00

## OpenAI Product

- last_seen_item: Reimagining advertising with AI
- last_seen_publish_time: 2026-09-16
- last_successful_scan: 2026-09-18T01:12:00+08:00

## OpenAI Research

- last_seen_item: Build more natural voice experiences with GPT‑Live‑1 in the API
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-18T01:12:00+08:00

## OpenAI Engineering

- last_seen_item: How we built ChatGPT’s novel ad stack for user trust and relevance
- last_seen_publish_time: 2026-10-21
- last_successful_scan: 2026-10-22T01:11:16+08:00

## OpenAI Safety

- last_seen_item: Our framework for reporting model misalignment
- last_seen_publish_time: 2026-09-16
- last_successful_scan: 2026-09-18T01:12:00+08:00

## OpenAI Security

- last_seen_item: Patch the Planet: global response coordination as agents uncover critical vulnerabilities
- last_seen_publish_time: 2026-10-21
- last_successful_scan: 2026-10-22T01:11:16+08:00

## OpenAI Global Affairs

- last_seen_item: Europe’s opportunity to deepen AI use
- last_seen_publish_time: 2026-10-14
- last_successful_scan: 2026-10-22T01:11:16+08:00

## Google DeepMind Blog

- last_seen_item: Introducing Gemini 3.8 Flash and 3.8 Flash Cyber
- last_seen_publish_time: 2026-09-02
- last_successful_scan: 2026-09-24T01:12:00+08:00

## Anthropic Newsroom

- last_seen_item: Physicist Christopher Stubbs joins Anthropic's Long-Term Benefit Trust
- last_seen_publish_time: 2026-10-21
- last_successful_scan: 2026-10-22T01:11:16+08:00

## Claude Blog

- last_seen_item: How Cresta turned CX expertise into an agent builder on the Claude Agent SDK
- last_seen_publish_time: 2026-10-05
- last_successful_scan: 2026-10-06T01:36:00+08:00

## DeepSeek Updates

- last_seen_item: Opening up the in-house search API
- last_seen_publish_time: 2026-10-17
- last_successful_scan: 2026-10-22T01:11:16+08:00

## DeepSeek Homepage

- last_seen_item: DeepSeek-V4.1-Flash-1017 更新与 Search/Fetch API
- last_seen_publish_time: 2026-10-17
- last_successful_scan: 2026-10-22T01:11:16+08:00

## DeepSeek Official Zhihu

- last_seen_item: 未初始化
- last_seen_publish_time: 未初始化
- last_successful_scan: 未完成

## DeepSeek Official X

- last_seen_item: 未初始化
- last_seen_publish_time: 未初始化
- last_successful_scan: 未完成

## Qwen Blog

- last_seen_item: Qwen3.8-LiveTranslate: Names the speaker. Carries the meaning.
- last_seen_publish_time: 2026-09-18
- last_successful_scan: 2026-09-21T01:10:00+08:00

## Qwen Chinese Blog

- last_seen_item: Qwen3Guard：实时安全，逐词响应
- last_seen_publish_time: 2025-09-23
- last_successful_scan: 2026-10-22T01:11:16+08:00

## Aliyun Model Studio New Models

- last_seen_item: xiaomi/mimo-v2.6-pro-ultraspeed
- last_seen_publish_time: 2026-10-19
- last_successful_scan: 2026-10-22T01:11:16+08:00

## ModelScope Qwen

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Zhipu Research

- last_seen_item: Toward Recursive Self-Improvement: How GLM Built Its Own Inference Infrastructure
- last_seen_publish_time: 2026-09-17
- last_successful_scan: 2026-09-21T01:06:00+08:00

## Kimi Blog

- last_seen_item: Kimi K3
- last_seen_publish_time: 2026-07-16
- last_successful_scan: 2026-10-22T01:11:16+08:00

## Moonshot Platform Blog

- last_seen_item: Kimi 开放平台：新功能发布记录
- last_seen_publish_time: 2025-11-07
- last_successful_scan: 2026-10-22T01:11:16+08:00

## ByteDance Seed Blog

- last_seen_item: SeedRealtime 音视频全双工大模型发布：走向全模态自然交互
- last_seen_publish_time: 2026-08-05
- last_successful_scan: 2026-09-21T01:06:00+08:00

## MiniMax Blog

- last_seen_item: MiniMax M3.1 Flash：重新定义 Agent 的性能与成本
- last_seen_publish_time: 2026-10-19
- last_successful_scan: 2026-10-21T01:11:54+08:00

## MiniMax News

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## MiniMax Model Release Notes

- last_seen_item: MiniMax M3.1 Flash
- last_seen_publish_time: 2026-10-19
- last_successful_scan: 2026-10-22T01:11:16+08:00

## Tencent Hunyuan Research

- last_seen_item: From LR to ELR: A Better Heuristic for Pretraining Dynamics
- last_seen_publish_time: 2026-08-10
- last_successful_scan: 2026-09-21T01:10:00+08:00

## Tencent HY Research

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Hugging Face Official Blog

- last_seen_item: Impactful scheduling for GPU clusters
- last_seen_publish_time: 2026-10-09
- last_successful_scan: 2026-10-15T01:08:00+08:00

## LLVM Blog

- last_seen_item: Static Memory Planner for MLIR: A GSoC 2026 Journey
- last_seen_publish_time: 2026-10-19
- last_successful_scan: 2026-10-22T01:11:16+08:00

## MaskRay

- last_seen_item: Who pays for Clang
- last_seen_publish_time: 2026-10-12
- last_successful_scan: 2026-10-22T01:11:16+08:00

## John Regehr

- last_seen_item: Looking for Missed Alarm Bugs in a Formal Verification Tool
- last_seen_publish_time: 2024-09-04
- last_successful_scan: 2026-10-22T01:11:16+08:00

## Chris Lattner

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Modular Blog

- last_seen_item: Nurturing the Modular ecosystem: the Modular Community Grant Program
- last_seen_publish_time: 2026-10-09
- last_successful_scan: 2026-10-22T01:11:16+08:00

## PyTorch

- last_seen_item: Introducing TorchTPU
- last_seen_publish_time: 2026-10-20
- last_successful_scan: 2026-10-22T01:11:16+08:00

## Triton

- last_seen_item: Triton 3.8.0
- last_seen_publish_time: 2026-08-28
- last_successful_scan: 2026-10-22T01:11:16+08:00

## MLIR / LLVM Project Updates

- last_seen_item: LLVM 23.1.1
- last_seen_publish_time: 2026-09-08
- last_successful_scan: 2026-09-18T01:12:00+08:00

## vLLM

- last_seen_item: Day-0 Support for Flint on vLLM
- last_seen_publish_time: 2026-10-21
- last_successful_scan: 2026-10-22T01:11:16+08:00

## SGLang

- last_seen_item: SGLang and Miles Add Day-0 Support for DeepSeek-V4.1
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-21T01:06:00+08:00

## SGLang GitHub Releases

- last_seen_item: v0.5.22
- last_seen_publish_time: 2026-10-19
- last_successful_scan: 2026-10-22T01:11:16+08:00

## CUDA / NVIDIA Developer Technical Updates

- last_seen_item: How SWE-Serve Exposes the Gap Between Local Tests and Live Serving
- last_seen_publish_time: 2026-09-23
- last_successful_scan: 2026-09-24T01:12:00+08:00

## Lilian Weng

- last_seen_item: Harness Engineering for Self-Improvement
- last_seen_publish_time: 2026-07-04
- last_successful_scan: 2026-10-22T01:11:16+08:00

## Sebastian Raschka

- last_seen_item: Language Models for Text Classification: From Bag-of-Words to Jev
- last_seen_publish_time: 2026-09-29
- last_successful_scan: 2026-10-22T01:11:16+08:00

## Chip Huyen

- last_seen_item: Common pitfalls when building generative AI applications
- last_seen_publish_time: 2025-01-16
- last_successful_scan: 2026-10-22T01:11:16+08:00

## GCC Releases

- last_seen_item: GCC 13.5
- last_seen_publish_time: 2026-09-11
- last_successful_scan: 2026-10-22T01:11:16+08:00

## Linux Kernel Releases

- last_seen_item: Linux 7.2.6
- last_seen_publish_time: 2026-09-14
- last_successful_scan: 2026-09-21T01:06:00+08:00

---

# Codex Usage Monitor State

- last_successful_scan: 2026-10-18T01:05:00+08:00
- last_seen_announcement: OpenAI Pro plans update — Pro 500 highest included usage and Astra Ultrafast; new non-grandfathered Pro 200 subscriptions have lower included usage, existing eligible Pro 200 allowance retained through 2026-10-29
- last_seen_publish_time: 2026-09-30
- last_alerted_announcement: OpenAI Pro plans update — Pro 500 highest included usage and Astra Ultrafast; new non-grandfathered Pro 200 subscriptions have lower included usage, existing eligible Pro 200 allowance retained through 2026-10-29

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

- title: Don't Drop Dropout: Optimizing Layer Sparsity for Efficient LLM Training and Inference
- url: https://arxiv.org/abs/2609.05275
- direction: 基础模型 / 训练效率 / 推理效率
- first_seen: 2026-09-08
- last_review: 2026-10-20
- next_review: 2026-10-27
- status: active
- quality: A
- maturity: M0
- personal_value: high
- main_evidence:
  - 2,400 余组训练实验，覆盖 271M～8.2B 参数与最多 160B tokens，并已进入 ICML 2026。
  - 作者报告在近似验证损失下最高节省 25% 训练 FLOPs，并可支持 early exit、layer skipping 与 self-speculative decoding。
  - 2026-10-09 核对 arXiv 仍仅有 2026-09-04 的 v1；修正状态中的论文标题，未发现新修订。
- missing_evidence:
  - 2026-10-02 定向检索仍未确认作者公开训练代码、完整 recipe 或跨 Cerebras 平台复跑。
  - 尚未确认作者代码或可直接复现的训练配置。
  - 缺少常见 GPU 训练栈、超 8.2B 规模及第三方独立复现。
  - 2026-09-23 复评仍未确认官方代码、训练 recipe 或第三方复现。
- known_assets:
  - 论文
  - 规模化实验与消融
- next_review_focus:
  - 代码或训练 recipe 是否发布
  - 更大模型、非 Cerebras 硬件与第三方复现
  - 推理加速的质量退化与端到端收益
- discovery_source: Hugging Face Daily Papers / arXiv recent
- last_review_result: 2026-10-20 arXiv 仍为 v1（09-04）；未确认公开代码或独立非 Cerebras 复跑，保留 A/M0，不因到期自动升级。

## 2609.04523

- title: MaxKernel: Agentic Kernel Generation for TPUs
- url: https://arxiv.org/abs/2609.04523
- direction: AI 系统 / 编译器 / TPU kernel agent
- first_seen: 2026-09-08
- last_review: 2026-10-22
- next_review: 2026-10-29
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 作者在 50 个 JaxBench 任务及真实模型 workload 上评估多 Agent kernel 优化闭环。
  - 官方仓库已提供 MaxKernel、JAXBench、MaxCode、文档与测试资产；2026-09-24 复评可见仓库已有 311 次提交，但未见稳定 release 或独立复现。
  - 2026-10-01 复评官方仓库仍公开 MaxKernel、JAXBench 和文档，累计 316 次提交；未确认稳定 release 或第三方 TPU 复现。
  - 2026-10-08 核对论文仍为 9 月版本，未见足以改变质量等级的新独立复现；继续观察。
  - 2026-10-15 复核 arXiv 仍为 9 月 3 日 v1，作者代码位于 AI-Hypercomputer/accelerator-agents/MaxKernel；未确认稳定 release 或第三方 TPU 复跑。
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
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。作者 accelerator-agents 代码仍公开，release 为空；未确认独立 TPU 复跑。

## 2609.05228

- title: ACE: Adaptive Calibration-Free Expert Skipping for MoE-based LLMs
- url: https://arxiv.org/abs/2609.05228
- direction: MoE / 推理效率 / Serving
- first_seen: 2026-09-08
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。公开资产与第三方复现仍待进一步确认；维持原评级与成熟度。
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
  - 本次复评未确认新增作者代码或第三方 serving 复现。
  - 2026-09-23 复评仍未确认公开实现或独立端到端数据。
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
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。ifm-ai/uno 作者实现仍公开，未核实新的独立端到端复现。
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
  - 2026-09-23 复评确认官方仓库和 checkpoints 持续可用，但未见稳定 release、生产集成或独立复现。
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

- title: Miles v0.1: Production-Level Post-Training
- url: https://arxiv.org/abs/2609.08368
- direction: LLM 后训练 / 分布式系统 / RL infrastructure
- first_seen: 2026-09-10
- last_review: 2026-10-20
- next_review: 2026-10-27
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 2026-10-13 复评：论文仍为 9 月 8 日 v1；对应 Miles v0.1.2 已发布，新增 torchtitan 共享训练接口、实验性 Kubernetes、多策略作业与 score centering，尚不能据此验证论文所述大规模性能。
  - 系统覆盖 SGLang rollout、Megatron-LM 或 PyTorch FSDP trainer、三种权重同步，以及 RL、LoRA RL、on-policy distillation、SFT 和 diffusion 路径。
  - 2026-09-26 v0.1.1 release 增加 Qwen3.8-Flash-Next、GLM-5.3-Flash 的权重更新相等与短程 rollout/trainer 对数概率差记录；长训和跨集群结论仍未独立复现。
  - 作者给出 64 台 GB300、GLM-5.2 744B-A40B 的全异步 terminal-coding RL 案例，前 30 步中位 step time 为 263 秒。
  - 本次复评确认核心仓库持续活跃，已包含 NVFP4 fake-QAT 融合 kernel 与 routed-expert 限定等后续提交。
  - 2026-10-06 复评：arXiv 仍为 9 月 8 日 v1；对应 Miles 仓库最新正式版仍是 9 月 26 日 v0.1.1，暂未见足以改变论文结论的独立验证。
- missing_evidence:
  - 大规模性能和稳定性主要来自作者自报，缺少第三方集群复现。
  - 安装复杂度、故障恢复、资源利用率和不同后端组合的完整对照仍不足。
  - 本次复评只确认 v0.1.0 仍为最新发布，未见独立集群复现。
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
- last_review_result: 2026-10-20 arXiv 仍为 v1（09-08）；Miles 最新稳定版仍为 v0.1.2（10-09），未确认独立完整 RL 训练复现，维持 B/M1。

## 2609.04971

- title: BeaconKV: Key-Value Cache Compression Guided by Beacon Queries for Efficient Large Reasoning Model Inference
- url: https://arxiv.org/abs/2609.04971
- direction: LLM Serving / KV cache / 长上下文推理
- first_seen: 2026-09-10
- last_review: 2026-10-17
- next_review: 2026-10-24
- last_review_result: 2026-10-17 定向核验未确认足以改变评级或单独推荐的新增证据。
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 通过代表性 beacon query 估计历史 token 被远距离重访的重要性，无需重新训练模型。
  - 作者在四个开放推理模型上报告最高 5.8× 显存压缩、超过 4.3× 吞吐提升，并已公开核心实现和评测脚本。
- missing_evidence:
  - 2026-10-02 官方仓库仍仅两次提交；评测脚本可运行，但未确认生产 serving 集成或可核验的独立同条件复跑。
  - 仓库提交和外部采用仍少，缺少第三方复现与生产 serving 集成。
  - 不同 batch、序列结构、硬件与 FlashAttention 版本下的收益稳定性未知。
  - 本次复评未确认独立 benchmark 或正式 serving 集成。
  - 2026-09-23 复评确认仓库仍提供 SeerAttention-R/simple-evals 路径和配置，但未见新的独立结果。
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
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v2（10-15）；本轮未确认足以改变等级的新证据。作者 Phi-Bench 仍有85项任务与离线评分；未确认新的独立完整复跑。
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
  - 2026-09-15 复评未发现新的独立 Agent 复跑、跨硬件校准或稳定 release。
  - 2026-09-20 复评未发现新的独立复跑、跨硬件校准或正式 leaderboard。
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
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v3（10-09）；本轮未确认足以改变等级的新证据。公开资产与第三方复现仍待进一步确认；维持原评级与成熟度。
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
  - 2026-09-15 复评仅发现解读文章与论文结果复述，未发现独立全量复跑或 leaderboard 迁移。
  - 2026-09-20 复评出现新的外部解读，但仍未确认独立全量复跑、修订审计或正式 leaderboard 迁移。
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
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。公开资产与第三方复现仍待进一步确认；维持原评级与成熟度。
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
  - 2026-09-16 复评仅发现领域索引收录，未发现作者代码、训练 recipe 或独立复跑。
  - 2026-09-21 复评仍未发现作者代码、数据、训练 recipe 或独立复现；论文页面也未出现可执行资产。
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
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。ncp_olmo_eval 最新稳定仍0.1.1；不等于训练或分数的独立复现。
- status: active
- quality: B
- maturity: M1
- personal_value: medium
- main_evidence:
  - 8.9B 参数模型在 5.73T Dolma-3 tokens 上联合训练 NTP 与离散 next-concept prediction，并提供参数对齐消融。
  - 作者报告以 51.3% 的 token 达到 OLMo-3-7B 最终预训练 loss，完整训练下游宏平均提升 2.45 分，并已公开模型 checkpoints。
  - 新公开 `LUMIA-Group/ncp_olmo_eval` 0.1.1，提供 vLLM 插件、不可变模型注册、固定 seed/prompt 和 GSM8K、SciQ、Core88、RULER、HELMET 的 fail-closed 评测流程；17 个公开 checkpoint 已完成加载 smoke test。
  - 2026-09-22 复核作者评测仓库与公开检索，未见完整训练 recipe 或独立参数对齐复现，原有等级不变。
- missing_evidence:
  - 缺少独立复现、完整训练代码和端到端训练成本审计。
  - NCP 目标、额外参数与训练数据处理各自贡献仍需外部拆分验证。
  - 新评测仓库仍属作者团队资产，且 load/route smoke 不等同于分数复现或原生后端等价。
- known_assets:
  - 论文
  - 模型 checkpoints
  - 架构与消融结果
  - vLLM 评测与长上下文 benchmark 工具
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
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v2（10-14）；本轮未确认足以改变等级的新证据。SaFo-Lab/EvoSafeHarness 的作者代码可访问，未确认独立安全—效用复跑。
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
  - 2026-09-23 复评未确认新增独立复现或生产权限系统集成。
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
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v3（09-16）；本轮未确认足以改变等级的新证据。作者仓库仍可访问；未确认主流 serving 集成或跨硬件独立验证。
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
  - 2026-09-23 复评仍未确认 vLLM/SGLang 集成、跨硬件结果或第三方复跑。
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
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v2（10-07）；本轮未确认足以改变等级的新证据。公开资产与第三方复现仍待进一步确认；维持原评级与成熟度。
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 对约 80M～1B active parameters、最高 8.5B total parameters 的 dense 与 MoE 模型进行重复数据对照。
  - 作者发现 MoE 在约 4 次重复后即明显受损，重复 32 次后基本丧失相对 dense 的优势；强 masking 可缓解但不能替代独特数据。
  - arXiv 于 2026-10-07 修订至 v2；截至 2026-10-12 仍未核实公开训练代码或独立复现，维持观察。
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
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。公开资产与第三方复现仍待进一步确认；维持原评级与成熟度。
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 利用模板内、模板间和沙箱间的页冗余，并把压缩安排到 LLM 等待阶段、在恢复路径预取。
  - 作者报告沙箱内存容量最高提升 8.7 倍，Linux 基线为 2.1 倍，并把激进压缩 slowdown 从 3.1 倍降至 1.40 倍。
  - 2026-09-22 定向复核未找到可核验的 AgentZip 实现或独立尾延迟复跑，维持观察。
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

## 2609.13134

- title: Rethinking Heterogeneous System Disaggregation for Subquadratic Attention
- url: https://arxiv.org/abs/2609.13134
- direction: LLM Serving / Heterogeneous Systems / Subquadratic Attention
- first_seen: 2026-09-15
- last_review: 2026-10-17
- next_review: 2026-10-24
- last_review_result: 2026-10-17 定向核验未确认足以改变评级或单独推荐的新增证据。
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - SQD 按二次与次二次注意力的状态和算术强度拆分 decode，而非沿用 attention/FFN 的统一拆分。
  - 作者在 8×B200 异构系统代理上报告 31%～56% token/J 提升，Rubin+LPX 解析模型报告最高 3.6 倍吞吐。
- missing_evidence:
  - 核心数据来自系统代理与解析模型，缺少真实异构集群的生产复现。
  - 尚未确认公开调度器实现、端到端服务代码或独立评测。
  - 本次复评未确认真实异构硬件实测或新代码资产。
  - 2026-09-24 复评仍未确认公开调度器、模拟器或真实异构集群复现。
- known_assets:
  - 论文
  - 系统代理实验
  - 解析模型
- next_review_focus:
  - 代码、模拟器和完整配置是否公开
  - 真实 Rubin/LPX 或多机系统上的吞吐、能效和尾延迟
  - 不同稀疏、线性、滑窗注意力模型的质量与调度敏感性
- discovery_source: arXiv recent

## 2609.12471

- title: AMDKernelVault: Large-Scale Datasets and Agentic Training for AMD GPU Kernel Optimization
- url: https://arxiv.org/abs/2609.12471
- direction: AMD GPU / HIP / Triton / Kernel Agent / Training Data
- first_seen: 2026-09-15
- last_review: 2026-10-17
- next_review: 2026-10-24
- last_review_result: 2026-10-17 定向核验未确认足以改变评级或单独推荐的新增证据。
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 开放 62,153 个执行验证 HIP kernel、39,893 个 Triton kernel 与 2,377 个 ROCm Libraries QA 条目。
  - Qwen3-8B 经 SFT 和执行感知 RL 后，在三项作者评测上获得对照模型中最高正确率，并公开数据与生成/训练代码。
- missing_evidence:
  - 当前主要是作者自评，缺少跨 AMD GPU 代际、编译器版本和外部团队复现。
  - 正确率领先未转化为全面的编译率或速度领先。
  - 本次复评未确认跨硬件或 ROCm 版本的独立结果。
  - 2026-09-24 复评确认数据集与 AMD-AGI/hip_kernel_llm_lab 仍可访问，未见新的跨代 GPU 独立验证。
  - 2026-10-03 复核作者仓库与论文，仍未见跨代 GPU 或独立速度复现。
- known_assets:
  - 论文
  - 数据集
  - kernel 生成流水线
  - 训练代码
- next_review_focus:
  - 数据与代码的可运行性、许可证和去重污染审计
  - 跨 MI300/MI350 等硬件与 ROCm 版本的复现
  - correctness、compilation、speedup 三类指标的独立对照
- discovery_source: arXiv recent / 作者 GitHub / Hugging Face

## 2609.12742

- title: Skill Issue: Lessons from Optimizing Repository SKILLs for Coding Agents
- url: https://arxiv.org/abs/2609.12742
- direction: Coding Agent / Repository Knowledge / SKILL Optimization / Evaluation
- first_seen: 2026-09-15
- last_review: 2026-10-17
- next_review: 2026-10-24
- last_review_result: 2026-10-17 定向核验未确认足以改变评级或单独推荐的新增证据。
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 从合并 PR 回退构造统一基线任务，以同一 Agent 有无 SKILL 文档的成对差值衡量收益。
  - 三个 Kotlin 仓库上 GEPA 文档平均提升 4.9 个百分点，SkillOpt 仅提升 0.1 个百分点；作者明确指出样本量不足以区分前者与运行方差。
- missing_evidence:
  - 仅覆盖三个 Kotlin 仓库，任务量和语言、框架多样性不足。
  - 尚未确认公开任务集、完整运行轨迹和跨 Agent 复现。
  - 本次复评未确认作者新公开的任务集或复跑轨迹。
  - 2026-09-24 复评仍未找到作者代码或完整运行轨迹；现有外部讨论未构成独立复现。
- known_assets:
  - 论文
  - 真实 PR 回退式评测方法
- next_review_focus:
  - 数据、代码和重复运行轨迹是否公开
  - 跨语言、跨 Agent 的 SKILL 收益与运行方差
  - 文档可读性、维护成本与任务指标的相关性
- discovery_source: arXiv recent

## 2609.15989

- title: Corrupt Plans, Clean Traces: Evading Chain-of-Thought Monitoring with Plan Injection
- url: https://arxiv.org/abs/2609.15989
- direction: Agent Safety / Chain-of-Thought Monitoring / Prompt Injection
- first_seen: 2026-09-16
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。公开资产与第三方复现仍待进一步确认；维持原评级与成熟度。
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 在多类 monitorability benchmark 上报告 25%～33% 的监控逃逸率，并扩展到 DeepSeek-R1。
  - Actor 会把注入计划改写为自身推理；向 Monitor 提供更多上下文或预算有时反而降低检测。
- missing_evidence:
  - 缺少生产 Agent、真实工具调用与多轮记忆环境的第三方复现。
  - 尚未确认公开代码、完整攻击集和稳健防御基线。
  - 2026-09-20 复评仍未确认公开实现或第三方生产 Agent 复现。
- known_assets:
  - 论文
- next_review_focus:
  - 代码与攻击数据是否公开
  - 上下文来源标注、引用追踪和 Monitor 隔离的防御效果
  - 跨模型、跨任务独立复现
- discovery_source: arXiv cs.AI recent

## 2609.15982

- title: The Router Within: Eliciting Native Skill Routing from a Frozen LLM
- url: https://arxiv.org/abs/2609.15982
- direction: Agent / Skill Routing / Representation Probing / Context Efficiency
- first_seen: 2026-09-16
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v2（09-28）；本轮未确认足以改变等级的新证据。公开资产与第三方复现仍待进一步确认；维持原评级与成熟度。
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 以两个线性映射读取冻结 LLM 中间层状态，先召回 Skill、再用模型自身判断复排，避免把完整 Skill 元数据放入上下文。
  - 作者报告 Qwen3-32B 相对带 1.2B～16B 外部参数的基线最高提升 13.4 分，中途触发 Skill 时最高提升 21.9 分。
- missing_evidence:
  - 缺少公开实现、SkillTraj 数据审计和独立跨模型复现。
  - Skill 库漂移、安装态缓存成本和线性映射迁移成本尚不清楚。
  - 2026-09-20 复评仍未确认代码与 SkillTraj 数据正式公开。
- known_assets:
  - 论文
  - SkillTraj benchmark 描述
- next_review_focus:
  - 代码与 372 条轨迹是否公开
  - 跨 backbone 与动态 Skill 库的迁移稳定性
  - 与低成本 embedding/retrieval 的等预算对照
- discovery_source: arXiv cs.LG / cs.AI recent

## 2609.15983

- title: Stellar Colosseum: A Many-Agent Harness for Long-Horizon Research in Mathematics and Theoretical Computer Science
- url: https://arxiv.org/abs/2609.15983
- direction: Multi-Agent / Harness / Long-Horizon Research / Theorem Proving
- first_seen: 2026-09-16
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v2（09-15）；本轮未确认足以改变等级的新证据。公开资产与第三方复现仍待进一步确认；维持原评级与成熟度。
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 以并行策略探索、readiness gate、章节级依赖、定向反证和重叠随机采样树聚合组织长程证明。
  - 作者报告 TCS-Bench 71.0%，并以带执行反馈的证明流水线解决 222 道 Codeforces 题中的 218 道。
- missing_evidence:
  - 所称开放问题新结果需要领域专家与正式评审确认。
  - 缺少完整实现、推理成本、消融和不同模型的独立复现。
  - 2026-09-20 复评仍未确认完整实现、公开轨迹或专家验证更新。
- known_assets:
  - 论文
  - Google Antigravity Teamwork 中的 Long Proof 集成说明
- next_review_focus:
  - 代码、轨迹与研究产物是否公开
  - TCS-Bench 污染、判分协议和成本对照
  - 新数学结果的专家验证状态
- discovery_source: arXiv cs.AI recent

## 2609.19134

- title: ScienceIDE: Turning World's Scientific Codebase into Agent Learnable Environments
- url: https://arxiv.org/abs/2609.19134
- direction: AI for Science / Agent 环境 / 科学软件验证
- first_seen: 2026-09-18
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。aitofound/ScienceIDE 仍列15/64环境与30/85难任务，未确认全量交付或独立复跑。
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 将科学仓库、专家案例与验收条件组织为可执行、可验证的 Agent 学习环境。
  - 作者仓库已公开 15/64 个环境、30/85 个高难任务、SFT/RL 代码、执行验证器及 4B/9B/72B PhAI-IDE 模型。
  - 项目规划覆盖 64 个环境、27 个代码库和 2,812 个任务；本次复评确认资产结构已足以审查环境构建和验收逻辑。
- missing_evidence:
  - 公开任务只是子集，作者自报收益尚待独立复跑。
  - 领域覆盖、数值验证充分性与跨科学软件迁移仍不明确。
  - 不同 benchmark 的模型收益不一致，部分 HumanEvalFix 结果下降。
- known_assets:
  - 论文
  - 部分环境与任务
  - 验证器
  - 作者代码
  - SFT/RL 训练代码与模型 checkpoints
- next_review_focus:
  - 公开环境与任务是否扩展
  - 第三方科学代码修复复现
  - 与普通单元测试及 benchmark 污染的对照
- discovery_source: Hugging Face Daily Papers / arXiv / 作者 GitHub

## 2609.19969

- title: DeepSeek-V4.1-Flash: Pushing the Limits of KV Cache Compression
- url: https://arxiv.org/abs/2609.19969
- direction: 基础模型 / 长上下文 / KV cache / Serving
- first_seen: 2026-09-19
- last_review: 2026-10-18
- next_review: 2026-10-25
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 2026-10-18 复评：论文仍为 v1；vLLM 的 GB300 专用 decode PR 是服务实现新证据，不能据此确认 CSA2/FP4 KV 全链路或独立长上下文质量复现。
  - 官方技术报告与开放模型资产说明 CED、CSA2、FP4 KV 和 SWA Bounded Replay 的协同设计。
  - 作者报告全局 KV 常驻 HBM 约 890 bytes/token，长期持久缓存约为 V4-Flash 的八分之一。
  - 2026-10-11 复评：原论文仍为初版；尚未核实独立长上下文质量与成本复现，完整 CSA2/FP4 KV 部署路径仍待确认。此前 vLLM v0.30.0 已列 DeepSeek-V4.1 支持，但不能据此推断其实现了论文全部缓存机制。
- missing_evidence:
  - 成本、精度和吞吐结果主要为模型团队自报，缺少独立同等硬件验证。
  - 552B backbone 和 1M context 的复现资源门槛高。
- known_assets:
  - 论文
  - 官方模型 checkpoint
  - 模型卡与部署说明
- next_review_focus:
  - vLLM/SGLang 等后端对 CSA2/FP4 KV 的真实支持
  - 独立长上下文质量与 HBM/SSD 成本测量
  - CED prefill/decode 效率的公平基线
- discovery_source: Hugging Face Daily Papers / arXiv / DeepSeek 官方模型卡

## 2609.20519

- title: SoL-Pi: Recursively Scaling Auto-Research Loops for Efficient Agent Harness
- url: https://arxiv.org/abs/2609.20519
- direction: Coding Agent / Harness / Context Compression / Evaluation
- first_seen: 2026-09-19
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。SoL-Pi 作者代码仍公开且无release，兼容与收益仍需独立验证。
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 作者在 51 项 EdgeBench 任务报告接近基线完成度、token 传输降约 44.7%～49.0%。
  - 官方仓库提供 Pi 独立扩展、四种可选机制、配置和测试。
  - 2026-09-23 复评确认 19 个测试文件、140 项测试已覆盖 Pi 0.85.1 与 0.84.2，公开兼容性与安全边界文档更完整。
- missing_evidence:
  - 缺少第三方跨模型和任务分布复跑，API 成本约降三分之一尚需验证。
  - 观察压缩与摘要机制的错误隐藏风险需要实际任务审计。
  - 兼容性证据仍来自作者仓库，未见独立长周期任务复现。
- known_assets:
  - 论文
  - 核心扩展代码
  - 配置与测试
- next_review_focus:
  - 独立成功率—成本 Pareto
  - 观察存档与压缩失败回退的正确性
  - 长周期、多线程 Agent 场景的迁移性
- discovery_source: Hugging Face Daily Papers / arXiv / NVIDIA 官方 GitHub

---

## 2609.22068

- title: CodeMidas: Scaling Agentic Coding RL Environments from Code Itself
- url: https://arxiv.org/abs/2609.22068
- direction: Coding Agent / RL / 可验证环境合成
- first_seen: 2026-09-22
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。另发现 Repo2RLEnv 0.9.2 的外部实验性 recipe；100任务数据集明确未公开，不能算原论文训练复现，维持M0。
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 从源代码现有功能合成行为规范、移除目标实现并用原始代码执行构造 verifier；经泄漏和解题 rollout 筛选出 3,185 仓库的 5,545 项任务。
  - 作者用同一 MiMo-V2.5 基座报告 DeepSWE 10.0%→21.7%、Terminal-Bench v2.1 63.7%→72.2%，并给出高质量 3k 优于未清洗 8k 的消融。
- missing_evidence:
  - 尚未核验公开任务集、核心环境合成代码、训练 recipe 与第三方复现。
  - 需进一步审查任务泄漏、verifier 的假阳/假阴及跨基座泛化。
- known_assets:
  - 论文及实验细节
- next_review_focus:
  - 代码、任务集和训练配置是否发布
  - 独立复跑与强合成环境基线对照
- discovery_source: arXiv recent cs.AI

## 2609.21509

- title: The Communication Bottleneck: A Round-Trip Study of Tree-Structured Expression Serialization in Language Models
- url: https://arxiv.org/abs/2609.21509
- direction: Agent 通信 / 结构化表示 / Evaluation
- first_seen: 2026-09-22
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v2（09-21）；本轮未确认足以改变等级的新证据。公开资产与第三方复现仍待进一步确认；维持原评级与成熟度。
- status: active
- quality: B
- maturity: M0
- personal_value: medium
- main_evidence:
  - 用表达式→文字题→表达式和符号等价 oracle 隔离树结构在自然语言通信中的损失，对 16 个模型两两组合测量。
  - 报告收发模型调换可带来最高 60.4 个百分点差异，并测试约 3,600 样本微调与异域迁移。
- missing_evidence:
  - 任务域偏窄，尚需真实多 Agent、代码或工具状态传递验证。
  - 尚未核验公开数据、评测实现及独立复跑。
- known_assets:
  - 论文
- next_review_focus:
  - 实验代码与数据发布
  - 结构化 IR/JSON 与自由文本的同预算比较
- discovery_source: arXiv recent cs.AI

## 2609.24974

- title: Harness-Zero: Harness Distillation via Agent-as-Harness
- url: https://arxiv.org/abs/2609.24974
- direction: Agent Harness / Distillation / Tool Use / SFT
- first_seen: 2026-09-23
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。metaevo-ai/harness-zero 代码可访问，未确认独立跨模型与完整成本复跑。
- status: active
- quality: A
- maturity: M1
- personal_value: high
- main_evidence:
  - 让 harnessing agent 在执行前审阅并改写 student 响应，再在目标 harness 动作空间内构造 SFT 轨迹，把专用 harness 诱导的行为蒸馏进权重。
  - 2026-10-05 深评核对 Qwen3.5-9B 三域分别训练的检查点：简易 harness 宏平均 23.3%→44.3%，超过未训练底座加优化 harness 的 41.7%；USPTO 领域仍为 30%<38%。
  - 官方仓库公开三域任务集、harness bank、rollout/SFT 代码、Docker 环境、测试与三个 LoRA checkpoints；2026-10-12 arXiv 尚无新版。
- missing_evidence:
  - 结果均为作者自报，缺少第三方跨模型复跑；三个 LoRA 检查点按领域分别训练，宏平均不代表一个通用检查点。
  - USPTO 消融显示强教师直接轨迹训练仅 12%、带专用 harness 的教师轨迹训练为 3%、规则指导逐步纠错为 30%；但每步额外审阅调用使该域平均轨迹收集耗时约 2.4 倍。
  - 权重内行为在 harness 更新、分布外任务和错误恢复上的稳定性未知。
- known_assets:
  - 论文
  - 核心代码与测试
  - 三域任务集与 harness bank
  - rollout/SFT recipe
  - LoRA checkpoints
- next_review_focus:
  - 第三方端到端复跑与成本核算
  - 跨基座、跨 harness 的消融与迁移
  - 分布外稳健性及行为更新成本
- discovery_source: arXiv cs.AI recent / Hugging Face Daily Papers / 作者 GitHub

## 2609.26779

- title: CliffCompaction: Cost-Efficient Compaction for Long-Horizon Coding Agents
- url: https://arxiv.org/abs/2609.26779
- direction: Coding Agent / Context Compaction / Cost Efficiency / Reliability
- first_seen: 2026-09-24
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。发现 EmbeddedLLM/pi-cliffcompaction 外部移植，尚未核验其原论文成功率—成本复现；不据移植自动升级成熟度。
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 采用删除与截断而非生成式重写，并始终从原始历史重新压缩，避免“摘要的摘要”累积漂移。
  - 作者报告 Terminal-Bench 成本最高下降约 50%，KernelBench 长轨迹收益在 200/400 步分别达 2.23 倍/3.58 倍。
  - 官方 MIT 仓库提供透明 API 代理、Claude Code/Codex 配置、测试、shadow 模式和失败透传路径。
- missing_evidence:
  - 结果仍为作者自报，仓库刚公开且规模较小，缺少跨模型、跨 harness 的第三方复跑。
  - 长工具输出删除可能丢失关键证据，前缀稳定假设与客户端原生压缩的交互需实测；2026-09-30 复核仓库仍有核心代理、配置及 tests，但未见独立复跑。
- known_assets:
  - 论文
  - 核心代理代码
  - CLI 与系统服务配置
  - tests
- next_review_focus:
  - 独立任务成功率—token 成本复跑
  - tool result 删除的错误模式与恢复路径
  - Codex/Claude Code 版本变化下的前缀稳定性
- discovery_source: arXiv recent cs.AI / 作者 GitHub

## 2609.26777

- title: SWE-Serve: A Benchmark for Agentic Inference Engineering
- url: https://arxiv.org/abs/2609.26777
- direction: Coding Agent / LLM Serving / Systems Benchmark / SGLang
- first_seen: 2026-09-24
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。NVIDIA/swe-serve 官方release为空；未确认独立验证器审计。
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 从 83 个已合并 SGLang PR 构造 53 个生产推理工程任务，覆盖 12 个 CPU 与 41 个单 H100 任务。
  - 作者对 627 个补丁报告：仅跑本地测试时通过率 69.4%，加入 live-server verifier 后降至 45.9%；跨 runtime 任务也明显更难。
  - NVIDIA 官方仓库公开任务、隐藏 verifier、参考解、Harbor runner、closed-book 网络隔离和三次运行配置。
- missing_evidence:
  - benchmark 仅来自 SGLang，且 GPU 复跑需要 H100、较大磁盘和内存资源。
  - 任务与榜单刚公开，2026-09-30 复核官方仓库后仍缺独立复跑、verifier 缺陷审计和跨推理引擎迁移。
- known_assets:
  - 论文
  - 53 项 benchmark
  - verifier 与参考解
  - runner 和复跑配置
- next_review_focus:
  - 独立榜单复跑与任务缺陷修订
  - 扩展到 vLLM、TensorRT-LLM 等 runtime
  - live-server verifier 的假阳性、资源隔离与稳定性
- discovery_source: NVIDIA Technical Blog / arXiv recent / NVIDIA 官方 GitHub

## 2609.26457

- title: Recursive Self-Improvement of AI Research Agents
- url: https://arxiv.org/abs/2609.26457
- direction: AI Research Agent / Recursive Self-Improvement / Evaluation
- first_seen: 2026-09-24
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 核对 arXiv 当前仍为v1；本轮未确认足以改变等级的新证据。公开资产与第三方复现仍待进一步确认；维持原评级与成熟度。
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - AIDE² 在八天连续运行中完成七轮对自身研究 Agent 的改进，并在冻结的留出问题上报告总体泛化增益。
  - 论文把奖励投机作为核心风险审计，报告人工检查后相关比例由 55% 降至 32%。
- missing_evidence:
  - 尚未确认官方代码、完整轨迹、冻结评测集或可重复运行 recipe。
  - 单次长期实验与作者自评不足以区分真实能力提升、搜索偏差和评测适配。
- known_assets:
  - 论文
  - 作者项目说明
- next_review_focus:
  - 官方代码、完整轨迹与评测集是否发布
  - 独立长周期复现及同预算基线
  - 奖励投机、回归和停止条件的外部审计
- discovery_source: arXiv recent cs.AI / missed-item backfill


## 2609.39903

- title: OSWorld-Science: A Benchmark of Computer Use Agents for Learning and Using Scientific Software
- url: https://arxiv.org/abs/2609.39903
- direction: AI for Science / GUI Agent / 可执行评测
- first_seen: 2026-10-02
- last_review: 2026-10-20
- next_review: 2026-10-27
- status: active
- quality: B
- maturity: M1
- personal_value: medium
- main_evidence:
  - 2026-10-13 复评：论文仍为 9 月 30 日 v1；已核对 DiscoAILab/OSWorld-Science 官方仓库公开，但仍未确认独立完整复跑或评分器审计。
  - 146 个专家设计任务覆盖 7 个科学领域、14 种软件配置，使用应用状态与产物执行评测，比较 12 个 VLM。
  - 官方 GitHub 提供 harness、评测器、配置、测试和运行入口；项目页链接官方数据与 VM 镜像。
  - 2026-10-06 复评：arXiv 仍为 9 月 30 日 v1；项目代码入口本次未能独立打开，未确认新的完整复跑或评分器审计，继续观察。
- missing_evidence:
  - 论文刚发布，尚缺第三方完整复跑；部分 EEGLAB/Windows Ansys 镜像未公开，完整镜像下载约 200 GB。
  - 需核对逐任务评分器、任务泄漏与模型/提示配置对结论的影响。
- known_assets:
  - paper and project page
  - core benchmark code and tests
  - task data and available VM images
  - example trajectories
- next_review_focus:
  - 可运行任务范围与评分器审计
  - 独立复跑及成本/质量比较
  - 是否出现模型能力与 harness 影响的可分离对照
- discovery_source: arXiv recent cs.AI / Hugging Face Daily Papers / 作者项目页

---
- last_review_result: 2026-10-20 arXiv 仍为 v1（09-30）；DiscoAILab/OSWorld-Science 代码可访问，未确认独立完整复跑，维持 B/M1。

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
- last_review: 2026-10-18
- next_review: 2026-10-25
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-10-18 greedy speculative decoding runner 契约已公开；暂无稳定 release 或已核验的新性能基准
- main_evidence:
  - 2026-10-18 复评：README 与代码已公开 greedy speculative decoding 的 ngram/custom_class runner 契约；仅支持 argmax_ids/host greedy acceptance，采样接受、lane-DP 等未实现，GitHub release 仍为空。
  - 以 out-of-tree plugin 接入 Tenstorrent，覆盖平台发现、模型注册、worker、scheduler 与执行桥。
  - 公开代码、文档、示例与测试，明确实现 phase-only scheduling、片上采样回退、异步 readback 和单进程 lane-DP。
- missing_evidence:
  - 官方文章未提供统一、可审计的端到端性能表，且硬件验证门槛较高。
  - greedy speculative decoding 已有 runner 契约，但 sampled acceptance、LoRA 与多机 serving 尚未实现；混合模型数据并行仍待硬件验证。
- known_assets:
  - core code
  - docs
  - examples
  - tests
- next_review_focus:
  - 首个稳定 release 与 vLLM 版本兼容性
  - 可复现吞吐、延迟和成本 benchmark
  - sampled speculative decoding、LoRA、多机与 hybrid DP 支持
- discovery_source: vLLM 官方博客 / GitHub

## AI-Hypercomputer/accelerator-agents

- repo: AI-Hypercomputer/accelerator-agents
- url: https://github.com/AI-Hypercomputer/accelerator-agents
- direction: AI 系统 / 编译器 / 自动 kernel 优化
- first_seen: 2026-09-08
- last_review: 2026-10-18
- next_review: 2026-10-25
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-10-11 复评未发现稳定 release 或独立复现；保留 2026-09-24 的迭代记录
- main_evidence:
  - 2026-10-18 复评：仓库仍无 GitHub release；未见可核验的独立跨硬件复跑、成本与失败率新证据。
  - 仓库包含 MaxKernel、JAXBench、MaxCode、文档、CI 与测试，不是仅有论文说明；本次复评可见 311 次提交。
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
- url: https://github.com/NVIDIA/cuda-rust/tree/main/cuda-oxide
- direction: GPU 编译器 / Rust / CUDA SIMT kernel
- first_seen: 2026-09-09
- last_review: 2026-10-18
- next_review: 2026-10-25
- status: active
- quality: B
- personal_value: high
- last_release: v0.2.1（2026-06-10）
- last_commit_or_major_delta: 2026-10-11 官方代码统一到 NVIDIA/cuda-rust；cuda-oxide 组件仍未发现高于 v0.2.1 的稳定 release
- main_evidence:
  - 2026-10-18 复评：统一仓库最新 cuda-oxide 仍为 v0.2.1，未见新稳定版或跨 workload 独立性能证据。
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
- url: https://github.com/NVIDIA/cuda-rust/tree/main/cutile-rs
- direction: GPU 编程 / Rust / tile-level DSL
- first_seen: 2026-09-09
- last_review: 2026-10-18
- next_review: 2026-10-25
- status: active
- quality: A
- personal_value: high
- last_release: v0.4.0（统一仓库 GitHub releases 页面已核验）
- last_commit_or_major_delta: 2026-10-08 NVlabs/cutile-rs 原仓库归档，代码并入 NVIDIA/cuda-rust；最新稳定版本仍为 v0.4.0，未见新的性能或兼容性证据
- main_evidence:
  - 2026-10-18 复评：统一仓库最新 cuTile Rust 仍为 0.4.0，尚无新的独立端到端基准。
  - 仓库提供稳定 Rust 上的 tile DSL、CUDA Tile IR JIT、host-side ownership API、示例与文档。
  - NVIDIA 官方文章确认 Hugging Face Grout 与 mistral.rs 已采用。
  - v0.4.0 release 给出源码行映射、异步 UAF 修复、跨 stream 冲突检测、DGX Spark 测试及可复核的 API 变更。
- missing_evidence:
  - 仍处早期阶段，0.4.0 有破坏性 API 变化；基础功能需 CUDA 13.2+，PDL 需 13.4 与 sm90+。
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


## radixark/miles

- repo: radixark/miles
- url: https://github.com/radixark/miles
- direction: LLM 后训练 / 分布式系统 / RL infrastructure
- first_seen: 2026-09-10
- last_review: 2026-10-20
- next_review: 2026-10-27
- status: active
- quality: A
- personal_value: high
- last_release: v0.1.2（2026-10-09）
- last_commit_or_major_delta: 2026-10-09 v0.1.2：统一训练后端、实验性 Kubernetes、多策略训练、score centering、DeepSeek-V4.1 Flash 主线支持
- main_evidence:
  - 2026-10-09 v0.1.2：torchtitan 与 FSDP 共享数据、损失、检查点及权重同步；实验性 Kubernetes 原生调度、热恢复测试、多策略作业和 score centering。多节点长期稳定性仍待独立复跑。
  - 包含训练入口、同步与异步执行、SGLang rollout、Megatron-LM/FSDP trainer、三种权重同步、文档和测试。
  - v0.1.1 对 Qwen3.8-Flash-Next 与 GLM-5.3-Flash 给出权重同步相等检查和短程 rollout/trainer 对数概率差；多 LoRA 槽的权重、FP32 master 和 Adam moments 恢复检查为零容差。
  - 作者展示 64 台 GB300 上 GLM-5.2 744B-A40B 的全异步 terminal-coding RL 案例。
  - 本次复评可见 2,175 次提交，近期仍在补充低精度训练 kernel、真实沙箱 CI 和硬件测试矩阵。
  - 2026-10-06 复评：官方 Releases 最新仍为 v0.1.1；已有工程与短程一致性证据仍成立，但未见新的正式版本或第三方多节点复跑，暂不重复推荐。
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
- last_review_result: 2026-10-20 最新稳定版仍为 v0.1.2（10-09）；未确认足以改变等级的外部端到端复现，维持 A。

## openai/codex

- repo: openai/codex
- url: https://github.com/openai/codex
- direction: Coding Agent / Harness / Sandbox / Developer Infrastructure
- first_seen: 2026-09-11
- last_review: 2026-10-20
- next_review: 2026-10-27
- status: active
- quality: A
- personal_value: high
- last_release: 0.163.0（2026-10-16 北京时间；UTC 10-15 21:30）；0.164.0-alpha 系列不作稳定版
- last_commit_or_major_delta: 0.163.0 修复权限恢复、代理 DNS/Host 检查与取消代码单元等路径；不据此推断桌面应用或托管 harness 的 revision
- main_evidence:
  - 成熟 Rust 主体仓库，包含 codex-rs、CLI、SDK、文档、工具、测试与长期提交历史。
  - 官方将其定位为 Agents API 的开源 harness 基础，可对照托管服务理解模型、工具、上下文和 sandbox 的边界。
  - 0.161.0 稳定版 release 对权限与恢复链路列出具体修正；当前聊天使用模型不随 release 自动改变。
  - 2026-10-15 复核稳定版 0.162.1 的两项具体 bug fix；不足以构成新的重大技术推荐。
- missing_evidence:
  - 托管 API 与公开仓库不完全等价，服务端调度、隔离和运维实现并未全部开源。
  - 仍需核对具体 Agents API harness 版本与仓库 revision 的对应关系。
  - 2026-09-16 可见高频 alpha 构建，但 release 页面没有提供足以验证上述映射的稳定说明。
  - 2026-09-30 检查 0.159.2 release 后，仍未见公开的 Agents API 托管 harness 与仓库 revision 对应表。
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
- last_review_result: 2026-10-20 核验稳定版 release，按实际发布时间补报；仍缺托管服务与公开 revision 的明确对应。

## JustVugg/colibri

- repo: JustVugg/colibri
- url: https://github.com/JustVugg/colibri
- direction: LLM Inference / MoE / Memory Hierarchy / Storage Streaming
- first_seen: 2026-09-15
- last_review: 2026-10-17
- next_review: 2026-10-24
- last_review_result: 2026-10-17 定向核验未确认足以改变评级或单独推荐的新增证据。
- status: active
- quality: B
- personal_value: high
- last_release: v2.0.0（2026-10-06）
- last_commit_or_major_delta: v2.0.0：所有 MoE 引擎增加 Vulkan 专家层和部分 dense 层设备链；最多 16 个会话槽。发布说明只在双开 Lavapipe 下验证双 GPU dense 链，真实双卡吞吐未测。
- main_evidence:
  - v1.12.1 官方发布说明给出 Qwen 757/2803→2803/2803、OLMoE 1560/1708→1708/1708 的 tokenizer 对齐结果；Tesla M10 放置回退和特定 Qwen3.8 解码测试仍属作者自测。
  - 纯 C 推理引擎把 VRAM、RAM 和 NVMe 作为统一层级，按 MoE 路由结果调度专家权重，并覆盖九类模型架构。
  - Apache-2.0，约 31.4k stars；公开 benchmark protocol、质量检查、端到端数据和负面结果记录要求。
- missing_evidence:
  - v1.12.1 的速度、RSS 与质量数据尚缺独立同硬件复跑，需验证 perplexity 变化。
  - 多数性能数据来自项目方与社区提交，缺少统一第三方硬件矩阵复现。
  - 超大模型仍需数百 GB 至 TB 级存储，低内存可运行不等于达到实用交互速度。
- known_assets:
  - core C engines
  - CLI and API gateway
  - CUDA / Metal / Vulkan backends
  - benchmark protocol and logs
  - model conversion tools
- next_review_focus:
  - 独立硬件复现与端到端质量对照
  - 路由热点缓存、预取和双 SSD 的受控 A/B
  - release 稳定性、issue 关闭质量和多模型语义一致性
- discovery_source: GitHub Explore / GitHub repository

## NVIDIA/TileGym

- repo: NVIDIA/TileGym
- url: https://github.com/NVIDIA/TileGym
- direction: GPU kernel / CUDA Tile IR / Agent 编译器工作流
- first_seen: 2026-09-17
- last_review: 2026-10-21
- next_review: 2026-10-28
- status: active
- quality: B
- personal_value: high
- last_release: v1.5.1（2026-09-22）；GitHub release 已核验，修复 wheel 中 .cuh/.rs/JSON 资源打包
- last_commit_or_major_delta: 10-19 cuTile Mamba-2 前向技术文提供 TileGym 实现与测试入口、三 kernel 设计及 B300 配置；release 仍为 v1.5.1，不能将新示例等同已打包交付
- main_evidence:
  - 2026-10-18 复评：最新 GitHub release 仍为 v1.5.1；未见第三方端到端复现。
  - 官方仓库提供转换 Skill、阶段校验器、CUDA Tile IR 对比、算子源码、测试与性能协议。
  - NVIDIA 自测在 B200 的 347 组配对配置上取得 0.995 的设备时间几何平均性能比，所有 24 个算子均超过 0.95 门槛。
- missing_evidence:
  - 暂无独立重复运行结果；Rust 路径依赖 CUDA 13.1+、Rust 1.89+、tileiras 和性能测试用 Blackwell。
  - CUPTI 设备时间不等于真实端到端延迟，部分算子仍使用不安全 API。
- known_assets:
  - core code
  - agent skill and validators
  - 24 converted operators
  - tests and benchmarks
- next_review_focus:
  - 第三方复现和实际应用中的端到端收益
  - Rust 安全 API 覆盖率与非 Blackwell 平台兼容性
  - 自动转换失败案例与审计成本
- discovery_source: NVIDIA Developer Blog / 官方 GitHub
- last_review_result: 2026-10-21 新 kernel/benchmark 触发核验；前向 1.14～1.82 倍为作者指定 B300 对照 Triton 3.7.1 的测量，反向/端到端和独立复跑未确认。技术内容单独报 A，项目评级仍 B。

## alibaba/open-code-review

- repo: alibaba/open-code-review
- url: https://github.com/alibaba/open-code-review
- direction: Coding Agent / Code Review / CI / Deterministic Harness
- first_seen: 2026-09-15
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 v1.13.2仍为最新；语言覆盖与路径有效性修正已核验，未确认独立AACR-Bench复跑，不重复推荐。
- status: active
- quality: B
- personal_value: high
- last_release: v1.13.2（2026-10-20）；新增 Shader/Nushell/PowerShell 覆盖与路径有效性检查
- last_commit_or_major_delta: v1.13.2 常规语言规则和扫描路径修复，未达到单独推荐门槛；本轮只做 release 轻检，保留原定复评日
- main_evidence:
  - 将文件覆盖、分组、规则匹配、评论定位和反思校验放入确定性流水线，Agent 负责跨文件语义判断。
  - Apache-2.0，约 24.5k stars；提供 CLI、全文件扫描、主流 CI 集成与 200 个真实 PR 的 AACR-Bench。
- missing_evidence:
  - 约九分之一 token 和更高 Precision/F1 等结果主要来自项目方，缺少独立 benchmark 复跑。
  - 官方明确以 Recall 换 Precision，真实团队能否接受漏报率需要按代码域验证。
- known_assets:
  - Go CLI
  - review rules
  - CI integrations
  - AACR-Bench dataset
  - docs and security policy
- next_review_focus:
  - AACR-Bench 的独立复现、污染与标注一致性
  - 定位和反思模块的消融效果
  - 私有仓库权限、遥测、模型端点数据边界与生产漏报率
- discovery_source: GitHub Explore / GitHub repository

## facebookresearch/ads_model_kernel_library

- repo: facebookresearch/ads_model_kernel_library
- url: https://github.com/facebookresearch/ads_model_kernel_library
- direction: GPU Kernel / Blackwell / MXFP8 FlashAttention / 训练系统
- first_seen: 2026-09-18
- last_review: 2026-10-17
- next_review: 2026-10-24
- last_review_result: 2026-10-17 定向核验未确认足以改变评级或单独推荐的新增证据。
- status: active
- quality: A
- personal_value: high
- last_release: lp_fa4 标为 release candidate，未确认稳定版本
- last_commit_or_major_delta: 2026-10-01 新增公开 TLX Jagged Flash Attention 技术拆解与 tlx_jfa 源码；B200 BF16 jagged 算子较 FA4 前向约快 13%、反向约快 50%
- main_evidence:
  - PyTorch 官方技术文章给出 TMEM scale 布局、反向量化与训练模块集成细节。
  - 作者提供核心代码、smoke tests 和 benchmark；16K KV tokens 模块报告约 1.30 倍收益。
  - 仓库已扩展为四组面向 Hopper/Blackwell 的广告与推荐训练 kernel，并给出各项目依赖和入口。
  - 新增 JFA 公开实现解释变长 tile 分配、dQ 双缓冲归约、TMEM 提前释放和寄存器 spill 等瓶颈，提供 jagged 与 dense 两类算子对照。
- missing_evidence:
  - 缺少独立复跑、跨硬件结果和端到端训练收益；密集前向只达到 FA4 约 87% 的速度。
  - 复现依赖 Blackwell、CUDA 13、PyTorch 2.13 等特定栈。
- known_assets:
  - core code
  - smoke tests
  - benchmark
  - 技术文章
- next_review_focus:
  - 稳定 release 与依赖兼容性
  - 独立精度和性能复现
  - 训练任务中端到端收益及质量影响
- discovery_source: PyTorch 官方博客 / Meta 作者仓库

## NVIDIA/TensorRT-Edge-LLM

- repo: NVIDIA/TensorRT-Edge-LLM
- url: https://github.com/NVIDIA/TensorRT-Edge-LLM
- direction: Edge LLM Serving / Jetson / Agentic Benchmark
- first_seen: 2026-09-18
- last_review: 2026-10-17
- next_review: 2026-10-24
- last_review_result: 2026-10-17 定向核验未确认足以改变评级或单独推荐的新增证据。
- status: active
- quality: B
- personal_value: high
- last_release: v0.11.0（2026-09-29），官方 release 已核验
- last_commit_or_major_delta: v0.11.0：匹配原生载荷的 wheel、实验性单 rank in-flight batching、C++ Jinja 模板与 XGrammar 约束解码
- main_evidence:
  - v0.11.0 发布了 wheel、C++ Jinja 渲染、XGrammar guided decoding 与实验性单 rank in-flight batching，修复 KV cache 和特殊 token 等正确性问题。
  - 官方 C++ 推理代码、配置、测试、量化 checkpoint 和 MLCommons harness 可供审计。
  - 20 段对话 1007 轮性能负载在单台 Thor 用时 24 分 36 秒；文章细分 KV/循环状态缓存和树形 MTP 收益。
  - v0.10.1 官方说明称实验服务器磁盘占用下降 60%～99%、冷启动时间下降 50%，并新增双 DGX Spark TP=2 与多种推测解码路径。
- missing_evidence:
  - v0.11.0 的 batching 缺少独立并发延迟/吞吐数据，且当前明确限于实验性单 rank 服务。
  - 6.4 倍对比是量化格式与 runtime 不同的完整系统提交，不能归因于单个优化。
  - 硬件与模型复现门槛较高，暂缺独立复跑。
- known_assets:
  - core C++ runtime
  - reproducibility branch
  - calibrated checkpoint
  - benchmark harness
  - tests and docs
- next_review_focus:
  - 第三方复跑与公平分项消融
  - 其他 Jetson / 模型的延迟吞吐质量权衡
  - 长轨迹中的缓存失效和内存压力
- discovery_source: NVIDIA Developer Blog / 官方 GitHub / MLCommons

## modular/modular

- repo: modular/modular
- url: https://github.com/modular/modular
- direction: Mojo 编译器 / MLIR / MAX Serving / GPU Kernel
- first_seen: 2026-09-19
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 最新正式版仍MAX26.6/Mojo1.1.0；本轮未完成外部compiler PR质量审查，未确认独立性能新增。
- status: active
- quality: A
- personal_value: high
- last_release: Modular 26.6 / Mojo 1.1（2026-09-17）
- last_commit_or_major_delta: Mojo 编译器公开接受贡献，MAX 新增音频与推测解码支持
- main_evidence:
  - 仓库包含 Mojo 编译器、标准库、MAX kernels、serving、模型管线和示例。
  - 官方 26.6 公告提供贡献开放与新增功能；部分 B200/MI355 kernel 相对前版有作者测量。
- missing_evidence:
  - 仓库首页贡献范围描述可能滞后，实际可提交路径需以新指南与 PR 验证。
  - 算子倍数不能外推为端到端吞吐，MAX 使用许可与开源代码许可不同。
- known_assets:
  - core compiler code
  - standard library
  - serving and model pipelines
  - kernels and examples
  - contribution guide
- next_review_focus:
  - 首批外部 compiler PR 的审查与合并质量
  - MAX 新模型、推测解码的可复现端到端效果
  - 开源与发行许可边界
- discovery_source: Modular 官方博客 / 官方 GitHub

## NVlabs/SoL-Pi

- repo: NVlabs/SoL-Pi
- url: https://github.com/NVlabs/SoL-Pi
- direction: Coding Agent / Harness / Token Efficiency
- first_seen: 2026-09-19
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 官方代码可访问，release仍为空；未确认独立成功率—成本复跑。
- status: active
- quality: B
- personal_value: high
- last_release: 未确认稳定 release
- last_commit_or_major_delta: 2026-09-23 增补 Pi 0.85.1/0.84.2 兼容文档，19 个测试文件共 140 项测试
- main_evidence:
  - 有 TypeScript 核心实现、安装说明、配置和测试，不需 patch Pi 主体。
  - 四种机制处理 action fusion、观察存档、保留证据的诊断压缩及在线上下文压缩，默认关闭。
  - 兼容性文档明确 Pi 版本、公有 API、失败回退与敏感日志边界。
- missing_evidence:
  - 成本与完成度证据来自作者评测，缺少独立复跑。
  - 摘要错误、任务类型差异和长周期稳健性待核验。
  - 当前兼容性和测试证据仍由作者维护，尚缺独立长周期验证。
- known_assets:
  - core extension
  - install docs
  - config
  - tests
- next_review_focus:
  - 第三方逐项 ablation 与成本复跑
  - 原文观察可恢复性和压缩回退
  - 非 Pi harness 的机制迁移性
- discovery_source: Hugging Face Daily Papers / arXiv / NVIDIA 官方 GitHub

## ai-dynamo/aiperf

- repo: ai-dynamo/aiperf
- url: https://github.com/ai-dynamo/aiperf
- direction: LLM Serving / Performance Benchmark / Production Trace Replay
- first_seen: 2026-09-20
- last_review: 2026-10-20
- next_review: 2026-10-27
- status: active
- quality: A
- personal_value: high
- last_release: v0.13.0（2026-09-24）
- last_commit_or_major_delta: 2026-09-24 v0.13.0：Kubernetes beta、推测解码接受率、首 chunk usage 修正、cache-bust 与服务端控制钩子
- main_evidence:
  - 2026-10-13 复评：官方 Releases 最新仍为 9 月 24 日 v0.13.0；尚未看到独立跨负载器对照，维持观察。
  - 多进程负载 worker、独立结果处理服务与 ZMQ 协调，直接处理高并发时客户端先成为瓶颈的问题。
  - 提供核心实现、测试、插件系统、Kubernetes operator、生产 trace 回放、SLA/goodput、服务端遥测与多次运行置信区间。
  - 0.13.0 版本说明对应具体 PR；按 chunk 统计 usage 修正首流式 chunk 合并导致的 TPS/user 偏高，并加入每请求推测解码接受率。
  - 支持 vLLM、SGLang、TensorRT-LLM 等服务端路径和多种生成式 AI 端点，采用 Apache-2.0 许可。
  - 2026-10-06 复评：官方 Releases 最新仍为 v0.13.0；未确认新的正式版本或跨负载器独立对照，暂不重复推荐。
- missing_evidence:
  - 缺少跨厂商独立验证及其自身 CPU、网络和协调开销的公开上界。
  - 真实结果仍高度依赖 tokenizer、输出长度、warm-up、连接限制和版本固定方式。
- known_assets:
  - core code
  - tests
  - plugin system
  - Kubernetes operator
  - docs and tutorials
- next_review_focus:
  - 与 GenAI-Perf、vLLM benchmark_serving 和其他负载器的独立对照
  - 高并发客户端资源占用与可饱和服务端规模
  - 跨引擎 trace replay、SLA/goodput 的可重复性
- discovery_source: NVIDIA Technical Blog / 官方 GitHub / 官方文档

---
- last_review_result: 2026-10-20 最新稳定版仍为 v0.13.0（09-24）；未确认新版本或足以改变等级的独立负载验证，维持 A。

## huggingface/tokbench

- repo: huggingface/tokbench
- url: https://github.com/huggingface/tokbench
- direction: LLM Systems / Tokenization / Benchmark
- first_seen: 2026-09-22
- last_review: 2026-10-22
- next_review: 2026-10-25
- last_review_result: 2026-10-22 核心实现与公共API测量规则可访问，release端点失败；不能断言无更新，短期复核。
- status: active
- quality: B
- personal_value: high
- last_release: 未见正式 release
- last_commit_or_major_delta: 2026-09-21 随 Tokenizers v1 候选版技术说明公开测量与复跑路径
- main_evidence:
  - Rust `core/`、`driver/`、多引擎适配、`hf-jobs/` 和仪表板形成可运行测量实体。
  - 统一 encode/decode 计时、输出 ID 哈希校验、加载时间分离，并针对语料重复率做控制。
- missing_evidence:
  - 官方实现者自测，缺跨硬件、Python API 与第三方复跑。
  - 新仓库维护和不同 tokenizer 支持覆盖需继续观察。
- known_assets:
  - core code
  - adapters
  - benchmark driver
  - cloud run recipes
- next_review_focus:
  - 独立测量、语料与版本可重复性
  - v1 正式版与 Python 调用路径结果
- discovery_source: Hugging Face 官方 Blog / 官方 GitHub

## NVIDIA/SWE-Serve

- repo: NVIDIA/SWE-Serve
- url: https://github.com/NVIDIA/SWE-Serve
- direction: Coding Agent / LLM Serving / Systems Benchmark / SGLang
- first_seen: 2026-09-24
- last_review: 2026-10-22
- next_review: 2026-10-29
- last_review_result: 2026-10-22 官方代码与arXiv已核，release页恢复可读且为空；未确认独立复跑或验证器审计。
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release；仓库当前仅 1 次初始提交
- last_commit_or_major_delta: 2026-09-23 NVIDIA 公开 53 项生产推理工程任务、live-server verifier、closed-book runner 与榜单配置
- main_evidence:
  - 53 项任务来自 83 个已合并 SGLang PR，覆盖 12 个 CPU 与 41 个单 H100 任务，并包含持久状态、并发请求和端到端服务检查。
  - 官方仓库提供 Harbor 格式任务、隐藏 verifier、参考解、oracle/nop 校验、网络隔离审计和三次运行配置。
- missing_evidence:
  - 仓库刚公开、提交历史很短，尚缺独立复跑和 verifier 缺陷审计。
  - 完整复跑需要 H100、至少 128 GiB 主存及约 700 GB 磁盘，且任务仅来自 SGLang。
- known_assets:
  - benchmark tasks
  - verifiers and reference solutions
  - Harbor runner
  - closed-book proxy and audit logs
  - leaderboard configs
- next_review_focus:
  - 独立榜单复跑、issue 和任务修订
  - 扩展到其他推理 runtime
  - live-server verifier 的稳定性与资源隔离
- discovery_source: NVIDIA Technical Blog / arXiv / NVIDIA 官方 GitHub

---

## NVIDIA/OpenShell

- repo: NVIDIA/OpenShell
- url: https://github.com/NVIDIA/OpenShell
- direction: Agent Runtime / Sandbox / Security / Policy Verification
- first_seen: 2026-09-29
- last_review: 2026-10-22
- next_review: 2026-10-29
- status: active
- quality: B
- personal_value: high
- last_release: v0.1.5（2026-10-21 北京时间；UTC10-20 17:28）
- last_commit_or_major_delta: v0.1.5：主机名策略绑定supervisor DNS、pod元数据allowlist、broker失败拒绝、MicroVM关闭刷盘及opt-in配置推送；新技术增量A，项目评级维持B
- main_evidence:
  - 2026-10-18 复评：最新稳定 GitHub release 已到 v0.1.4（2026-10-14 北京时间），增加凭据检索与运行时修复；尚缺独立安全审计。
  - 官方仓库包含 Rust crates、Python/多语言 SDK、deploy、e2e、examples 与架构文档，不是 README 占位。
  - 官方可运行示例验证无网络、GitHub 只读和拒绝 POST；v0.1.3 的合并 PR 给出 MCP 版本选择、批量成员检查、转发前再次验证及测试边界。
- missing_evidence:
  - 缺独立安全审计与多协议覆盖矩阵；跨 Agent 组合权限分析仍在开发。
  - BlueField-4/Sentry 属额外参考架构，不应计入纯软件部署的已验证能力。
- known_assets:
  - core code
  - CLI and SDK
  - examples
  - e2e tests
  - docs
- next_review_focus:
  - 第三方对抗测试、协议覆盖与容器网络前提
  - policy prover 实际支持的安全性质和跨 Agent 组合权限
  - 0.1.x 版本稳定性与升级路径
- discovery_source: NVIDIA 官方技术博客 / 官方 GitHub
- last_review_result: 2026-10-22 正式版触发提前复评，已报告具体网络/元数据/恢复语义与兼容性；仍缺独立安全审计。

## NVIDIA/NeMo-Relay

- repo: NVIDIA/NeMo-Relay
- url: https://github.com/NVIDIA/NeMo-Relay
- direction: Agent / 执行运行时 / 可观测性 / 策略中间件
- first_seen: 2026-10-01
- last_review: 2026-10-21
- next_review: 2026-10-28
- last_review_result: 2026-10-21 新安全边界与观测修复触发提前复评；已简报 B 级增量，项目原有 A 级不因修复日志升级，仍缺独立审计。
- status: active
- quality: A
- personal_value: high
- last_release: 0.10.4（2026-10-21 北京时间；UTC10-20 17:53）
- last_commit_or_major_delta: 0.10.4修复hook验证另一账户运行的daemon并更新Hono；本次仅轻检，不构成独立推荐或成熟度升级
- main_evidence:
  - 共用 run/turn/tool/LLM/subagent scope、middleware 与事件流，导出 ATOF、ATIF、OpenTelemetry。
  - README 给出 Codex/Claude Code 包装、真实产物验证与缺失 LLM span/ATIF 的诊断条件。
  - v0.10.0-beta.1 release 与源码/文档提供可复查的实现实体。
- missing_evidence:
  - 跨 harness 事件语义一致性、采集完整率、额外时延和策略绕过率缺少独立评测。
  - Codex Desktop 生命周期限制、Go/C FFI 实验状态及宿主依赖需进一步验证；0.10.0 仍为 beta，需验证 trace 兼容迁移。
- known_assets:
  - core code
  - CLI
  - docs
  - examples
  - tests
- next_review_focus:
  - 独立场景对 ATOF/ATIF/OTel 的字段和缺失行为对照
  - Codex Desktop 与 CLI hook 的生命周期完整性
  - middleware 失败关闭行为及性能成本
- discovery_source: NVIDIA Technical Blog / 官方 GitHub

## allenai/Olmo-core

- repo: allenai/Olmo-core
- url: https://github.com/allenai/Olmo-core
- direction: MoE 训练 / 分布式系统 / GPU 并行
- first_seen: 2026-10-02
- last_review: 2026-10-17
- next_review: 2026-10-24
- last_review_result: 2026-10-17 定向核验未确认足以改变评级或单独推荐的新增证据。
- status: active
- quality: A
- personal_value: high
- last_release: v3.0.0（2026-10-01），GitHub 官方 release tag 已核验
- last_commit_or_major_delta: v3.0.0 含元数据文档边界路径，修复部分 SFT 缓存中上游截断丢 EOS 导致的训练 token 漏计；另有专家反向融合与 HF 导出校验
- main_evidence:
  - Ai2 原始技术文章给出旧 FSDP 到 DDP 专家常驻的执行链、8 B300 47B MoE 的 19.4k→52k tokens/s/GPU 同口径吞吐以及 MXFP8/BF16 对照。
  - 官方仓库公开 src、测试、文档及训练入口；文章还公开路由指标失真、学习率调整和通信计算重叠失败的负面结果。
  - v3.0.0 release 记录 SFT 文档边界选项；作者一份缓存测得旧路径 97.98%、新路径 100% 的 token 进入训练实例。
- missing_evidence:
  - 512 B300 的 1.2T 与 2.38T 数据为系统基准或短容量测试，不代表收敛训练；缺独立集群复跑与模型质量结果。
- known_assets:
  - core training code
  - tests and docs
  - technical article
  - training entry points
- next_review_focus:
  - 对应代码版本、正式 release 与可复现 benchmark recipe
  - 较小 GPU 规模复跑和端到端 loss/稳定性
  - 真实负载下路由平衡、通信与显存开销
  - 文档边界元数据与 EOS 的一致性、旧 API 移除后的升级兼容
- discovery_source: Ai2 官方技术文章 / 官方 GitHub

## ggml-org/llama.cpp

- repo: ggml-org/llama.cpp
- url: https://github.com/ggml-org/llama.cpp
- direction: 推理运行时 / 决策模型 / Agent 路由
- first_seen: 2026-10-03
- last_review: 2026-10-17
- next_review: 2026-10-24
- last_review_result: 2026-10-17 定向核验未确认足以改变评级或单独推荐的新增证据。
- status: active
- quality: B
- personal_value: high
- last_release: 未将本次功能核对到稳定 release
- last_commit_or_major_delta: 2026-10-02 PR #29818 合并，新增 Decision Models 与 /v1/systemone 服务接口
- main_evidence:
  - 合并 PR 含五种决策模型的转换、决策头、GGUF 元数据、服务端上下文及测试。
  - 作者给出概率与参考实现对照，最差差异可到 2.2e-2；单 RTX PRO 6000 示例单问题中位延迟 3～43 毫秒。
- missing_evidence:
  - 缺真实路由或审核任务的质量、校准、高并发吞吐与跨硬件复跑。
  - 各决策模型输出概率不能不经校准直接共用阈值。
- known_assets:
  - merged code
  - tests
  - model conversion
  - server API
- next_review_focus:
  - 稳定 release 与模型兼容矩阵
  - 概率校准、任务准确率与并发延迟
  - 多模型服务的内存、冷启动与隔离成本
- discovery_source: ggml-org 官方博客 / GitHub 合并 PR

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

## gemini-4-argon-model-card

- type: project
- title: Gemini 4 Argon model card and safety case
- url: https://storage.googleapis.com/deepmind-media/Model-Cards/Gemini-4-Argon-Model-Card.pdf
- direction: 前沿模型 / 多模态 MoE / Agent 安全评估
- first_seen: 2026-10-15
- last_review: 2026-10-22
- next_review: 2026-10-29
- status: watchlist
- quality: A
- maturity: M1
- personal_value: high
- watch_reason: 官方模型卡已能核验架构、局限、内部安全比较及前沿风险阈值措辞；更细训练规模、外部任务复跑和部署安全验证仍缺。
- trigger_events:
  - 独立长任务与代码修复评测
  - 模型卡或安全报告实质更新
  - 成本、延迟和工具行为的真实工作负载复跑
- last_review_result: 2026-10-22 14页官方模型卡仍可访问；未识别可确认的实质新修订或独立长任务复跑，不将内部红队与自动评测当独立验证。

## dsx-ai-factory/run-ai

- type: github
- title: NVIDIA Run:ai open-source GPU orchestration platform
- url: https://github.com/dsx-ai-factory/run-ai
- direction: Kubernetes GPU 调度 / 多租户资源治理 / 工作负载抽象
- first_seen: 2026-10-14
- last_review: 2026-10-21
- next_review: 2026-10-28
- status: watchlist
- quality: A
- maturity: M1
- personal_value: medium-high
- watch_reason: NVIDIA 于 2026-10-13 开放 Apache-2.0 单仓源码，含控制面、集群组件、安装器、本地 Kind 路径及规模测试；尚缺可复现的相对现有调度器的真实集群收益。
- trigger_events:
  - 第三方部署或性能复现
  - 正式 release 与安装兼容矩阵
  - Workload Map / GPU Fractioning 的生产反馈
- last_review_result: 2026-10-21 官方代码与 release 已核，最新仍为 3.0.20（10-11）；新增材料主要是来源解读，未确认独立部署/平台级 benchmark，维持 A/M1。

## vLLM bidirectional KV transfer

- type: project
- title: Bi-Directional KV Transfer for Multi-Turn Agentic Workloads
- url: https://vllm.ai/blog/2026-10-12-bidirectional-kvxfer-multiturn-agentic-workload
- direction: 多轮 Agent serving / KV 缓存 / prefill-decode 分离
- first_seen: 2026-10-14
- last_review: 2026-10-21
- next_review: 2026-10-28
- status: watchlist
- quality: A
- maturity: M1
- personal_value: high
- watch_reason: vLLM v0.21.0 实现与可复现实验显示长多轮提示 TTFT 改善，作者评测关闭 prefill 前缀缓存；仍须验证真实缓存命中、KV 保留显存与多节点失效。
- trigger_events:
  - 独立多会话复现
  - 路由器与 KV TTL 生产改进
  - 与高命中前缀缓存的对照
- last_review_result: 2026-10-21 原始正文与实现线索仍可访问；定向发现的外部文章明确仅为来源解读而非复跑，未确认独立多会话、高前缀命中与失效复现，维持 A/M1。

## 2610.13778 / ReplaySSM

- type: paper / github
- title: ReplaySSM: Cache SSM Inputs, Not State
- url: https://arxiv.org/abs/2610.13778
- direction: 混合模型推理 / SSM 状态 / 推测解码 / 低精度
- first_seen: 2026-10-13
- last_review: 2026-10-20
- next_review: 2026-10-27
- status: watchlist
- quality: A
- maturity: M1
- personal_value: high
- watch_reason: 作者论文、vLLM 研究 fork、benchmark 脚本和框架集成 PR 支持核心机制；batch 256 的 1.20～1.47 倍 decode step 加速来自作者指定的四模型单卡配置，batch 1 无增益。
- trigger_events:
  - 上游框架正式 release
  - 独立跨硬件复跑
  - 长生成低精度质量验证
- last_review_result: 2026-10-20 arXiv 仍为 v1（10-09）；作者仓库列出 TensorRT-LLM/vLLM/FlashInfer 集成 PR，既有集成线索不作为首次采用。尚缺 release/revision 映射、长生成低精度与跨硬件独立完整链路验证，维持 A/M1。

## google/embeddinggemma-2

- type: project
- title: EmbeddingGemma 2
- url: https://huggingface.co/google/embeddinggemma-2
- direction: 多模态嵌入 / 代码检索 / 端侧 RAG
- first_seen: 2026-10-12
- last_review: 2026-10-20
- next_review: 2026-10-27
- status: watchlist
- quality: A
- maturity: M1
- personal_value: high
- watch_reason: 官方开放 740M 模型权重与完整模型卡，代码检索、跨模态和向量维度对照可复测；缺独立真实语料与跨设备端到端验证，优先观察 256/128 维质量和数值精度问题。
- trigger_events:
  - independent retrieval benchmark
  - device-level latency and memory reproduction
  - framework integration or checkpoint revision
- last_review_result: 2026-10-20 SGLang v0.5.22 已正式支持并提供 cookbook；外部 Strata2Signal 自报小语料检索（68 queries/2569 passages）有结果，但数据包未发布、内部多 Agent 审计不构成外部验证，维持 A/M1，待可复跑资产后再判断成熟度。

## openai/math

- type: github
- title: OpenAI mathematics manuscripts and proof artifacts
- url: https://github.com/openai/math
- direction: AI for science / 数学 / Lean 形式化验证
- last_review: 2026-10-21
- next_review: 2026-10-28
- watch_reason: 2026-10-06 首次公开 722 份手稿、372 个家族和部分 Lean 形式化；公开产物可核验，但未形式化结果可能有错，独立数学审查与命题语义核对仍待积累。
- trigger_events:
  - independent mathematical review
  - Lean formalization expansion
  - material corrections or retractions
  - independent build and proof audit
- last_review_result: 2026-10-21 仓库历史 10-07 撤回三份手稿并修订另 14 份，此前未补报；目录为 719 份/372 家族，README 自报约 42% top-line formalized。按实质勘误提前复评，已于 10-21 补报，不提升独立验证成熟度。

## torch-spyre/torch-spyre

- type: github
- title: PyTorch backend for IBM Spyre AIU
- url: https://github.com/torch-spyre/torch-spyre
- direction: 异构加速器 / PyTorch PrivateUse1 / Inductor / 推理运行时
- last_review: 2026-10-21
- next_review: 2026-10-28
- watch_reason: 2026-10-08 PyTorch 技术文章给出从二次建图到原生设备、驻留张量及有序队列的完整重构和 Granite 3.3 8B 对照；仓库有核心代码、文档与测试，但外部构建需 IBM 软件栈开发版本，缺独立复跑。
- trigger_events:
  - reproducible public build
  - independent performance reproduction
  - operator or model coverage expansion
  - upstream integration or release
- last_review_result: 2026-10-21 10-20 新技术文与 DataflowScheduler 代码补齐 KTIR→DataflowIR 边界，已按新技术增量单独推荐；V1 逐元素/广播/归约与局部启发式，matmul 与成本模型仍在推进，不能推断完整设备栈已可独立复跑。

## Muse Spark Open

- type: model
- title: Meta Muse Spark Open 816B-A42B
- url: https://huggingface.co/meta-models/Muse-Spark-Open-816B-A42B
- direction: 多模态开放权重 / MoE / Agent Serving
- first_seen: 2026-10-17
- last_review: 2026-10-17
- next_review: 2026-10-24
- status: watchlist
- quality: A
- personal_value: high
- main_evidence: 官方 BF16/NVFP4 权重、模型卡、评测方法及 HF 部署说明；816B/42B，文本/图像/音频/视频输入。
- missing_evidence: 独立同条件代码 Agent 评测、长上下文成本/准确率、完整安全报告、真实多租户吞吐。
- next_review_focus: 模型卡/许可更新、vLLM/SGLang 性能、第三方同口径复跑。

## Beam 501B-A23B

- type: model
- title: Reflection Beam 501B-A23B
- url: https://reflection.ai/beam-model-card
- direction: 开放权重 / 文本 Agent / MoE / 后训练
- first_seen: 2026-10-17
- last_review: 2026-10-17
- next_review: 2026-10-24
- status: watchlist
- quality: A
- personal_value: high
- main_evidence: 2026-10-16 权重正式发布；BF16/FP8/NVFP4、Apache 2.0、模型卡、部署和 TRL/Miles 配方。
- missing_evidence: 独立同 harness 的代码任务/推理 token 成本对照、长上下文生产表现；自蒸馏配方尚待发布。
- next_review_focus: 第三方复跑、自蒸馏配方实际交付、量化与 serving 成本。

## Zephon

- type: paper
- title: Elastic Determinism for Online, Stateful Foundation Model Data Loading Pipelines
- url: https://arxiv.org/abs/2610.03087
- direction: 分布式训练 / 数据加载 / 弹性确定性
- first_seen: 2026-10-17
- last_review: 2026-10-17
- next_review: 2026-10-24
- status: watchlist
- quality: A
- personal_value: high
- main_evidence: 论文与 PyTorch 技术文章、TorchTitan 集成代码；16→8/32/64 GPU 恢复时全局 batch hash 一致，DCLM/FineWeb 消融跨度明显缩小。
- missing_evidence: 独立大规模复跑、复杂动态课程/多模态 pipeline 的吞吐与恢复成本。
- next_review_focus: 主线上游集成、不同集群配置的恢复成本和外部复现。

## jerrysfls/HyQuant

- repo: jerrysfls/HyQuant
- url: https://github.com/jerrysfls/HyQuant
- direction: LLM Serving / Attention / KV cache / Triton
- first_seen: 2026-09-12
- last_review: 2026-10-17
- next_review: 2026-10-24
- last_review_result: 2026-10-17 定向核验未确认足以改变评级或单独推荐的新增证据。
- status: watchlist
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-10-03 仍未见稳定 release、框架集成或第三方端到端复现；转入长期观察
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

## openai/NavierStokesAndEuler

- repo: openai/NavierStokesAndEuler
- url: https://github.com/openai/NavierStokesAndEuler
- direction: AI Scientist / 形式化验证 / 数学
- first_seen: 2026-09-10
- last_review: 2026-10-16
- next_review: 2026-10-30
- status: watchlist
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-10-16 复查仍为 2026-09-08 与 09-10 两次公开提交，未发现新版正式发布或可核验的独立数学审查
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

## ifm-ai/uno

- type: github
- title: Uno: Unlocking Lossless Speedups in LLMs via Discrete Diffusion
- url: https://github.com/ifm-ai/uno
- direction: LLM 推理 / speculative decoding / 离散扩散
- last_review: 2026-09-24
- next_review: 2026-10-24
- watch_reason: 核心代码、训练 recipe、评测与 checkpoints 已公开，但截至本次复评仍未见稳定 release、主流 serving 集成或独立端到端复现，转入低频观察。
- trigger_events:
  - stable release
  - vLLM / SGLang integration
  - third-party reproduction
  - production adoption

## NVIDIA/TensorRT-Model-Connect

- type: github
- title: TensorRT Model Connect
- url: https://github.com/NVIDIA/TensorRT-Model-Connect
- direction: C++ 推理运行时 / 模型接入 / TensorRT / 验证契约
- last_review: 2026-10-22
- next_review: 2026-11-05
- watch_reason: 已公开核心代码、Qwen 端到端路径、模型 family 描述符、C++ runtime DSO 与 E2E oracle；截至 2026-10-08 未确认新的稳定 release 或独立硬件复跑，继续低频观察。
- trigger_events:
  - stable release
  - broader model qualification
  - independent hardware reproduction
  - ABI or bundle contract change
- last_review_result: 2026-10-22 release仍仅见TRTMC Nightly 75e25af75499（08-14），不作稳定版；未确认独立硬件复现。

## one2piece2hello/faibench_Frontier_InfraBench

- type: github
- title: Φ-Bench / Frontier InfraBench
- url: https://github.com/one2piece2hello/faibench_Frontier_InfraBench
- direction: AI 系统 / Coding Agent / Kernel / Runtime / Benchmark
- last_review: 2026-10-01
- next_review: 2026-10-29
- watch_reason: 85 项任务与离线评分仍可用，但当前未见稳定 release、独立跨硬件复跑或正式榜单；与同名活跃论文维持独立观察。
- trigger_events:
  - stable release
  - independent agent evaluation
  - cross-hardware recalibration
  - benchmark revision or leaderboard
## redhat-et/vllm-helion

- type: github
- title: Helion vLLM Linear Backend
- url: https://github.com/redhat-et/vllm-helion
- direction: LLM Serving / GPU Kernel / AOT Autotuning
- last_review: 2026-10-18
- next_review: 2026-10-25
- watch_reason: 2026-10-11 复评未确认上游合入、独立端到端 benchmark 或跨硬件结果；作者 fork 已开放 Helion 线性后端、预调配置与 benchmark 工具，逐形状调优及维护成本仍待验证。 2026-10-18 复评仍未确认上游合入或独立同配置端到端复现。
- trigger_events:
  - vLLM upstream merge
  - independent benchmark
  - Blackwell or AMD end-to-end result
  - autotuning cost reduction

---

## nvidia/Nemotron-3.5-Super-VL

- type: project
- title: NVIDIA Nemotron 3.5 Super VL
- url: https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Super-VL-120B-A12B-NVFP4
- direction: 开放多模态 MoE / Agent 推理 / 量化与缓存
- first_seen: 2026-10-16
- last_review: 2026-10-16
- next_review: 2026-10-23
- status: watchlist
- quality: A
- maturity: M1
- personal_value: high
- watch_reason: 120B-A12B 权重、技术报告、NVFP4 与服务配方已公开；需要独立同任务的质量/延迟/成本分层复现。
- trigger_events:
  - 独立 Agent 与视觉任务复跑
  - 量化、LiLiCorr、Dynamo 的消融与跨硬件结果
  - 权重、模型卡或许可实质变更

## huggingface/tokenizers#2508

- type: project
- title: BERT / Unicode normalizer optimization
- url: https://github.com/huggingface/tokenizers/pull/2508
- direction: tokenizer / CPU 性能 / 检索服务
- first_seen: 2026-10-16
- last_review: 2026-10-21
- next_review: 2026-10-28
- status: watchlist
- quality: A
- maturity: M1
- personal_value: high
- watch_reason: 原团队提供待合并 PR、分语种性能矩阵和复现代码；中文及短文本有回退，需确认合并与正式发布。
- trigger_events:
  - PR merge 与稳定版发布
  - 独立语种/长度矩阵复跑
  - 中文性能回退修复
- last_review_result: 2026-10-21 PR 仍为 Draft，16 commits、未合并；release 最新为 v1.0.0-rc.3，不能推断本优化已正式交付。外部 tokenizer 成本比较不等于该 PR 加速复现，维持 A/M1。

## vllm/push-kv-and-adaptive-verification

- type: project
- title: vLLM Push KV connector and online Adaptive Verification
- url: https://vllm.ai/blog/2026-10-14-nixl-push-connector
- direction: prefill-decode 分离 / 推测解码 / 在线校准
- first_seen: 2026-10-16
- last_review: 2026-10-16
- next_review: 2026-10-23
- status: watchlist
- quality: A
- maturity: M1
- personal_value: high
- watch_reason: 两项 10 月 14 日漏报实现均有原团队技术文和代码；Push 的极端加速限定 1P1D/EFA 且关闭 decode 前缀缓存，AV 的收益限定可变长验证与合适 batch。
- trigger_events:
  - 独立真实生产负载复跑
  - 与前缀缓存、动态路由及双向 KV 的对照
  - AV 对更多模型对与 batch 的收益验证


## 2610.22367

- type: paper
- title: Discovering state-of-the-art quantum circuits with large language models
- url: https://arxiv.org/abs/2610.22367
- direction: AI for science / verifiable search / quantum circuits
- first_seen: 2026-10-18
- last_review: 2026-10-18
- next_review: 2026-10-23
- status: watchlist
- quality: A
- maturity: M0
- personal_value: medium
- watch_reason: 八类基元有作者论文、程序校验和模逆 Lean 证明；仍需核查公开证明/电路资产、独立资源重算与物理门开销。
- trigger_events:
  - proof or circuit code release
  - independent resource recount
  - fault-tolerant cost analysis

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

## helion-compileiq-20261019

- type: systems / compiler
- title: Helion × NVIDIA CompileIQ 联合搜索
- url: https://pytorch.org/blog/one-search-two-layers-compiler-controls-inside-pytorch-helion-using-nvidia-compileiq/
- archived_at: 2026-10-20
- quality: A
- maturity: M1
- personal_value: extremely high
- key_conclusion: 有配置接口与预调优 kernel；GB200/CUDA13.3/Triton3.8 作者重测的 kernel 收益约 4.8%/6.9%，非端到端或独立结果；保留无 ACF 基线并逐环境校验。
- reconsider_if: 新架构独立复跑、工具链兼容性变化或完整模型收益公开。

## mlir-static-memory-planner-20261019

- type: compiler
- title: MLIR Static Memory Planner
- url: https://blog.llvm.org/posts/2026-08-24-gsoc-2026-static-memory-planner/
- archived_at: 2026-10-20
- quality: A
- maturity: M1
- personal_value: extremely high
- key_conclusion: 10-19 技术复盘，基础/控制流修正代码此前已合并；别名、嵌套释放与保守生命周期是主要学习价值，未证实通用性能收益。
- reconsider_if: 动态形状、复杂控制流支持或独立系统基准交付。

## anthropic-scion

- type: systems
- title: Scion source control
- url: https://www.anthropic.com/engineering/redesigning-source-control
- archived_at: 2026-10-20
- quality: A
- maturity: M0
- personal_value: high
- key_conclusion: 正文 10-13 发布、10-15 更新，列表 10-19 不作首发日；changeset/派生数据/在线客户端/不可变缓存值得学习，200 倍基础设施缩减为内部自报，未开源。
- reconsider_if: 实现交付、独立工作负载验证或故障恢复细节公布。

## sglang-v0.5.22

- type: github
- title: SGLang v0.5.22
- url: https://github.com/sgl-project/sglang/releases/tag/v0.5.22
- archived_at: 2026-10-20
- quality: A
- maturity: M1
- personal_value: high
- key_conclusion: 10-19 正式版；prefill_complete KV 分配为 opt-in，early 仍默认；特定压力负载 26.8% 吞吐/48.9% p95 TTFT 为作者结果，后续 rebase 验证仍需补齐。另修正混合模型推测解码与结构化输出的 Mamba 状态追踪边界。
- reconsider_if: 独立 PD 复跑、默认策略变化或状态恢复回归。

## torchtpu-20261020

- type: systems / github
- title: TorchTPU and vLLM TorchTPU
- url: https://github.com/google-pytorch/torch_tpu
- archived_at: 2026-10-21
- quality: A
- maturity: M1
- personal_value: extremely high
- key_conclusion: 10-20 新原生后端；公开 0.2.0 安装与文档，eager/StableHLO/PjRT 与插件路径可审查；无崩溃与数值容差检查不等价，vLLM 插件 Python3.12/v7x 与其他代际实验支持有边界。
- reconsider_if: 独立数值/成本复跑、动态形状及 RL colocation 支持变化。

## spyre-dataflow-scheduler

- type: compiler / github
- title: Spyre DataflowScheduler
- url: https://github.com/torch-spyre/dataflow-scheduler
- archived_at: 2026-10-21
- quality: A
- maturity: M1
- personal_value: extremely high
- key_conclusion: 10-20 技术文和 Apache-2.0 核心/测试/CLI；固定 LLVM22.1.3，KTIR→ScheduleIR→DFIR，以架构图合法化数据搬运，V1 局部启发式，matmul 尚待完善。
- reconsider_if: matmul、成本模型、独立端到端或其他硬件 backend 交付。

## vllm-elastic-ep-20261019

- type: systems
- title: vLLM Elastic EP near-zero downtime
- url: https://vllm.ai/blog/2026-10-19-elastic-ep-near-zero-downtime
- archived_at: 2026-10-21
- quality: A
- maturity: M1
- personal_value: high
- key_conclusion: 10-19 漏报已补；异步准备+NIXL EP 保持 CUDA Graph 地址/布局，指定 DeepSeekV4Pro/GB200 的扩容暂停0.82s、总耗时92.34s；v0.30.0 有四 GPU 扩缩容/准确率测试，非独立复现。
- reconsider_if: 独立跨拓扑复跑、失败恢复与控制面集成。

## mps-2.15-20261020

- type: systems
- title: MPS in PyTorch 2.15
- url: https://huggingface.co/blog/mps-pytorch-2-15
- archived_at: 2026-10-21
- quality: A
- maturity: M1
- personal_value: high
- key_conclusion: 10-20 HF 团队复盘，相关 grouped_mm/padding PR 9 月已合入；当前为候选版试用，2.16 另算。正文 MoE 5～6.5倍与小节1.3倍口径不同，日报不复述统一模型加速承诺；重点 GPU 偏移、driver memory 与 stream 生命周期。
- reconsider_if: 正式版、独立硬件/模型复跑与2.16交付。

## minilangbench-20261019

- type: evaluation / github
- title: MultiLangBench
- url: https://github.com/openai/MultiLangBench
- archived_at: 2026-10-21
- quality: B
- maturity: M1
- personal_value: high
- key_conclusion: 10-19 公开，10-21 补报；SQLite3.40.1 数据库状态接口，约24k转换测试、标准272子集、隔离/去SQLite约束明确。模型分数作者自报，不能等同完整SQL/并发行为或通用工程成功率。
- reconsider_if: 独立跨 harness 复跑、测试覆盖/污染审计。

## torchneuron-native-beta

- type: systems / github
- title: TorchNeuron native backend delivery
- url: https://github.com/aws-neuron/torch-neuronx
- archived_at: 2026-10-21
- quality: B
- maturity: M1
- personal_value: high
- key_conclusion: 10-21 核验代码、示例和安装已公开，torch2.14/torch-neuronx2.14.*需配套；旧同名包是XLA路径。静态shape/连续tensor限制、float64降为float32、TorchAO未交付需明确。
- reconsider_if: 独立构建/正确性/性能复现与动态形状或数值支持改变。

## mamba2-cutile-20261019

- type: systems / kernel
- title: cuTile Mamba-2 forward
- url: https://developer.nvidia.com/blog/accelerating-mamba-2-with-high-performance-forward-pass-kernels-in-nvidia-cuda-tile/
- archived_at: 2026-10-21
- quality: A
- maturity: M1
- personal_value: high
- key_conclusion: 10-19 技术文，10-21 正文恢复可读并补报；三kernel、布局/TensorMemory/自动调优和TileGym测试入口，B300前向1.14～1.82倍为作者自测，无反向/整训练收益。
- reconsider_if: 独立复跑、反向实现与完整训练benchmark。


## humming-20261021

- type: github / kernel
- title: Humming quantized inference kernels
- url: https://github.com/vllm-project/humming
- archived_at: 2026-10-22
- quality: A
- maturity: M1
- personal_value: extremely high
- key_conclusion: 10-21完整技术发布；此前已存在。量化表示、三类配置与JIT可审查；8H20端到端14%～43%包含BF16→FP8激活变化，不能全归因内核；autotune仍计划。
- reconsider_if: 独立同精度与质量复跑、autotune交付或重要硬件支持变化。

## flint-vllm-20261021

- type: systems / model backend
- title: Flint low-latency vLLM implementation
- url: https://github.com/vllm-project/vllm/pull/62938
- archived_at: 2026-10-22
- quality: A
- maturity: M1
- personal_value: high
- key_conclusion: 10-21专用镜像可用，模型PR仍Open；单Blackwell TP1小batch，NVFP4 GGUF实际W4A16/BF16KV；作者固定tree测试267passed1skip，非独立与非逐位数值验证。
- reconsider_if: 主线合并/稳定release、独立数值或多租户成本复跑。

## specter-v2-20261020

- type: paper / github
- title: Specter quantization-enabled speculative offloading
- url: https://arxiv.org/abs/2511.14102
- archived_at: 2026-10-22
- quality: A
- maturity: M1
- personal_value: high
- key_conclusion: 初版2025-11-18，v2于2026-10-20修订并有artifact；draft路由预测+FP16目标验证，单请求相对SpecMoEOff均值1.50x/最高1.88x为作者A100测量。公开包batch1，与论文额外batch实验分开；依赖锁定/资产哈希/状态边界可审查。
- reconsider_if: 独立A100与其他硬件复现、批量artifact交付或长上下文质量审计。


## nemotron-35-retriever-20261021

- type: model / retrieval
- title: Nemotron 3.5 Embed, Rerank and Parse
- url: https://huggingface.co/blog/nvidia/nemotron-retriever-world-class-agentic-retrieval
- archived_at: 2026-10-22
- quality: A
- maturity: M1
- personal_value: high
- key_conclusion: 10-21技术文；8B Embed卡标10-20、Parse标10-17。冻结语言部分保留对应BF16文本嵌入；新视觉能力、重排与结构解析各有独立成本。NVFP4需Blackwell/vLLM，量化不可沿用相同向量假设；Agent token减少不等于总GPU成本下降。Parse单遍72.74/16.1页秒、三遍75.20/10.5为不同H100配置。权重OpenMDW1.1。
- reconsider_if: 独立任务召回—全链成本评估、量化索引兼容验证或重要后端更新。

## torchneuron-profiling-20261021

- type: systems / tutorial
- title: Profiling TorchNeuron Part 1
- url: https://huggingface.co/blog/amazon/profiling-torchneuron-part-1
- archived_at: 2026-10-22
- quality: A
- maturity: M1
- personal_value: high
- key_conclusion: 10-21教程正文有可审查示例；PrivateUse1+Neuron trace对齐框架/运行时/硬件，循环内同步避免空设备计时。BF16[4,512]单active iteration中朴素/融合/compile设备时间2355/403/376us，不能当整模型或生产尾延迟。外链examples本次不可访问，不据此声称独立复跑。
- reconsider_if: 后续设备级分析或独立多负载复跑。

# Low-value / Deferred

> 低价值或当前证据不足的条目只保留最小状态，避免重复扫描和重复深评。

<!--
- id:
  reason:
  reconsider_after:
-->

---

- id: minimax-m31-flash / https://www.minimax.cn/blog/minimax-m31f
  reason: 10-20 已报 B；API 已上线但权重尚待开放，自报速度/成本与成绩缺完整同条件复跑，待模型卡与可部署资产。
  reconsider_after: 2026-10-23
- id: 2610.23328 / Peak-Memory Schedules You Can Trust
  reason: 10-16 新论文，内存规划方向匹配；仅初筛摘要，代码与可复跑资产待核实，不提前深评。
  reconsider_after: 2026-10-23
- id: 2610.23044 / Where Does Performance Go? C-to-Rust
  reason: 10-16 新论文，迁移后性能归因方向匹配；仅初筛，独立复跑与资产待核实。
  reconsider_after: 2026-10-23
- id: 2610.23787 / DLite
  reason: 10-16 新论文，无历史 draft KV 的推测解码；自报收益缺完整代码/checkpoint 与训练成本验证，先观察。
  reconsider_after: 2026-10-23
- id: xiaomi/mimo-v2.6-pro-ultraspeed
  reason: 10-19 阿里云平台上架，速度主张缺公开基线和复测方法；不因平台展示直接推荐。
  reconsider_after: 2026-10-23

- id: 2610.26632 / When the harness decides success
  reason: 10-19 新论文；合成重观察探针有预注册/跨provider复制，ARC四游戏单次运行局限明显；初筛后待核验代码、成本及独立复现。
  reconsider_after: 2026-10-26
- id: 2610.26693 / Parallel Language Models via Variational Decoding
  reason: 10-19 新论文；摘要称1.3B对照与2.3～5.7倍，代码仍写will release；默认观察，未深评。
  reconsider_after: 2026-10-26
- id: 2610.22791 / Harness-Policy Optimization
  reason: HF10-20发现；新论文先初筛，待公开代码/轨迹与同预算、留出集证据核验。
  reconsider_after: 2026-10-26
- id: FairStress / https://huggingface.co/blog/allenai/fairstress
  reason: Ai2 Enterprise Article属定向研究发现，不是HF官方Tier1；300场景/50K核心与成对扰动值得观察，待原报告和独立验证。
  reconsider_after: 2026-10-26
- id: ALTK-Evolve customer-service / https://huggingface.co/blog/ibm-research/altk-evolve-bc
  reason: IBM Enterprise Article仅定向候选；40/20测试任务、simulator及更多guideline token的收益边界需审计，不因榜单自称领先当天推荐。
  reconsider_after: 2026-10-26
- id: AnyLanguageModel 1.0 / https://huggingface.co/blog/anylanguagemodel-1-0
  reason: HF官方1.0发布与跨provider接口可信，当前Swift应用开发直接投入价值较低，保留低频；避免重复把已支持模型当新模型。
  reconsider_after: 2026-11-03

- id: 2610.28595 / RTLRepairBench
  reason: 10-20 v1；作者数据、formal/simulation与离线证据代码已公开；新论文先观察，待reset/首周期语义及完整复现实审。
  reconsider_after: 2026-10-26
- id: 2610.28576 / Token-Energy Law
  reason: 10-20 v1；三模型BF16与校准时间模型，仅初筛；跨配置外推与测量资产待核实。
  reconsider_after: 2026-10-27
- id: 2610.28369 / Dont Skip the Baseline
  reason: 10-20 v1；等专家计算预算的静态k对照值得关注，不能未读全文就判ACE已被证伪。
  reconsider_after: 2026-10-26
- id: 2610.28577 / AKV
  reason: 10-20 v1；thu-nics/AKV代码已公开，缓存操作历史决定状态的正确性重要；先观察，待评测/重定位语义与复跑核验。
  reconsider_after: 2026-10-26
- id: 2610.28441 / Stratified Sparse Attention
  reason: 10-20 v1；摘要称有CUDA代码与1M上下文加速，未深评同预算质量/成本和独立证据。
  reconsider_after: 2026-10-27
- id: 2610.28619 / Adaptive Multi-Token Prediction
  reason: 10-20 v1；在线horizon控制且保持verifier，摘要最佳相对固定窗约10%；新论文先观察。
  reconsider_after: 2026-10-27
- id: 2610.24648 / EdgeKernelBench
  reason: 10-17 v1、HF10-21发现；TVM/LEKA代码公开，但one-shot/引擎实验drivers、调优基线库及历史运行输出未包含，待核验复现覆盖。
  reconsider_after: 2026-10-26
- id: RFD4-Proteina / https://developer.nvidia.com/blog/design-proteins-with-rfd4-proteina-using-reward-guided-inference-time-search/
  reason: 10-21原始教程与代码入口已见，联合序列结构及reward-guided搜索；未核验完整湿实验/基线和独立成本证据，先观察。
  reconsider_after: 2026-10-26
- id: SynthID-Bio / https://deepmind.google/blog/introducing-synthid-bio/
  reason: 09-30历史候选正文已读，有三靶点作者湿实验与方法论文/代码交付声明；Nature正文不可访问，证据/对抗篡改与资产仍待核验，不推进DeepMind全源cursor。
  reconsider_after: 2026-10-26
- id: Raschka-classifier-history-and-jev / https://magazine.sebastianraschka.com/p/classifier-history-and-jev
  reason: 09-29教程已核原始日期及正文，主要为分类与校准解释，非新独立benchmark；当前投入优先级较低。
  reconsider_after: 2026-11-05

- id: granite-speech-5 / https://huggingface.co/blog/ibm-granite/granite-speech-5
  reason: 10-21 IBM Enterprise正文已核，2B ASR/翻译及470M CTC、4.1 Plus更新真实；现阶段语音工程投入优先级低，WER/RTFx作者测量，暂不推荐。
  reconsider_after: 2026-11-05
- id: kumo-forecast / https://huggingface.co/blog/nvidia/kumo-forecast
  reason: 10-21 NVIDIA Enterprise正文已核，340M MOMENT编码器+检索增强预测头及代码/权重；当前用户价值较低，未核实完整量化强baseline，暂不推荐。
  reconsider_after: 2026-11-05
- id: hf-train-agents-curriculum / https://huggingface.co/blog/huggingface/train-agents
  reason: 10-20 HF团队作者课程整合，虽为Community模板但作者官方；主要归纳既有学习材料，未识别足以改变当前判断的新技术，暂缓。
  reconsider_after: 2026-11-05

# Maintenance Notes

- 2026-10-22 用户要求新增订阅源：已在 PROMPT.md 纳入 DeepSeek 官方知乎 https://www.zhihu.com/org/deepseek-75/posts 与 X https://x.com/deepseek_ai，每日25h及独立cursor补漏；原API日志/官网路径保留。仅完成过知乎单篇与X单个发布串的未登录正文核验，尚未完成账号列表初始化，故两个新cursor保持未初始化。首次扫描须检查近期历史，并优先处理尚未写入日报的DeepInfer事件：知乎 https://zhuanlan.zhihu.com/p/2095560295930508953 （页面编辑于10-20 19:30，不当成首次发布时间）、X发布串 https://x.com/deepseek_ai/status/2112476496283775135 （10-20发布）。不能因已在对话解释而认定日报已补报。

- 2026-10-22（补核 2026-10-22T01:17:01+08:00）：HF列表发现的TorchNeuron profiling作为高价值后端作者定向证据入选；Nemotron3.5按重大Hub资产检测核验BF16/NVFP4/Parse模型卡，分别标注原始资产日期与公告日期。Granite Speech、Kumo Forecast及HF课程只保留最小待办；未扩展Community全量扫描。

- 2026-10-22（保存 2026-10-22T01:11:16+08:00）：先写2026-10-22.md再保存本状态；25h窗口为2026-10-20T23:57:13+08:00至2026-10-22T00:57:13+08:00。已访问全部固定源并对照各自旧cursor，处理可访问新增与漏项；当日此前无日报。22篇到期论文核对arXiv版本及定向资产，5个到期GitHub、2个到期Watchlist已复核；新论文仅初筛并列最小待办。OpenShell新正式版触发提前复评，Relay0.10.4仅轻检。
- 2026-10-22 cursor：OpenAI Security已跨Daybreak旧值，09-30推理提取与10-21Patch均已处理；Global Affairs六项历史候选正文核对后以政策/地区/培训/采用类为主，不构成当前技术推荐，闭合至10-14。Engineering新广告架构已报。Raschka通过archive恢复枚举，09-29教程已处理。PyTorch列表首项TorchTPU与旧Nine Members同日，均已处理，校正latest为TorchTPU。
- 2026-10-22 保留边界：OpenAI News/Index/Product/Research列表仍未跨旧cursor，Safety入口404；DeepMind SynthID/PrivateAI等正文可读但完整历史资产核验未闭合，PrivateAI按B级方案补报，SynthID留待办；Claude分页未跨旧值。Qwen主站/ModelScope/Seed/混元空动态页、智谱超时、MiniMax Blog/News本次仅导航，均不推进。HF主页经分页参数恢复可见Enterprise与Community列表，10-21三篇Enterprise及HF团队10-20课程已处理；定向发现Nemotron3.5资产后深核并报告，但未跨旧cursor，不能宣称官方历史已完整枚举；LMSYS空列表，Lattner无稳定日期列表；LLVM release notes不可访问，Linux主页7.2.12与目录仍仅7.2.11不一致，历史未闭合，均保留cursor。
- 2026-10-22 GitHub/Watchlist轻检：Active release和Watchlist模型/代码入口均访问；Codex稳定仍0.163.0、alpha9非正式，cuda-rust仍cuTile0.4/oxide0.2.1，其他可核验版本无重大新推荐。torch-spyre release与tokbench release失败，不将失败记为无更新。Flint模型PR62938仍Open，页面Merged字样属于关联博客PR，不混淆。Specter论文批量实验与公开batch1包明确分开。
- 2026-10-22 额度：官方News/Help与官方社交检索已执行；banked仍09-03/04及09-07既有规则，付费reset页面未确认实质新规则。社区Day16的12h caching/effective usage链接指向官方X但403，Day15仅截图。Help更新时间及auto-review免费现行说明不足以确定新公告日期；无可确认满足条件的新事件，monitor四字段保持，不提醒。ai-2本地为ACTIVE每日01:00 heartbeat；仅发现此一份日报automation配置，未设置模型或推理覆盖。

- 2026-10-21（保存 2026-10-21T01:11:54+08:00）：已先写 2026-10-21.md；25h 窗口为 2026-10-20T00:03:05+08:00 至 2026-10-21T01:03:05+08:00。固定源逐个访问并对照旧 cursor；PyTorch/vLLM 新文、OpenAI MultiLangBench 和 Mamba-2 漏项已核验报告。到期 Run:ai、双向 KV、tokenizers PR 维持观察并移至10-28；TorchNeuron交付和Mamba待办已处理。新日论文只做发现/初筛，不占满Active后强行新增。
- 2026-10-21 来源边界：OpenAI Research/Product 列表仍未跨旧值，Safety入口404；Engineering已遇旧cursor，Security与Global Affairs历史候选待完整处理，其余OpenAI cursor保留。DeepMind/Claude旧cursor补漏尚未闭合；HF列表混合官方和Enterprise/Community，未完整跨旧cursor。Qwen/ModelScope/Seed/混元动态页与智谱访问不全，Raschka/Lattner缺可确认最新枚举；LLVM release/Linux历史未闭合，LMSYS列表不完整。上述源不推进。NVIDIA正文访问恢复解决Mamba项，但全源仍未跨旧cursor，不推进。
- 2026-10-21 GitHub轻检：核验Active release及Watchlist代码/模型入口；Codex稳定版仍0.163.0，新alpha不作正式版。open-code-review1.13.2仅语言/路径维护；Relay0.10.3有凭据边界修复并简报。部分release访问失败（tokbench、SWE-Serve、torch-spyre），不声称这些仓库无更新。math历史发现10-07实质勘误，按触发规则提前复评并补报。
- 2026-10-21 额度：News/Help及官方社交定向查找已执行；社区提示Day12 effective usage和Day15 reset，但官方原帖未能直接核实，Help页更新时间本身不构成新公告。维持monitor四字段，待核实；无符合提醒条件的已确认新事件，不提醒。单纯已发生reset也不能自动等同未来预告或可领取banked reset。

- 2026-10-20（保存 2026-10-20T01:11:12+08:00）：日报已先写入 2026-10-20.md；扫描窗口 2026-10-19T00:01:27+08:00 至 2026-10-20T01:01:27+08:00。25h、逐源补漏、arXiv/HF Papers/OpenReview/ACL、GitHub/Watchlist 已执行可访问内容检查；7 个到期项维持评级并移至 10-27，Codex 新稳定版触发复评。新高价值技术复盘压缩归档，不突破 Active 容量。
- 2026-10-20 cursor 边界：仅对已确认 latest→old 范围全部检查的来源推进。OpenAI 分类页返回通用有限列表；DeepMind 历史候选仍缺关联原始论文/资产核验（SynthID Bio、Private AI Compute 等）；Claude/HF 列表未跨旧 cursor；Qwen/Seed/混元等动态页不完整；NVIDIA 新文正文失败；LLVM release/Linux release 历史未完整跨越旧值。上述源原值保留，继续补漏；不能把访问尝试视为全源成功。
- 2026-10-20 额度监控：官方 News/Help 的付费 reset 与 banked reset 说明未出现可确认的新预告；社交原帖当前不可核实，last_successful_scan、last_seen 和 last_alerted 均不推进，不发提醒。

- 2026-10-19 01:04 北京时间：完成 25h 与逐来源 cursor 扫描。DeepSeek 更新日志新增 10-17 模型与 Search/Fetch，已补报并推进该源 cursor；其他动态页或未完整跨越旧 cursor 的源保持原值。论文到期项核对 arXiv 修订，GitHub 到期项核对仓库和可访问 release；证据不足者维持等级并安排短期复核。Codex reset 仅见已发生消息，未发现符合提醒条件的可核验新预告。

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
