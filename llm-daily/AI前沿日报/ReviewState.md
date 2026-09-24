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

- last_seen_item: Rapidly scaling online storage to serve over 1 billion ChatGPT users
- last_seen_publish_time: 2026-09-11
- last_successful_scan: 2026-09-18T01:12:00+08:00

## OpenAI Safety

- last_seen_item: Our framework for reporting model misalignment
- last_seen_publish_time: 2026-09-16
- last_successful_scan: 2026-09-18T01:12:00+08:00

## OpenAI Security

- last_seen_item: Daybreak for Frontline Defenders
- last_seen_publish_time: 2026-09-03
- last_successful_scan: 2026-09-18T01:12:00+08:00

## OpenAI Global Affairs

- last_seen_item: Helping older adults use AI in everyday life
- last_seen_publish_time: 2026-09-16
- last_successful_scan: 2026-09-18T01:12:00+08:00

## Google DeepMind Blog

- last_seen_item: Introducing Gemini 3.8 Flash and 3.8 Flash Cyber
- last_seen_publish_time: 2026-09-02
- last_successful_scan: 2026-09-24T01:12:00+08:00

## Anthropic Newsroom

- last_seen_item: Introducing Claude Opus 5.5
- last_seen_publish_time: 2026-09-22
- last_successful_scan: 2026-09-24T01:12:00+08:00

## Claude Blog

- last_seen_item: Working at the frontier: How Balyasny Asset Management evaluates and governs Claude Fable 5
- last_seen_publish_time: 2026-09-17
- last_successful_scan: 2026-09-21T01:06:00+08:00

## DeepSeek Updates

- last_seen_item: DeepSeek-V4.1-Flash Release
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-21T01:06:00+08:00

## DeepSeek Homepage

- last_seen_item: DeepSeek-V4.1-Flash 发布
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-19T01:11:00+08:00

## Qwen Blog

- last_seen_item: Qwen3.8-LiveTranslate: Names the speaker. Carries the meaning.
- last_seen_publish_time: 2026-09-18
- last_successful_scan: 2026-09-21T01:10:00+08:00

## Qwen Chinese Blog

- last_seen_item: Qwen3Guard：实时安全，逐词响应
- last_seen_publish_time: 2025-09-23
- last_successful_scan: 2026-09-19T01:11:00+08:00

## Aliyun Model Studio New Models

- last_seen_item: deepseek-v4.1-flash
- last_seen_publish_time: 2026-09-13
- last_successful_scan: 2026-09-18T01:12:00+08:00

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
- last_successful_scan: 2026-09-24T01:12:00+08:00

## Moonshot Platform Blog

- last_seen_item: Kimi 开放平台：新功能发布记录
- last_seen_publish_time: 2025-11-07
- last_successful_scan: 2026-09-19T01:11:00+08:00

## ByteDance Seed Blog

- last_seen_item: SeedRealtime 音视频全双工大模型发布：走向全模态自然交互
- last_seen_publish_time: 2026-08-05
- last_successful_scan: 2026-09-21T01:06:00+08:00

## MiniMax Blog

- last_seen_item: MiniMax Music 3.0：新一代开放权重、生产级全能音乐模型
- last_seen_publish_time: 2026-08-13
- last_successful_scan: 2026-09-24T01:12:00+08:00

## MiniMax News

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## MiniMax Model Release Notes

- last_seen_item: MiniMax H3
- last_seen_publish_time: 2026-07-31
- last_successful_scan: 2026-09-19T01:11:00+08:00

## Tencent Hunyuan Research

- last_seen_item: From LR to ELR: A Better Heuristic for Pretraining Dynamics
- last_seen_publish_time: 2026-08-10
- last_successful_scan: 2026-09-21T01:10:00+08:00

## Tencent HY Research

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Hugging Face Official Blog

- last_seen_item: Know Who Spoke When: Build Real-Time, Multi-Speaker AI with NVIDIA Nemotron 3 Diarization
- last_seen_publish_time: 2026-09-23
- last_successful_scan: 2026-09-24T01:12:00+08:00

## LLVM Blog

- last_seen_item: GSoC 2026: Improving HLSL Support in clangd
- last_seen_publish_time: 2026-09-21
- last_successful_scan: 2026-09-24T01:12:00+08:00

