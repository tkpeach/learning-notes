# AI 前沿日报｜Codex 长期执行提示词

你需要每日生成《AI 前沿日报》。

这不是一次性回答，而是一个需要**读取持久状态 → 扫描公开信息 → 更新状态 → 写入日报文件**的长期任务。

---

# 【0. 文件与执行规则】

## 工作目录

在当前项目中使用：

```text
AI前沿日报/
```

如果目录不存在则创建。

每天生成：

```text
AI前沿日报/YYYY-MM-DD.md
```

其中日期使用：

```text
Asia/Shanghai
```

即北京时间。

长期状态保存到：

```text
AI前沿日报/ReviewState.md
```

如果 `ReviewState.md` 不存在，则创建空的初始状态。

## 每次运行顺序

严格执行：

```text
读取 ReviewState.md
        ↓
读取 Source Cursor
        ↓
执行 25h realtime scan
        +
执行 per-source last_seen cursor 补漏扫描
        ↓
执行 Codex 额度重置 / 临时刷新监控
        ↓
扫描论文 / GitHub / Watchlist
        ↓
候选筛选与复评
        ↓
生成最终日报
        ↓
写入 AI前沿日报/YYYY-MM-DD.md
        ↓
更新 ReviewState.md
        ↓
若发现新的 Codex 额度公告，仅在 Codex 窗口提示
```

必须先完成全部扫描和状态处理，再写最终日报。

## 输出要求

最终日报使用中文 Markdown。

日报文件中**只允许包含最终日报正文**。

禁止把以下内容写入日报：

- 搜索过程
- shell / tool 调用日志
- 网络访问日志
- 扫描状态
- 候选池
- Review State
- Source Cursor
- cache
- reasoning
- 质量检查过程
- 调试信息
- “正在搜索”等过程说明
- 无关说明

这些内容只用于内部执行或 `ReviewState.md`。

如果运行环境要求输出一条最终消息：

- 正常情况下只简单说明：

```text
日报已写入 AI前沿日报/YYYY-MM-DD.md
```

- 如果本次运行发现了**新的、可确认的 Codex 额度重置 / 临时刷新 / usage limit 变化公告**，则在上述文件完成提示之后，额外在 **Codex 当前窗口**输出一次简短提醒。该提醒不得写入日报文件。
- 如果没有新的 Codex 额度公告，不输出“无新增”等占位信息，避免每日噪声。
- 不要在终端最终输出中重复整篇日报。

---

# 【定位】

日报是：

> **AI 技术情报 + 学习优先级**

不是单纯 0-day 新闻流。

业界新闻保持较高时效性。

论文与 GitHub 优先：

- 质量
- 证据成熟度
- 对用户实际价值

允许数周甚至更长时间以后再推荐。

真正高价值内容可以详细分析。

普通内容保持简短。

---

# 【固定结构】

日报必须严格使用：

```markdown
# AI 前沿日报｜YYYY-MM-DD

## Part 1/3

# 今日总览

# 业界进展

## Part 2/3

# 系统与编译器进展

# GitHub 高价值项目洞察

## Part 3/3

# 科研进展

# 本期最值得关注
```

无合格内容时写：

```text
本窗口该部分无重要新增。
```

---

# 【1. 每日实时扫描算法】

实时扫描必须使用：

> **25h realtime scan + per-source last_seen cursor**

两套机制并行执行。

它们解决不同问题：

```text
25h realtime scan
负责时效性

per-source last_seen cursor
负责完整性
```

不得只执行其中一种。

## 1.1 25h realtime scan

每次运行时，对所有固定实时扫描源检查当前运行时间之前最近 25 小时内的真实新增。

必须核验内容的：

- 原始 publish 时间
- 原始 update 时间

不能把以下时间误判为新增：

- 搜索引擎抓取时间
- 列表页重新出现时间
- 聚合站收录时间
- 转载时间
- 网页重新索引时间
- 页面模板变化时间
- 页面更新时间但正文没有重要变化

## 1.2 Per-source last_seen cursor

对**每一个固定扫描源独立维护 cursor**。

在 `ReviewState.md` 中保存压缩状态：

```text
source
last_seen_item
last_seen_publish_time
last_successful_scan
```

不得只维护一个全局 cursor。

每次扫描一个固定源时：

```text
打开该源最新内容
        ↓
从最新条目向历史方向检查
        ↓
持续检查
        ↓
直到遇到 last_seen_item
```

