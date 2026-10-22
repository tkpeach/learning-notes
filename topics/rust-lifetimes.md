# Rust 生命周期

## 返回与接收者速查

| 目标 | 写法 | 数据关系 |
| --- | --- | --- |
| 借用 String 的内容 | s.as_str() 或 s.trim() | 返回 &str，仍依赖原数据 |
| 复制成独立 String | slice.to_owned() 或 string.clone() | 新拥有数据，可独立保存 |
| 从拥有参数转交数据 | fn take(s: String) -> String { s } | 移动所有权，不复制文本 |
| 只读查看对象 | fn view(&self) -> &str | 输出借用依赖 self |
| 不消耗对象生成快照 | fn snapshot(&self) -> String | 复制数据 |
| 消耗简单对象取走字段 | fn into_text(self) -> String | 移动字段所有权 |

输入是 String 不意味着 trim() 自动返回 String；返回类型也不会自动把 &str 转成拥有值。&mut self 是可变借用，不是获得对象所有权，不能直接移走 String 字段。

转换 API 的核心区别：ToOwned 可把 str 转 String、切片转 Vec；Clone 返回其 Self 类型的新值，不保证深复制；Copy 是允许简单位复制的标记，不提供 copied 方法。迭代器/Option 的 copied 和 cloned 则按 T: Copy / T: Clone 将 &T 转为 T。[类型、条件与示例](../learning-plans/rust-lifetimes/copy-clone-owned.md)。

[学习入口](../learning-plans/rust-lifetimes/README.md) · [学习过程](../learning-plans/rust-lifetimes/learning-log.md)

## 引用有效性

**引用被使用时，被引用的数据必须仍然有效。**

判断顺序：找数据所有者 → 找数据失效位置 → 找引用使用位置。不要只看引用变量声明在哪一层。

代表性案例：[E01-A](../learning-plans/rust-lifetimes/exercises/01-reference-validity/case-a.rs) 和 [E01-B](../learning-plans/rust-lifetimes/exercises/01-reference-validity/case-b.rs)。两例都在外层声明 view，在内层 String 上创建借用；A 在内层打印，B 在 String 销毁后打印。2026-10-20：学习者首次判断正确，导师编译验证 A 通过、B 报 E0597。

### 自测

把引用变量声明在外层，能否让它借用的内层 String 数据存活到外层？

<details>
<summary>查看答案</summary>

不能。引用不拥有 String 的数据，引用变量的声明位置不会延长被引用数据的存活时间；需要检查实际使用位置。

</details>

## 绑定的作用域与借用持续时间

**共享引用绑定仍在作用域内，不代表共享借用必须持续到块末尾。** 在本次直线代码中，后续是否还读取引用，决定共享借用是否需要跨过对所有者的修改。

- [C 原版](../learning-plans/rust-lifetimes/exercises/01-reference-validity/case-c.rs)：最后一次读取 view 后再调用 push_str，编译通过。
- [C 追加版](../learning-plans/rust-lifetimes/exercises/01-reference-validity/case-c-later-use.rs)：push_str 之后再次读取 view，共享借用与可变借用冲突，报 E0502。

这是基于控制流推断借用范围的非词法生命周期（NLL）的入门例子。2026-10-20 首次判断有误，已编译验证并讲解；理解修正仍待学习者复述与迁移检验。

### 自测

为什么删除追加版最后一行对 view 的打印，可以改变编译结果？

<details>
<summary>查看答案</summary>

删除后，view 的最后一次读取在 push_str 之前；共享借用不再需要跨过可变借用。不是 view 的绑定提前离开了作用域。

</details>

## 可修改绑定与可变借用

`let mut text = String::from("rust")` 创建可修改的所有者绑定，不创建借用。`&text` 创建共享借用，`&mut text` 创建可变借用。

本题中 push_str 临时取得可变借用且不返回借用，调用后借用结束；之后再创建 view 可以通过。格式化打印 text 只需共享借用，能与 view 的共享借用共存。[D 实际代码](../learning-plans/rust-lifetimes/exercises/01-reference-validity/case-d-mutate-first.rs) 已编译并运行通过。

首次迁移回答将 mut 所有者绑定误认为可变借用；已讲解，随后显式绑定/共享借用/可变借用三项分类全部答对。借用范围的独立迁移检验仍需继续。

后续小节结论随学习补充。

## 函数签名中的输入与输出关系

生命周期标注描述引用之间的有效性约束，不延长数据存活时间。E02 正确签名为 `fn keep_first<'a>(x: &'a str, note: &str) -> &'a str`：输出关联到 x，note 具有独立、未显式命名的生命周期。

首次尝试给 x 标注了 'a，但输出仍写 &str，实际报 E0106。存在两个输入引用时，仅给其中一个命名不会使省略的输出自动选择它，返回类型也需要表达关联。[尝试与补全代码](../learning-plans/rust-lifetimes/exercises/README.md#首次尝试与后续变式)。