## MaskRay

- last_seen_item: lld 23 ELF changes
- last_seen_publish_time: 2026-09-12
- last_successful_scan: 2026-09-21T01:06:00+08:00

## John Regehr

- last_seen_item: Looking for Missed Alarm Bugs in a Formal Verification Tool
- last_seen_publish_time: 2024-09-04
- last_successful_scan: 2026-09-19T01:11:00+08:00

## Chris Lattner

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Modular Blog

- last_seen_item: Modular 26.6: Open compiler contributions, audio generation, and expanded model support
- last_seen_publish_time: 2026-09-17
- last_successful_scan: 2026-09-24T01:12:00+08:00

## PyTorch

- last_seen_item: Hardware-Agnostic Models in vLLM
- last_seen_publish_time: 2026-09-22
- last_successful_scan: 2026-09-24T01:12:00+08:00

## Triton

- last_seen_item: Triton 3.8.0
- last_seen_publish_time: 2026-08-28
- last_successful_scan: 2026-09-21T01:06:00+08:00

## MLIR / LLVM Project Updates

- last_seen_item: LLVM 23.1.1
- last_seen_publish_time: 2026-09-08
- last_successful_scan: 2026-09-18T01:12:00+08:00

## vLLM

- last_seen_item: PD Serving of Qwen3.8-2.4T
- last_seen_publish_time: 2026-09-21
- last_successful_scan: 2026-09-24T01:12:00+08:00

## SGLang

- last_seen_item: SGLang and Miles Add Day-0 Support for DeepSeek-V4.1
- last_seen_publish_time: 2026-09-10
- last_successful_scan: 2026-09-21T01:06:00+08:00

## SGLang GitHub Releases

- last_seen_item: v0.5.20
- last_seen_publish_time: 2026-09-18
- last_successful_scan: 2026-09-22T01:07:00+08:00

## CUDA / NVIDIA Developer Technical Updates

- last_seen_item: How SWE-Serve Exposes the Gap Between Local Tests and Live Serving
- last_seen_publish_time: 2026-09-23
- last_successful_scan: 2026-09-24T01:12:00+08:00

## Lilian Weng

- last_seen_item: Harness Engineering for Self-Improvement
- last_seen_publish_time: 2026-07-04
- last_successful_scan: 2026-09-16T01:07:36+08:00

## Sebastian Raschka

- last_seen_item: GPT-6 Astra, Looped Transformers, and Hidden Reasoning
- last_seen_publish_time: 2026-09-09
- last_successful_scan: 2026-09-15T01:06:56+08:00

## Chip Huyen

- last_seen_item: Common pitfalls when building generative AI applications
- last_seen_publish_time: 2025-01-16
- last_successful_scan: 2026-09-14T01:00:46+08:00

## GCC Releases

- last_seen_item: GCC 13.5
- last_seen_publish_time: 2026-09-11
- last_successful_scan: 2026-09-21T01:06:00+08:00

## Linux Kernel Releases

- last_seen_item: Linux 7.2.6
- last_seen_publish_time: 2026-09-14
- last_successful_scan: 2026-09-21T01:06:00+08:00

---

# Codex Usage Monitor State

- last_successful_scan: 2026-09-24T01:12:00+08:00
- last_seen_announcement: GPT-6 Sol and GPT-6 Luna — higher Codex usage limits, exact increase not published
- last_seen_publish_time: 2026-09-22
- last_alerted_announcement: GPT-6 Sol and GPT-6 Luna — higher Codex usage limits, exact increase not published

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
- last_review: 2026-09-23
- next_review: 2026-09-30
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
  - 2026-09-23 复评仍未确认官方代码、训练 recipe 或第三方复现。
- known_assets:
  - 论文
  - 规模化实验与消融
- next_review_focus:
  - 代码或训练 recipe 是否发布
  - 更大模型、非 Cerebras 硬件与第三方复现
  - 推理加速的质量退化与端到端收益
- discovery_source: Hugging Face Daily Papers / arXiv recent

## 2609.04523