然后判断：

```text
current latest
      ↓
      ↓ 这些条目是否已经在日报报告？
      ↓
last_seen_item
```

所有“此前没有报告 + 真实属于该源新增”的内容都必须进入本次候选。

## 1.3 Missed-item backfill

如果 cursor 扫描发现某条内容的原始发布日期已经超过 25 小时，但是：

```text
它位于当前最新条目与 last_seen_item 之间
+
此前日报没有报告
```

则必须作为：

> **missed-item backfill**

补报一次。

补报时：

- 使用真实发布日期
- 不得伪装为今天发布
- 必要时明确写“此前漏报，原始发布于 YYYY-MM-DD”
- 补报一次后正常去重

## 1.4 Cursor 推进规则

只有满足以下全部条件：

```text
成功访问该源
+
能够确认当前最新可见条目
+
已经完成 latest → old cursor 范围检查
+
已经处理其中所有未报告新增
```

才允许推进：

```text
last_seen_item
last_seen_publish_time
last_successful_scan
```

如果发生：

- 网站不可访问
- 页面内容不完整
- 搜索结果不确定
- 无法确定最新条目
- 只获得搜索摘要
- 页面加载失败
- 日期无法确认

则：

> **不得推进 cursor。**

## 1.5 只有日期、没有时间的情况

如果官方源只显示 `YYYY-MM-DD` 而没有精确时间，采取保守策略。

如果某条内容位于 `latest → last_seen_item` 范围内，而且此前没有报告，必须进一步检查。

不能仅因为无法确认小时级时间而丢弃。

## 1.6 Cursor 与 25h 窗口的关系

每次都必须同时执行：

```text
A. 最近 25h 扫描

B. latest → last_seen cursor 扫描
```

最终候选集合：

```text
Candidate =
25h realtime items
∪
cursor missed items
```

再执行去重。

因此：

- 一次搜索失败
- 官方页面延迟索引
- Codex 某天没有执行
- 单次日报漏检
- 某网站短暂不可访问

都不能导致真实新增永久消失。

---

# 【2. 海外 Tier 1 官方源】

每日扫描：

- OpenAI News
- OpenAI Index
- OpenAI Product
- OpenAI Research
- OpenAI Engineering
- OpenAI Safety
- OpenAI Security
- OpenAI Global Affairs
- Google DeepMind Blog
- Anthropic Newsroom
- Claude Blog

这些源全部纳入：

```text
25h realtime scan
+
per-source last_seen cursor
```

不要新增其他 OpenAI 源。

---

# 【3. 中国大模型 Tier 1 官方源】

只扫描以下来源，不扩展 Tier 2。

## 中文优先规则

同一官方内容如果存在中文网页：

> **必须优先读取、总结并链接中文网页。**

只有没有可用中文官方正文时才使用英文官方页。

## DeepSeek

主发现入口：

```text
https://api-docs.deepseek.com/updates/
```

官方稳定 Change Log，用于发现模型、API、重大变化。

辅助入口：

```text
https://www.deepseek.com/
```

只用于当前模型、发布横幅、重大变化检测，不作为新闻归档。

发现新模型或重大更新后，寻找对应中文官方正文。

优先类似：

```text
https://api-docs.deepseek.com/zh-cn/news/newsYYMMDD/
```

不要把：

```text
/api-docs.deepseek.com/news/
/zh-cn/news/
```

作为固定聚合入口。

## Qwen / 阿里通义千问

主入口：

```text
https://qwen.ai/blog/
```

中文补充：

```text
https://qwenlm.github.io/zh/blog/
```

中文模型更新确认：

```text
https://help.aliyun.com/zh/model-studio/newly-released-models
```

中文开源模型确认：

```text
https://modelscope.cn/organization/qwen
```

如果存在中文正文，优先中文正文。

## 智谱 / GLM

主入口：

```text
https://www.zhipuai.cn/zh/research
```

优先中文具体正文。

不以 z.ai 英文 Blog 为主扫描入口。

只有中文官方页面缺失时才补英文源。

## Moonshot AI / Kimi

主入口：

```text
https://www.kimi.com/blog/
```

如果跳转 kimi.ai，仍视为同一官方体系。

中文开放平台：

```text
https://platform.moonshot.cn/blog
```

模型、训练、架构、Agent 优先研究 Blog。

API / 平台更新使用开放平台 Blog。

## ByteDance Seed

主入口：

