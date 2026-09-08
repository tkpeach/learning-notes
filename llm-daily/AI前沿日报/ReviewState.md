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

- last_seen_item: An Alien Mind
- last_seen_publish_time: 2026-09-06
- last_successful_scan: 2026-09-08T10:06:07+08:00

## OpenAI Index

- last_seen_item: An Alien Mind
- last_seen_publish_time: 2026-09-06
- last_successful_scan: 2026-09-08T10:06:07+08:00

## OpenAI Product

- last_seen_item: GPT-6 Astra: A new generation of intelligence
- last_seen_publish_time: 2026-09-03
- last_successful_scan: 2026-09-08T10:06:07+08:00

## OpenAI Research

- last_seen_item: Research acceleration: The view inside OpenAI Research
- last_seen_publish_time: 2026-09-06
- last_successful_scan: 2026-09-08T10:06:07+08:00

## OpenAI Engineering

- last_seen_item: Jalapeño’s first results show industry-leading speed and efficiency in AI inference
- last_seen_publish_time: 2026-08-25
- last_successful_scan: 2026-09-08T10:06:07+08:00

## OpenAI Safety

- last_seen_item: An Alien Mind
- last_seen_publish_time: 2026-09-06
- last_successful_scan: 2026-09-08T10:06:07+08:00

## OpenAI Security

- last_seen_item: Daybreak for Frontline Defenders
- last_seen_publish_time: 2026-09-03
- last_successful_scan: 2026-09-08T10:06:07+08:00

## OpenAI Global Affairs

- last_seen_item: Supporting independent journalism in Ukraine
- last_seen_publish_time: 2026-09-07
- last_successful_scan: 2026-09-08T10:06:07+08:00

## Google DeepMind Blog

- last_seen_item: Introducing Gemini 3.8 Flash and 3.8 Flash Cyber
- last_seen_publish_time: 2026-09-02
- last_successful_scan: 2026-09-08T10:06:07+08:00

## Anthropic Newsroom

- last_seen_item: Introducing Claude Fable 5.1 and Claude Mythos 5.1
- last_seen_publish_time: 2026-09-01
- last_successful_scan: 2026-09-08T10:06:07+08:00

## Claude Blog

- last_seen_item: A guide to the anatomy of effective commerce agents
- last_seen_publish_time: 2026-09-02
- last_successful_scan: 2026-09-08T10:06:07+08:00

## DeepSeek Updates

- last_seen_item: DeepSeek-V4-Flash-Vision-Exp Release
- last_seen_publish_time: 2026-08-21
- last_successful_scan: 2026-09-08T10:06:07+08:00

## DeepSeek Homepage

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Qwen Blog

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Qwen Chinese Blog

- last_seen_item: Qwen3Guard：实时安全，逐词响应
- last_seen_publish_time: 2025-09-23
- last_successful_scan: 2026-09-08T10:06:07+08:00

## Aliyun Model Studio New Models

- last_seen_item: qwen3.8-max-0902
- last_seen_publish_time: 2026-09-02
- last_successful_scan: 2026-09-08T10:06:07+08:00

## ModelScope Qwen

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Zhipu Research

- last_seen_item: GLM-5.3-Flash：前沿智能进入普惠时代
- last_seen_publish_time: 2026-08-26
- last_successful_scan: 2026-09-08T10:06:07+08:00

## Kimi Blog

- last_seen_item: Kimi K3
- last_seen_publish_time: 2026-07-16
- last_successful_scan: 2026-09-08T10:06:07+08:00

## Moonshot Platform Blog

- last_seen_item: Kimi 开放平台：新功能发布记录
- last_seen_publish_time: 2025-11-07
- last_successful_scan: 2026-09-08T10:06:07+08:00

## ByteDance Seed Blog

- last_seen_item: SeedRealtime 音视频全双工大模型发布：走向全模态自然交互
- last_seen_publish_time: 2026-08-05
- last_successful_scan: 2026-09-08T10:06:07+08:00

## MiniMax Blog

- last_seen_item: MiniMax Music 3.0：新一代开放权重、生产级全能音乐模型
- last_seen_publish_time: 2026-08-13
- last_successful_scan: 2026-09-08T10:06:07+08:00

## MiniMax News

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## MiniMax Model Release Notes

- last_seen_item: MiniMax H3
- last_seen_publish_time: 2026-07-31
- last_successful_scan: 2026-09-08T10:06:07+08:00

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
- last_successful_scan: 2026-09-08T10:06:07+08:00

## MaskRay

- last_seen_item: Block frequency
- last_seen_publish_time: 2026-08-23
- last_successful_scan: 2026-09-08T10:06:07+08:00

## John Regehr

- last_seen_item: Looking for Missed Alarm Bugs in a Formal Verification Tool
- last_seen_publish_time: 2024-09-04
- last_successful_scan: 2026-09-08T10:06:07+08:00

## Chris Lattner

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Modular Blog

- last_seen_item: Mojo is now open source!
- last_seen_publish_time: 2026-08-18
- last_successful_scan: 2026-09-08T10:06:07+08:00

## PyTorch

- last_seen_item: Alibaba Cloud, Ant Group, Cambricon and Huawei Come Together in Shanghai to Advance the Open Source AI Stack at PyTorch Conference China
- last_seen_publish_time: 2026-09-07
- last_successful_scan: 2026-09-08T10:06:07+08:00

## Triton

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## MLIR / LLVM Project Updates

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## vLLM

- last_seen_item: Serving LLMs on Tenstorrent Hardware: Inside the vLLM TT Plugin
- last_seen_publish_time: 2026-09-07
- last_successful_scan: 2026-09-08T10:06:07+08:00

## SGLang

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## CUDA / NVIDIA Developer Technical Updates

- last_seen_item: Building a Memory-Driven Agent with NVIDIA NemoClaw
- last_seen_publish_time: 2026-09-04
- last_successful_scan: 2026-09-08T10:06:07+08:00

## Lilian Weng

- last_seen_item: Harness Engineering for Self-Improvement
- last_seen_publish_time: 2026-07-04
- last_successful_scan: 2026-09-08T10:06:07+08:00

## Sebastian Raschka

- last_seen_item:
- last_seen_publish_time:
- last_successful_scan:

## Chip Huyen

- last_seen_item: Common pitfalls when building generative AI applications
- last_seen_publish_time: 2025-01-16
- last_successful_scan: 2026-09-08T10:06:07+08:00

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
- last_review: 2026-09-08
- next_review: 2026-09-12
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
- last_review: 2026-09-08
- next_review: 2026-09-13
- status: active
- quality: B
- maturity: M1
- personal_value: high
- main_evidence:
  - 作者在 50 个 JaxBench 任务及真实模型 workload 上评估多 Agent kernel 优化闭环。
  - 官方仓库已提供 MaxKernel、JAXBench、MaxCode、文档与测试资产。
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
- last_review: 2026-09-08
- next_review: 2026-09-13
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
- last_review: 2026-09-08
- next_review: 2026-09-12
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
- last_review: 2026-09-08
- next_review: 2026-09-13
- status: active
- quality: B
- personal_value: high
- last_release: 未发现稳定 release
- last_commit_or_major_delta: 2026-09-03 MaxKernel 论文与对应代码公开
- main_evidence:
  - 仓库包含 MaxKernel、JAXBench、MaxCode、文档、CI 与测试，不是仅有论文说明。
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