- title: MaxKernel: Agentic Kernel Generation for TPUs
- url: https://arxiv.org/abs/2609.04523
- direction: AI 系统 / 编译器 / TPU kernel agent
- first_seen: 2026-09-08
- last_review: 2026-09-24
- next_review: 2026-10-01
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 作者在 50 个 JaxBench 任务及真实模型 workload 上评估多 Agent kernel 优化闭环。
  - 官方仓库已提供 MaxKernel、JAXBench、MaxCode、文档与测试资产；本次复评可见仓库已有 311 次提交，但未见稳定 release 或独立复现。
  - 2026-09-24 复评可见仓库仍在改进搜索脚本、输入生成与事件压缩，但未形成稳定 release 或第三方结果。
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
- last_review: 2026-09-23
- next_review: 2026-09-30
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
- last_review: 2026-09-23
- next_review: 2026-09-30
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
- last_review: 2026-09-19
- next_review: 2026-09-26
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

## 2609.04971

- title: BeaconKV: Training-Free KV Cache Compression via Representative Beacon Queries
- url: https://arxiv.org/abs/2609.04971
- direction: LLM Serving / KV cache / 长上下文推理
- first_seen: 2026-09-10
- last_review: 2026-09-23
- next_review: 2026-09-30
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
- last_review: 2026-09-20
- next_review: 2026-09-25
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
- last_review: 2026-09-20
- next_review: 2026-09-25
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
- last_review: 2026-09-21
- next_review: 2026-09-26
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
- last_review: 2026-09-22
- next_review: 2026-09-27
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
- last_review: 2026-09-23
- next_review: 2026-09-30
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
- last_review: 2026-09-23
- next_review: 2026-09-30
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
- last_review: 2026-09-22
- next_review: 2026-09-27
- status: active
- quality: B
- maturity: M0
- personal_value: high
- main_evidence:
  - 对约 80M～1B active parameters、最高 8.5B total parameters 的 dense 与 MoE 模型进行重复数据对照。
  - 作者发现 MoE 在约 4 次重复后即明显受损，重复 32 次后基本丧失相对 dense 的优势；强 masking 可缓解但不能替代独特数据。
  - 2026-09-22 定向复核未找到可核验的作者训练代码或独立复现，维持观察。
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
- last_review: 2026-09-22
- next_review: 2026-09-27
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
- last_review: 2026-09-24
- next_review: 2026-10-01
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
- last_review: 2026-09-24
- next_review: 2026-10-01
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
- last_review: 2026-09-24
- next_review: 2026-10-01
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
- last_review: 2026-09-20
- next_review: 2026-09-25
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
- last_review: 2026-09-20
- next_review: 2026-09-25
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
- last_review: 2026-09-20
- next_review: 2026-09-25
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
- last_review: 2026-09-23
- next_review: 2026-09-30
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
- last_review: 2026-09-24
- next_review: 2026-10-01
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 官方技术报告与开放模型资产说明 CED、CSA2、FP4 KV 和 SWA Bounded Replay 的协同设计。
  - 作者报告全局 KV 常驻 HBM 约 890 bytes/token，长期持久缓存约为 V4-Flash 的八分之一。
  - 2026-09-24 复评确认 vLLM Ascend 已提供 W8A8 多机部署教程，但通用 vLLM/SGLang 对 CSA2 与 FP4 KV 的完整支持仍未确认。
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
- last_review: 2026-09-23
- next_review: 2026-09-30
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
- last_review: 2026-09-22
- next_review: 2026-09-26
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
- last_review: 2026-09-22
- next_review: 2026-09-28
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
- last_review: 2026-09-23
- next_review: 2026-09-28
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 让 harnessing agent 在执行前审阅并改写 student 响应，再在目标 harness 动作空间内构造 SFT 轨迹，把专用 harness 诱导的行为蒸馏进权重。
  - 作者在 SpreadsheetBench、AppWorld、USPTO 上报告 Qwen3.5-9B 宏平均成功率 23.3%→44.3%，并高于保留优化 harness 的 41.7%。
  - 官方仓库公开三域任务集、harness bank、rollout/SFT 代码、Docker 环境、测试与三个 LoRA checkpoints。