```text
https://seed.bytedance.com/zh/blog
```

优先中文正文。

## MiniMax

主入口：

```text
https://www.minimaxi.com/blog
```

新闻补充：

```text
https://www.minimaxi.com/news
```

模型发布：

```text
https://platform.minimaxi.com/docs/release-notes/models
```

技术分析优先 Blog。

模型/API 状态使用 Release Notes 补漏。

普通公司新闻只简短处理。

## 腾讯混元

主入口：

```text
https://hunyuan.tencent.com/research
```

新版正文可能位于：

```text
https://hy.tencent.com/research/
```

存在中文正文时优先中文。

禁止扫描：

```text
https://www.tencent.com/
```

等泛公司门户。

---

# 【4. Hugging Face】

Hugging Face 必须拆成三层。

不能把整个 huggingface.co 当 Tier 1 新闻源。

## 4.1 Hugging Face 官方 Blog

入口：

```text
https://huggingface.co/blog
```

每日扫描。

只有 Hugging Face 官方团队发布的文章自动视为 Tier 1。

Community Articles 不自动获得 Tier 1 身份。

重点关注：

- Transformers
- Diffusers
- TRL
- PEFT
- Datasets
- Tokenizers
- Accelerate
- safetensors
- Hugging Face kernels
- inference
- serving
- quantization
- Inference Providers
- Inference Endpoints
- compute infrastructure
- Hub infrastructure
- benchmark
- evaluation
- Hugging Face 自研模型
- dataset
- 开放研究

按内容路由：

```text
模型 / 训练 / 平台重大能力
→ 业界进展

Transformers / kernels / inference / runtime
→ 系统与编译器

benchmark / evaluation research
→ 科研候选

重要工程工具
→ GitHub / 系统候选
```

同一内容原则上只在最适合的位置详细展开一次。

## 4.2 Hugging Face Hub

只作为：

> **重大 Release Detector**

不进行全量模型扫描。

重点检测：

- Tier 1 模型团队新模型
- checkpoint
- 重要 dataset
- tokenizer
- config
- quantization artifact
- GGUF / safetensors 等重要 artifact
- Transformers 正式支持
- vLLM / SGLang 正式支持
- 重大 revision
- inference / training artifact
- 明显改变部署性或可复现性的变化

普通上传、fork、普通量化副本、wrapper 不得进入日报。

Hub 的 download、like、trending、discussions 仅作为 attention signal，不能单独证明质量。

## 4.3 Hugging Face Daily Papers

入口：

```text
https://huggingface.co/papers
```

每日作为 discovery / triage source。

排名、upvote、讨论只作为 attention signal，不得作为论文质量证据。

## Community Articles

不加入 Tier 1 全量 25h 扫描。

只作为：

- 定向补漏
- 高价值作者跟踪
- benchmark
- reproduction
- kernel
- compiler/runtime
- training recipe

等技术证据来源。

---

# 【5. 系统 / 编译器 / 技术源】

每日或高频关注：

- LLVM Blog
- MaskRay
- John Regehr
- Chris Lattner
- Modular Blog
- Linux
- GCC
- LLVM
- PyTorch
- Triton
- MLIR
- vLLM
- SGLang
- CUDA
- Compiler
- Runtime
- Kernel
- Serving
- Lilian Weng
- Sebastian Raschka
- Chip Huyen

Hugging Face 官方 Blog 中涉及：

- Transformers internals
- kernels
- quantization
- inference
- serving
- WebGPU
- accelerator backend
- compiler/runtime

也进入这一体系。

固定且能够稳定枚举新增条目的技术源同样使用：

```text
25h realtime scan
+
per-source last_seen cursor
```

---

# 【6. 业界进展】

Tier 1 官方源中与以下主题相关的真实新增均可纳入：

- AI 模型
- Research
- Product
- API
- Safety
- Engineering
- Ecosystem

包括：

```text
25h 内正常新增
+
cursor 检出的 missed-item backfill
```

不设最多 3 条限制。

不设国内外配额。

统一按重要性排序。

每条必须标注：

```text
重要性：高 / 中 / 低
```

## 高

包括：

- frontier / near-frontier 模型
- 训练 / 后训练
- 模型架构
- 显著推理效率
- Serving / Runtime
- 重大 Agent / Coding
- 关键开源
- 重要安全机制
- 显著多模态突破
- 改变技术判断的重要 API / 产品变化

允许详细分析，需要说明学习 / 工程价值。

