# LLVM 普通 issue 的新贡献者入口：已合入 PR 核查

核查日期：2026-10-14。下文日历日期、时间均为北京时间；合入耗时按 API 时间戳差值计算。目标是验证：不抢 good first issue，是否仍可用普通后端 issue 建立直接经历；以及此前 #231385、#227352、#226919 的推荐是否有实际贡献路径。

## 结论及证据边界

有新贡献者直接修普通 issue 并合入的公开先例，既有处理别人报告的 bug，也有自己报告后直接提交 PR。LLVM 没有规定新人只能做 good first issue，也没有要求小型 bug fix 必须先获得 assignee 才能提交。

但这里能确认的是“刚开始向 LLVM 投稿/首次 LLVM PR”，不是“此前完全没有编译器知识”。公开 PR 无法完整证明作者工作背景。机器人说 first PR 也不能单独当作事实：本轮作者历史搜索发现，有人已经提交多项 PR，却仍在后续 PR 得到同类欢迎留言。

本轮定向搜索已合入 PR，检查了 6 个样本的 merge 时间、正文、review、文件修改和关联 issue，再检查 4 位作者按创建时间排序的最早 PR。下列 3 个普通后端样本符合新贡献阶段证据；另列 1 个自述新人的前端样本作沟通成本反例。不是随机抽样，不估算新人成功率、平均合入时间或个人合入概率。