- missing_evidence:
  - 结果均为作者自报，缺少第三方跨模型复跑。
  - 教师调用、harness 演化与训练成本尚未和更简单蒸馏基线充分拆分。
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
- last_review: 2026-09-24
- next_review: 2026-09-29
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
  - 长工具输出删除可能丢失关键证据，前缀稳定假设与客户端原生压缩的交互需实测。
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
- last_review: 2026-09-24
- next_review: 2026-09-29
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
  - 任务与榜单刚公开，尚缺独立复跑、verifier 缺陷审计和跨推理引擎迁移。
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
- last_review: 2026-09-24
- next_review: 2026-09-30
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
- last_review: 2026-09-24
- next_review: 2026-10-01
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-09-24 复评可见 vLLM v0.29.0 兼容性与 KV cache 压力调度仍在 issue 阶段，未见稳定 release
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
- last_review: 2026-09-24
- next_review: 2026-10-01
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-09-24 可见搜索脚本文档、benchmark 输入初始化和事件压缩仍在迭代，未确认重要 release 或外部复现
- main_evidence:
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
- url: https://github.com/NVlabs/cuda-oxide
- direction: GPU 编译器 / Rust / CUDA SIMT kernel
- first_seen: 2026-09-09
- last_review: 2026-09-24
- next_review: 2026-10-01
- status: active
- quality: B
- personal_value: high
- last_release: v0.2.1（2026-06-10）
- last_commit_or_major_delta: 2026-09-24 复评仍以 v0.2.1 为最新稳定 release，未确认重要版本或架构变化
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
- last_review: 2026-09-24
- next_review: 2026-10-01
- status: active
- quality: B
- personal_value: high
- last_release: v0.3.1（2026-09-06）
- last_commit_or_major_delta: 2026-09-24 复评仍以 v0.3.1 为最新稳定 release，未确认重要版本或架构变化
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

## openai/NavierStokesAndEuler

- repo: openai/NavierStokesAndEuler
- url: https://github.com/openai/NavierStokesAndEuler
- direction: AI Scientist / 形式化验证 / 数学
- first_seen: 2026-09-10
- last_review: 2026-09-23
- next_review: 2026-09-30
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-09-23 仍见两次公开提交、无 PR 记录，未确认外部数学审查结论
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
- last_review: 2026-09-19
- next_review: 2026-09-26
- status: active
- quality: B
- personal_value: high
- last_release: v0.1.0（2026-08-18），本次仍为最新
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
- last_review: 2026-09-23
- next_review: 2026-09-30
- status: active
- quality: A
- personal_value: high
- last_release: 2026-09-17 可见 0.155.0-alpha.16 等预发布构建；普通 alpha release 不视为重大能力结论
- last_commit_or_major_delta: 2026-09-10 OpenAI 宣布 Agents API 由开源 Codex harness 驱动；2026-09-23 复评仍未找到托管版本映射
- main_evidence:
  - 成熟 Rust 主体仓库，包含 codex-rs、CLI、SDK、文档、工具、测试与长期提交历史。
  - 官方将其定位为 Agents API 的开源 harness 基础，可对照托管服务理解模型、工具、上下文和 sandbox 的边界。
- missing_evidence:
  - 托管 API 与公开仓库不完全等价，服务端调度、隔离和运维实现并未全部开源。
  - 仍需核对具体 Agents API harness 版本与仓库 revision 的对应关系。
  - 2026-09-16 可见高频 alpha 构建，但 release 页面没有提供足以验证上述映射的稳定说明。
  - 2026-09-23 仍只有高频预发布构建，未见稳定说明或 Agents API revision 对应表。
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
- last_review: 2026-09-20
- next_review: 2026-09-25
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
  - 2026-09-15 复评未发现新的独立评测、跨硬件复现或稳定 release。
  - 2026-09-20 复评未发现新的独立评测、跨硬件复现或正式榜单更新。
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
- last_review: 2026-09-24
- next_review: 2026-10-01
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-09-24 复评未见稳定 release、框架集成或第三方端到端复现
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

## JustVugg/colibri

- repo: JustVugg/colibri
- url: https://github.com/JustVugg/colibri
- direction: LLM Inference / MoE / Memory Hierarchy / Storage Streaming
- first_seen: 2026-09-15
- last_review: 2026-09-19
- next_review: 2026-09-26
- status: active
- quality: B
- personal_value: high
- last_release: v1.11.0（2026-09-13），本次仍为最新
- last_commit_or_major_delta: 2026-09-14 GitHub Explore 更新并进入当日推荐面
- main_evidence:
  - 纯 C 推理引擎把 VRAM、RAM 和 NVMe 作为统一层级，按 MoE 路由结果调度专家权重，并覆盖九类模型架构。
  - Apache-2.0，约 31.4k stars；公开 benchmark protocol、质量检查、端到端数据和负面结果记录要求。