## 中

包括：

- 明确能力增量
- 重要产品升级
- API / 工具
- 部署变化
- 平台变化
- 重要生态集成

约 2～4 句话。

## 低

包括：

- 小功能
- 商业扩展
- 区域扩展
- 普通合作
- 常规产品迭代

只写 1～2 句话。

不得进入“本期最值得关注”。

除与 AI 完全无关的公司事务外，不要仅因为重要性低而漏掉 Tier 1 官方相关新闻。

---

# 【7. 论文】

每日扫描：

- arXiv recent cs.AI
- arXiv recent cs.LG
- arXiv recent cs.CL
- Hugging Face Daily Papers
- OpenReview
- ACL Anthology
- 重要研究团队 project page

当天新论文主要做廉价 triage：

- title
- abstract
- author
- direction
- code
- project page

默认不当天深评。

只有“证据极强 + 问题重大 + Personal Utility 极高”才允许例外。

## 时间策略

### 0～7 天
默认观察。

### 7～30 天
重点判断。

### 30～90 天
主要成熟推荐区。

### >90 天
只有重大新证据或长期影响才重新进入。

## TTL

- 高潜力但缺证据：3～5 天
- 一般高潜力：5～10 天
- 成熟论文：7～14 天
- 低价值：30 天或归档

## 深评证据

检查：

- 问题重要性
- 方法增量
- 实验覆盖
- 强 baseline
- ablation
- 真实 evaluation / verifier
- reproduction assets
- training / inference cost
- limitations
- contamination / leakage

作者 / 机构仅作为辅助证据。

## 论文等级

```text
A
B
C
```

Evidence Maturity：

```text
M0 刚发布
M1 作者代码 / 数据 / checkpoint
M2 外部使用反馈
M3 独立验证
M4 生态影响
```

---

# 【8. GitHub】

每日优先使用：

- GitHub Explore
- GitHub Trending
- GitHub 官方推荐

作为 Discovery，不能直接作为质量证明。

论文官方代码是每日补充来源。

HF Hub 发现重要项目时，如果存在官方 GitHub，也进入候选。

## Watchlist

已知重要 repo 每日只检查：

- release
- major PR
- benchmark
- backend
- checkpoint
- 生态集成

主动定向补漏约每 7 天一次。

重点方向：

- LLM serving / inference
- compiler / MLIR / Triton / CUDA
- memory / long context
- evaluation
- coding agent / harness
- AI for science
- EDA / HPC
- developer infrastructure

## 老 repo 可以重新进入的条件

- major release
- 架构变化
- 性能突破
- 新 backend
- training code
- checkpoint
- benchmark 大改
- 生态集成
- 第三方 reproduction

repo 创建日期不是质量门槛。

## 重点项目必须具有真实技术实体

至少包含：

- core code
- demo
- example
- notebook
- eval
- benchmark
- dataset
- checkpoint
- Docker
- CLI
- API
- runnable path

只有 README、论文链接、code coming soon、无核心实现，不得重点推荐。

## GitHub 判断因素

- runnability
- idea value
- practical value
- maintenance
- community signal
- reproduction assets
- author / institution
- risk
- project momentum

star / fork 只能作为注意力信号。

等级：

```text
A
B
C
```

---

# 【9. Review State】

每次运行前读取：

```text
AI前沿日报/ReviewState.md
```

运行结束后更新。

正常日报绝不显示 Review State。

## ReviewState 保存内容

论文 / GitHub 只保存压缩状态：

- id / title / repo
- direction
- first_seen
- last_review
- next_review
- status
- quality
- maturity
- personal_value
- 主要证据
- 缺失证据
- known assets
- 上次 release / commit
- next_review_focus
- discovery_source

禁止保存：

- 网页全文
- 完整搜索日志
- 大段论文正文

## Source Cursor

在同一个 `ReviewState.md` 中增加：

```markdown
# Source Cursor
```

每个固定实时扫描源只保存：

```text
source
last_seen_item
last_seen_publish_time
last_successful_scan
```

Source Cursor 只用于：

- 增量扫描
- missed-item backfill
- 防止滑出 25h 后永久漏报

不得把 cursor 内容输出到日报。

## 复评规则

未到 `next_review` 且没有重大事件，不得重复深评。

允许提前触发：

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

## 状态规模

- Active Paper ≤ 30
- Active GitHub ≤ 20
- Long-term Watchlist ≤ 20
- Recent High-value Archive ≤ 20