补全版已编译运行通过；过度关联 note 的变式首次预测有误，实际报 E0597。调用者按签名中的关系检查，即使函数体只返回 x，也不能忽略同为 'a 的 note 对输出的约束。已反馈，待整组迁移检验，不据此标记已掌握。

## 编译期契约与运行时行为

生命周期关联是在类型中表达有效性约束；编译器根据使用位置、输入/输出关系和借用规则检查，不是运行时延长数据生命。<'a> 声明生命周期泛型参数，不会仅因生命周期不同就生成不同机器码实现；类型泛型 T 则可参与单态化。

本轮省略规则四项与 pair 的独立依赖标注正确，但对“两个输入同为 'a”仍误认为只看函数体返回来源，需要继续复习。[原理、约束示意与官方来源](../learning-plans/rust-lifetimes/compiler-mechanism.md)。

覆盖方向不是由名字 'a 决定。对直接共享引用，来源提供的有效性保证要覆盖接收处要求；调用参数、返回表达式、调用后使用会分别产生方向约束。`'src: 'out` 表示 src 覆盖 out，允许相等。[三个检查边界的展开](../learning-plans/rust-lifetimes/compiler-mechanism.md#8-覆盖方向从哪里来)。

识别来源与使用时，追踪“数据所有者 → 创建借用的表达式 → 引用经赋值、传参、返回或字段继续流动 → 后续读取/写入等使用”。来源与使用是相对当前检查边界的角色，不是变量的永久分类。哪些引用共享 'a 仍由声明与省略规则决定，不能把函数内所有被读取的引用都关联到输出。[完整追踪示例](../learning-plans/rust-lifetimes/compiler-mechanism.md#9-如何识别借用来源与使用)。

复习检查流程时按“定位借用/传参/赋值/返回/读取/修改或销毁 → 收集使用需求与类型约束 → 传播 → 检查借用是否跨过冲突或失效 → 关联产生、失效和后续使用三处诊断”。[手工模拟与检查点表](../learning-plans/rust-lifetimes/check-workflow.md)。

精确到规则：返回 x 降低为给返回槽赋值；对直接共享引用，检查 RHS 类型 <: LHS 类型。`&'a str <: &'b str` 根据生命周期协变生成 a: b。普通局部赋值也能触发同一关系，不是因为 x 是参数就天然要求 a 比 b 长。[IR、源码与本机验证](../learning-plans/rust-lifetimes/ir-to-constraints.md)。

Rust MIR 是 Mid-level IR，借用检查在机器码生成前利用显式控制流、移动/借用等语义。函数声明中的界限在实现内是条件，在调用点是义务。调用匹配可展开为实参 p: A、被调用者界限 A: B、输出 B: q，因而要求 p: q。[阶段与声明/调用拆解](../learning-plans/rust-lifetimes/ir-to-constraints.md#8-mir-是中层-ir为什么在这里检查)。

## 不限于函数输入输出

局部引用、结构体字段、方法与泛型约束都涉及生命周期有效性关系。Excerpt<'a> 中的 'a 描述字段借用，不要求结构体实例恰好活这么久。

方法 `fn via_self(&self) -> &str` 的输出默认关联到 self 借用；若字段本身是 &'a str，可以用 `fn data(&self) -> &'a str` 返回其携带的外部借用。后者可在包装结构体先销毁后继续使用，只要底层数据仍有效。两例已由导师编译验证；学习者应用能力待检验。[讲义 L04](../learning-plans/rust-lifetimes/lesson.md#l04生命周期关系不限于函数输入输出)。

## M03 已暴露的 API 设计误区

- 已能正确判断借用型结构体的输入依赖、note 过度关联和修改前后借用重叠。
- 方法省略输出关联 self；接收结果的变量只能提出使用需求，不能替底层数据提供有效性。
- 函数内部 format! 创建局部 String，返回其 as_str() 会悬空；关联输入 a 或加 static 都不修复数据来源。返回 String 则移动所有权，调用者获得新文本。
- 方法签名与所有权返回仍待纠错后迁移检验。[集中反馈与验证](../learning-plans/rust-lifetimes/exercises/08-application/attempts/validation.md)。

方法输出省略时关联本次 self 借用；显式写 &'data str 可以保留结构体字段携带的外部借用关系。impl<'data> 只声明类型实现使用的泛型参数，不给 impl 块或 self 设定存活时长。应区分外部数据参数 data 与方法借用参数 s；默认契约合法，但未必支持包装先销毁后的输出使用。

“保留字段已有保证”的代码表达是三步：字段 text: &'data str → self.text 表达式提供 &'data str → 返回类型明确要求 &'data str。读取包装需要 &self，但复制出的共享引用不借用包装字段的存储位置；&self.text 才是在新建对字段本身的借用。