- missing_evidence:
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
- last_review: 2026-09-24
- next_review: 2026-10-01
- status: active
- quality: B
- personal_value: high
- last_release: PyPI 可安装；Rust 后端仅源码 checkout 可用
- last_commit_or_major_delta: 2026-09-24 复评未见独立复现、稳定 Rust 后端 release 或新的跨硬件结果
- main_evidence:
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

## alibaba/open-code-review

- repo: alibaba/open-code-review
- url: https://github.com/alibaba/open-code-review
- direction: Coding Agent / Code Review / CI / Deterministic Harness
- first_seen: 2026-09-15
- last_review: 2026-09-19
- next_review: 2026-09-26
- status: active
- quality: B
- personal_value: high
- last_release: v1.12.6（2026-09-18）
- last_commit_or_major_delta: v1.12.6 主要为 viewer 界面整理及测试修复，未改变核心判断
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
- last_review: 2026-09-23
- next_review: 2026-09-30
- status: active
- quality: B
- personal_value: high
- last_release: lp_fa4 标为 release candidate，未确认稳定版本
- last_commit_or_major_delta: 2026-09-23 仓库可见 GDPA、Block Attention、Multi-CTA Norm Fusion 与 GDPA Megakernel，累计 23 次提交
- main_evidence:
  - PyTorch 官方技术文章给出 TMEM scale 布局、反向量化与训练模块集成细节。
  - 作者提供核心代码、smoke tests 和 benchmark；16K KV tokens 模块报告约 1.30 倍收益。
  - 仓库已扩展为四组面向 Hopper/Blackwell 的广告与推荐训练 kernel，并给出各项目依赖和入口。
- missing_evidence:
  - 缺少独立复跑、跨硬件结果和更多序列长度的端到端稳定性证据。
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
- last_review: 2026-09-24
- next_review: 2026-10-01
- status: active
- quality: B
- personal_value: high
- last_release: v0.10.1（2026-09-03）；另有基准复现分支 release/0.9.1-mlpinf
- last_commit_or_major_delta: 2026-09-24 复评补确认 v0.10.1：双 DGX Spark TP=2、JetSpec、FP8 ViT/DART 与实验服务器重构
- main_evidence:
  - 官方 C++ 推理代码、配置、测试、量化 checkpoint 和 MLCommons harness 可供审计。
  - 20 段对话 1007 轮性能负载在单台 Thor 用时 24 分 36 秒；文章细分 KV/循环状态缓存和树形 MTP 收益。
  - v0.10.1 官方说明称实验服务器磁盘占用下降 60%～99%、冷启动时间下降 50%，并新增双 DGX Spark TP=2 与多种推测解码路径。
- missing_evidence:
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
- last_review: 2026-09-19
- next_review: 2026-09-26
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
- last_review: 2026-09-23
- next_review: 2026-09-30
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
- last_review: 2026-09-20
- next_review: 2026-09-25
- status: active
- quality: A
- personal_value: high
- last_release: 未确认稳定 release
- last_commit_or_major_delta: 2026-09-18 NVIDIA 将其正式定位为 GenAI-Perf 后继者；仓库已有约 887 次提交
- main_evidence:
  - 多进程负载 worker、独立结果处理服务与 ZMQ 协调，直接处理高并发时客户端先成为瓶颈的问题。
  - 提供核心实现、测试、插件系统、Kubernetes operator、生产 trace 回放、SLA/goodput、服务端遥测与多次运行置信区间。
  - 支持 vLLM、SGLang、TensorRT-LLM 等服务端路径和多种生成式 AI 端点，采用 Apache-2.0 许可。
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

## huggingface/tokbench

- repo: huggingface/tokbench
- url: https://github.com/huggingface/tokbench
- direction: LLM Systems / Tokenization / Benchmark
- first_seen: 2026-09-22
- last_review: 2026-09-22
- next_review: 2026-09-27
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
- last_review: 2026-09-24
- next_review: 2026-09-29
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