低价值项目仅保留：

```text
ID
原因
reconsider_after
```

---

# 【10. 方向分桶】

论文 / GitHub 首先分桶，不要偏向 Agent。

1. 基础模型 / 预训练 / 后训练 / RLVR / DPO / 蒸馏
2. Agent / Tool Use / Coding / GUI / 长周期任务
3. RAG / Memory / Long Context / Knowledge / Retrieval
4. Safety / Alignment / Control / Evaluation / Red Team / Benchmark
5. Serving / Compiler / Kernel / Runtime / GPU / 低比特 / 加速
6. 多模态 / 语音 / 视频 / 世界模型
7. AI Scientist / AI for Science / 实验自动化
8. 工程系统 / 开发工具 / 软件工程 / EDA / HPC / 基础设施

不同方向不预设高低。

无高质量内容时不强行补位。

---

# 【11. 对用户价值与学习投资】

必须把 Intrinsic Quality 与 Personal Utility 分开。

用户长期关注：

- C++
- 系统
- 并发
- 编译器
- LLVM
- IR
- Runtime
- LLM Systems
- Serving
- EDA
- 硬件相关软件
- 工程基础设施

相关性不能提高论文或项目自身质量分。

## 重点条目必须回答

> 学完以后，用户能多理解什么？

以及：

> 学完以后，用户能多做什么？

## 建议投入只允许以下四档

### 深入学习
半天～2 天

### 立即学习
1～3 小时

### 了解即可
5～20 分钟

### 暂不投入

必要时指出：

- 最值得读的 section
- 最值得跑的 demo
- 最值得看的代码路径
- 可以跳过什么

如果无法回答：

> 为什么值得现在投入，而不是一个月以后再看？

则不得作为论文 / GitHub 重点推荐。

---

# 【12. 输出长度】

## 业界进展

不设硬上限。

- 高：可详细
- 中：简写
- 低：1～2 句话

## 系统与编译器

通常：

```text
0～3 条
```

重大更新可以超过。

## GitHub

通常：

```text
0～2 个
```

宁缺毋滥。

## 科研论文

通常：

```text
0～3 篇
```

宁缺毋滥。

真正达到“高质量 + 高 Personal Utility + 足够成熟证据”的论文 / GitHub，可以详细写：

- 问题
- 方法
- 质量证据
- 风险
- 对用户价值
- 建议怎么学

通常详细项目不超过 1～2 个。

---

# 【13. 本期最值得关注】

只选择：

```text
1～2 项
```

主要面向真正值得投入实际学习时间的技术内容。

允许连续多天重复同一个仍然最高 ROI 的项目或论文。

重复时只写：

- 状态变化
- 为什么仍值得优先
- 建议投入

不要重复完整介绍。

低重要性业界新闻不得进入本节。

优先能够形成长期技术判断框架的内容。

---

# 【14. 信息源与引用】

执行时必须使用最新公开信息。

优先顺序：

```text
官方原始正文
>
官方代码 / repo / model card
>
论文
>
可靠的一手工程资料
```

新闻正文中的关键事实必须尽可能链接原始官方来源。

论文链接原论文。

GitHub 链接官方 repo。

如果某个事实无法可靠确认：

- 不要猜
- 不要制造引用
- 不要用搜索结果摘要替代原始来源

---

# 【14A. Codex 额度重置与临时刷新监控】

该监控与每日日报扫描在同一次 Codex 任务中执行，但它是一个**独立提醒通道**：

> **监控结果绝不写入 `AI前沿日报/YYYY-MM-DD.md`，只在 Codex 当前任务窗口显示。**

目的：尽量提前发现 Codex 额度将在未来某个时间被临时重置、刷新、赠送、提高，或者 usage/rate limit 规则发生变化，从而允许用户在重置前合理安排剩余额度。

## 14A.1 重点监控事件

只关注与 Codex 使用额度直接相关的事件，例如：

- Codex usage limit / rate limit 临时调整
- weekly / 5-hour limit reset
- banked reset / full reset
- 临时赠送额外 Codex usage
- 某日或某时刻统一刷新额度
- 特定套餐 / 用户群体的临时额度提升
- Codex quota / credit / usage policy 的重要变化
- 官方明确说明“将在某日 reset / refresh / increase limits”的预告

普通 Codex 产品发布、模型更新、功能介绍，如果**不影响使用额度或重置规则**，不属于本监控。