来源：[LLVM 贡献指南](https://llvm.org/docs/Contributing.html)、[review 政策](https://llvm.org/docs/CodeReview.html)。贡献指南推荐 GFI 作为熟悉代码的入口，但同时描述普通 bug 修复流程：留言告知工作、主线复现、孤立修改与测试、提交 PR。重大设计、LangRef/新 intrinsic 等可能需要 RFC；普通局部 bug fix 不等同此类工作。

## 已合入的普通后端样本

| PR / issue | 新贡献者证据与进入方式 | 实现与测试 | review/合入 |
| --- | --- | --- | --- |
| [#225886](https://github.com/llvm/llvm-project/pull/225886) → [#224127](https://github.com/llvm/llvm-project/issues/224127) | 作者 agourakis82 在评论自述首次参与贡献；可见投稿历史从 2026-09-22 开始，此 PR 于 09-24 提交，是第 9 个可见 PR，而不是第一个。处理 anun333 报告的普通 issue；公开 issue 没有先分派给作者的记录，也未发现前置认领评论 | SelectionDAG vector legalizer 对多结果节点使用错误的 result index/type。实现文件 +8/-5，测试文件 +129/-15 | arsenm/topperc review，要求取 `Unrolled.getValue(ResNo)`、简化提交说明、格式调整。9 月 24 日提交，9 月 26 日合入，约 2.17 天 |
| [#228839](https://github.com/llvm/llvm-project/pull/228839) → [#228828](https://github.com/llvm/llvm-project/issues/228828) | 作者 waroad 的最早可见 LLVM PR，随后数秒内又提交两项其他 PR。作者自己报告 issue 后直接提交，不是领取别人已在做的任务；不能把此例等同“初学者接别人 issue” | DAG combine 在 store address 依赖原节点时制造环；实现 +6/-0，测试 +100/-0 | RKSimon 明确 APPROVED；10 月 4 日提交，10 月 6 日合入，约 1.38 天 |
| [#220743](https://github.com/llvm/llvm-project/pull/220743) → [#220542](https://github.com/llvm/llvm-project/issues/220542) | 作者 kodlan 可见投稿从 9 月 1 日开始，此 PR 是其第 4 个，处于第 3 天。处理别人报告的普通 issue；未见前置指派/认领请求 | shift+mask 与 rotate 的等价条件对非普通整数宽度错误。3 个实现/头文件合计 +13/-8，测试 +72 | review 追问 rotate 是否 profitable，作者进一步限定 target hook 对合法 scalar type 的偏好。9 月 3 日提交，9 月 13 日合入，约 10.59 天，期间有作者暂未跟进，不全是维护者等待 |

以上对应 issue 的当前标签和可见标签变更历史未出现 good first issue。读取的 issue 评论与事件没有需要先获得维护者“批准认领”才能提交 PR 的记录。严格地说，证据是“直接开始并提交 PR 获得 review”，不是每例都先留言认领。

**这些先例说明：普通 issue 不是保留给资深维护者的任务池。一个明确 bug 的局部修复加有效测试，是现实入口。**

也说明“改动小”与“验证简单”不同。三个后端样本的主要测试工作比实现多；涉及类型/结果编号、依赖关系或等价条件。不能只按修改几行评价难度。

### 具体 review 中的学习成本

#225886 的作者最初处理了 type/result 的一部分问题，review 明确要求结果也必须按 ResNo 取，说明“改错类型”与“取错结果”需要一起理解。适合新贡献阶段，仍要求作者修正具体语义。

#220743 的初始修复证明了正确性条件，但暴露新的非标准宽度 rotate 选择，review 继续要求判断 profitability。修复不能以“理论等价”取代目标成本与合法化判断。

#228839 没有额外行内 review 评论，只有明确 approval。不能从它推断所有同类问题都有快速 review；其最小依赖检查及大段回归已经足够 reviewer 判断，是本例的具体条件。

## 小 patch 仍可能需要长时间沟通

[PR #181482](https://github.com/llvm/llvm-project/pull/181482) 对应普通 [issue #181298](https://github.com/llvm/llvm-project/issues/181298)。作者 kevinlzh1108 在讨论中明确自述新到 LLVM。原方案修改 isWeakImported 遍历 redeclaration chain；最终合入位置转为 ASTReaderDecl 的属性合并逻辑，配套 Modules 测试。最终只有 2 个文件、实现 +6/-5、测试 +23/-5，但从 2026-02-14 到 05-07 约 81.56 天。

review 中需要找更了解 ObjC/Apple 场景的 reviewer、调整修复层级与测试，最终 vsapsai approve 并代为合入。作者几次 ping，说明“能合入”不等于“沟通成本低”。该例属于前端，列为成本反例，不拿来证明机器后端技术匹配。

## 不用作普通 issue 初学者先例的样本

- [#228100](https://github.com/llvm/llvm-project/pull/228100) 确实已合入、局部后端修复且有新人欢迎，但对应 #227648 当时已经标 GFI。它可用于学习 MIR/debugify 回归，不作为“普通 issue 无标签入口”证据。
- [#218019](https://github.com/llvm/llvm-project/pull/218019) 也是普通 issue 合入，但作者在提交前已有多个 PR，并有更早提交的其他后端工作。它能说明早期贡献阶段的路径，不能称作者第一个 PR。它的 review 要求恢复已有测试检查、增加实际 CodeGen 检查、重置 patch 的类型限制与 rebase；不当作无成本模板。

## 为什么 GFI 抢手而普通 issue 看起来没人认领

下面是结合样本的判断，不是统计推断：

1. GFI 为新人提供预筛选/可见入口，普通 issue 没有这个信号。普通 issue 的成本可能来自复现、旧版本变化、合法性或测试，而不是写代码。
2. 无 assignee 不代表无人做。本轮普通样本里就有直接提交 PR、而不先把自己挂到 issue 上的方式。关联 PR、正文里的实现意向与评论应一起检查。
3. 某些 issue 虽零评论，作者自己已有 patch；此前 #231378 就属于这类，因此已经排除。
4. 维护者不会给每个简单普通 bug 补 GFI 标签。有明确定位且已有 reproducer 的问题，仍可能没有标签；需要自己承担筛选与背景学习。
5. 仅看已合入成功样本会高估可行性。它们证明“可以进入”，不能证明一个新人提交就会合入；作者还提交了多项开放/关闭 PR，不能忽略未完成工作。

## 三个推荐 issue 的重新判断

2026-10-14 北京时间 11:26 刷新 issue 页面：三个均 OPEN、无指派、0 评论、无页面关联 PR。11:31 再查同仓库 PR 中的 issue 编号，均 0 结果。没有给用户发布认领或 PR。编号零结果不能排除未公开工作及未提编号的 PR。

### #231385：适合作为第一个实现候选，但还不是“已验证可直接合入”

[Issue](https://github.com/llvm/llvm-project/issues/231385)。报告的边界溢出发生在 SelectionDAGBuilder 的 memcmp/bcmp lowering。本次之前读取的主线源码与描述相符，尚未构建当前 LLVM 运行复现。

它与 #220743 的贡献形态相近：已经存在的后端变换，其合法性条件在特殊整数范围下不成立。修正边界条件并保留正常优化，加边界正反测试，有上述已合入先例支撑。

这里“可以做和提 PR”指：社区没有新人身份障碍，技术范围初步局部，问题来源和回归可以明确，值得投入主线复现；不指维护者预先接受方案。先用 IR 证明确实从大长度误生成短比较，再证明小长度正常优化没有被绕过。不能只扩大一个变量类型后便默认所有溢出、截断及 target 回调都正确。

建议优先级仍为第一。实际实现前刷新占用，固定 revision、建立失败回归；正确修复后可以提交普通 bug-fix PR，不必等正式分派。

### #227352：合理的第二候选，属于后端错误输入处理

[Issue](https://github.com/llvm/llvm-project/issues/227352)。X86 inline asm 的 A 约束接受 vector，随后在 operand lowering 崩溃；此前读取的主线 case A 与报告相符，尚未运行复现。

局部 target 约束检查加测试符合普通 bug-fix 范围。该任务能学 MVT、register class、inline-asm input lowering，与你的岗位方向相关。比后端成本策略更容易定义正确/错误结果。

但诊断位置有 target hook 与通用复制路径两种可能，不能仅关闭 assertion 或拒绝合法整数类型。验收应覆盖 vector 的不合法输入、合法整数输入，必要时兼顾 32/64-bit 和读写约束。简历写 target lowering/诊断正确性，不写性能提升或寄存器分配优化。

仍值得实现与提交；若当前主线已不复现则调整或放弃，不把昨天的静态检查当作今天的运行证据。

### #226919：降为第二阶段，不作为新手第一项的可靠推荐

[Issue](https://github.com/llvm/llvm-project/issues/226919)。PDEP/PEXT 的默认软件展开成本，正文只给短提示。与 #220743 review 对 profitability 的追问相呼应：成本问题即使 patch 小，正确估计与评审解释可能很重。

默认 expansion、native instruction override、scalar/vector、bit width、cost kind 的覆盖都需要理解。最初建议中“可以切入”的口径过宽；它目前只是值得研究的后续方向，不应与前两项一样视为范围已清楚的小修复。

在源码梳理后，先提出有依据的范围与预期成本测试，再与维护者短讨论；这项沟通是为了定义验收，不是因为新人被禁止做普通 issue。对于用户“不希望沟通占过多精力”的条件，先后置。

## 对用户的实施门槛与简历目标

建议只启动 #231385 一项：

1. 固定主线 revision 和 assertions build，用最小 IR 本地复现；做出修改前失败的 regression。
2. 确认原始调用、SelectionDAG lowering 和 target code 的行为链路，明确边界与正常情况。
3. 明确修复位置与不改变的既有正常路径；补正反测试，跑相关 CodeGen 测试。
4. 在 issue 留言告知开始工作和具体范围；局部 bug fix 无需以得到 assignee 为前提，也不需要问“是否允许新人做”。发布消息仍须用户明确授权。
5. PR 解释根因、为什么该位置正确、测试及相关 issue，遵循 LLVM 政策；不能把工作理解/验证交给 reviewer。

第一项完成后，在同模块做一项生成代码优化，才能从“会修一个边界 bug”走向可讲清楚的后端经历。上述成功样本都只作学习参考，不能写成用户自己的贡献。

最终判断：**普通 LLVM issue 是现实入口；#231385、#227352 可以作为复现→修复→PR 的候选，#226919 后置。前两项的建议有合入形态先例，但尚无用户本地复现与 patch 证据，不能承诺合入。**
