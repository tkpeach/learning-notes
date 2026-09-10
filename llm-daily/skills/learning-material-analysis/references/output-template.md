# 输出模板

根据资料类型删减不适用部分，不要为了填满模板而编造内容。

## 面向用户的分析

```markdown
# [资料标题]

## 一句话判断

[用三至五句话说明核心价值、可信度、主要限制和是否值得跟进]

## 最值得记住的三点

1. [关键点]
2. [关键点]
3. [关键点]

## 资料讲了什么

- [事实或资料明确内容]

## 关键主张与证据

| 主张 | 证据 | 结论状态 | 可信度 |
|---|---|---|---|

## 与已有做法的差异

| 对象 | 差异 | 差异性质 | 证据状态 |
|---|---|---|---|

## 不确定点、疑问和反例

- [不确定点]
- [疑问]
- [潜在反例]

## 应用价值与限制

- 适用场景：
- 潜在价值：
- 使用前提：
- 主要限制：

## 下一步建议

- [检索 / 复现 / A/B 实验 / 加入工作流 / 暂不跟进]

## 关键讨论过程

### 争议一：[争议标题]

- 初始主张：
- 反方质疑：
- 关键证据：
- 回应或无法回应：
- 当前裁决：
- 对最终结论的影响：

### 争议二：[争议标题]

- 初始主张：
- 反方质疑：
- 关键证据：
- 回应或无法回应：
- 当前裁决：
- 对最终结论的影响：

## 执行状态

- 分析方式：真实独立 agent / 单 agent 独立轮次 / 单 agent 综合判断
- 说明：
```

## 知识卡片

```yaml
title: ""
source_type: paper | book | news | daily | prompt-practice | tutorial
source: ""
date: ""
summary: ""
claims:
  - text: ""
    status: confirmed-fact | source-conclusion | reasonable-inference | anecdotal | hypothesis | time-bound
    confidence: high | medium | low
    evidence: ""
    conditions: []
    counterexamples: []
related_topics: []
open_questions: []
next_action: ""
```

`yaml` 中的枚举值保持英文，便于脚本处理；说明文字使用简体中文。