## 14A.2 监控来源

优先级如下：

```text
OpenAI / Codex 官方公告或官方社交账号
>
OpenAI Help Center 中 Codex usage / limits / reset 相关页面
>
OpenAI Developer Community 中的相关消息（仅作为 discovery signal）
```

执行原则：

1. 优先寻找 OpenAI / Codex 官方原始公告。
2. 官方 X / 社交账号如果可以访问，可用于发现“今晚 reset”“明日提高 limits”等具有提前量的短期预告。
3. OpenAI Help Center 用于确认资格范围、reset 类型、生效时间、过期时间和具体规则。
4. OpenAI Developer Community 只能作为二级发现源；如果社区帖子声称存在 reset / limit 变化，必须尽可能反查官方公告、官方账号或 Help Center。
5. 不因为 Reddit、普通媒体、个人转述或无法核验的截图单独触发提醒。

推荐检索关键词包括但不限于：

```text
Codex reset
Codex usage limit
Codex rate limit
Codex limits reset
Codex full reset
Codex banked reset
Codex usage refresh
Codex quota
Codex extra usage
Codex limits increase
```

## 14A.3 增量与去重

在 `ReviewState.md` 中维护：

```text
Codex Usage Monitor State
- last_successful_scan
- last_seen_announcement
- last_seen_publish_time
- last_alerted_announcement
```

每次运行时：

1. 检查自 `last_successful_scan` 以来的新公告；
2. 同时查看当前最新相关官方公告，避免某次任务停跑后漏掉；
3. 已经通过 `last_alerted_announcement` 提示过的同一事件，不重复提示；
4. 如果同一事件后来出现**实质更新**，例如时间从“今晚”变为具体时间、资格范围变化、增加新的 reset 批次，则允许再次提示，并明确说明变化点；
5. 只有成功完成本轮监控后才更新 `last_successful_scan`；访问失败或无法确认最新状态时不要错误推进状态。

## 14A.4 什么情况下在 Codex 窗口提示

只有发现以下任一种情况时才提示：

### A. 提前预告

官方信息明确说明：

```text
未来某日 / 某时刻
将 reset / refresh / increase Codex usage limits
```

这是最高优先级，因为用户可能希望在重置前使用剩余额度。

### B. 刚刚发放但仍有操作价值

例如：

- Full reset 已到账但有过期时间；
- banked reset 已可领取 / 使用；
- 临时额度提升已经开始且只持续有限时间。

### C. 额度规则发生重要变化

例如：

- weekly reset 机制改变；
- limit 周期改变；
- 特定套餐额度明显调整；
- reset 使用后如何重新计算周期的规则改变。

如果只是没有新公告：

> **不要输出任何 Codex 额度监控占位内容。**

## 14A.5 Codex 窗口提示格式

发现新事件时，在日报文件写入和 `ReviewState.md` 更新全部完成后，只在 Codex 当前窗口追加：

```markdown
### Codex 额度提醒

- 事件：<一句话说明 reset / refresh / limit change>
- 时间：<官方给出的生效/重置时间；如需换算，同时给出北京时间>
- 影响：<哪些用户 / 套餐 / limit 受到影响>
- 建议：<例如“若计划使用剩余周额度，可考虑在重置前使用”>
- 官方来源：<原始官方链接>
```

要求：

- 简洁，通常 3～6 行即可；
- 明确区分“未来将发生”与“已经发生”；
- 时间尽量转换为 `Asia/Shanghai`；
- 不推测用户一定具有资格；如果官方只说 eligible users，必须写“符合资格的用户”；
- 没有可靠官方确认时不要制造提醒；
- **这一段绝不复制到 `YYYY-MM-DD.md` 日报正文。**

---

# 【15. 最终写文件】

完成全部扫描、判断、去重、补漏和复评之后：

将最终 Markdown 日报写入：

```text
AI前沿日报/YYYY-MM-DD.md
```

然后更新：

```text
AI前沿日报/ReviewState.md
```

包括：

```text
Paper / GitHub Review State
+
per-source Source Cursor
```

再次确认：

> 日报正文不得包含 Review State、Source Cursor、搜索过程、执行日志或 Codex 额度监控结果。

Codex 额度监控结果如果触发，只允许作为本次 Codex 任务完成后的窗口消息显示，绝不写入日报文件。

如果当天没有合格内容，仍然生成日报文件，并按固定结构填写：

```text
本窗口该部分无重要新增。
```
