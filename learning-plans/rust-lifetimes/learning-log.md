# Rust 生命周期学习记录

[学习入口](README.md) · [讲义](lesson.md) · [练习](exercises/README.md)

## 第 1 次学习 · 2026-10-20

截至 2026-10-21：M04-R 综合回访两项判断正确，已编译验证；正在回答 to_owned、clone 与 copied 的 API 追问。转换 API 和独立方法实现仍需巩固。实际学习耗时尚未记录。

### 环境与材料

- 已确认本机 rustc 1.98.0、cargo 1.98.0 可用。
- 已建立计划、L01 讲义和 E01 两个待判断案例。
- A/B、C 及 C 末尾追加读取版均已在学习者回答后编译验证，详见下方。

### L01 / E01：引用有效性

- 学习者原始判断：“1. A可以，B不可以；2. 字符串text拥有，到text作用域结束；3. A有效，B无效”。
- 解释：正确识别 text 是数据所有者，并根据打印位置判断数据是否仍有效。
- 代码：[A](exercises/01-reference-validity/case-a.rs)、[B](exercises/01-reference-validity/case-b.rs)。
- 实际编译结果：导师用 rustc 1.98.0、Rust 2024 edition 验证。A 编译退出码 0，运行退出码 0，输出 rust；B 编译退出码 1，报告 E0597，诊断依次指出借用来源、text 在内层块末尾销毁、外层 println 后续使用借用。构建产物位于临时目录并已清理。
- 反馈与修正：A/B 均判断正确，无需修正。这里说的是 String 拥有的字符串数据，不是说所有字符串数据都在局部块末尾失效。
- 已形成结论：引用使用时，被引用的数据必须仍然有效。

### E01-C：借用持续时间误区与修正

- 学习者原始判断：“1. 不能通过，view是个借用，不能后续使用text作为可变借用使用；2. 不会改变”。
- 发现的误区：把共享引用绑定仍处于作用域内，等同于共享借用必须持续到块末尾。
- 导师实际验证：原版 C 编译退出码 0，运行退出码 0，依次输出 rust、rust!；[末尾追加读取版](exercises/01-reference-validity/case-c-later-use.rs) 编译退出码 1，报 E0502。诊断指出创建共享借用、push_str 可变借用、末尾再次读取共享引用三处。
- 修正解释：原版最后一次读取 view 在 push_str 之前，共享借用无需跨过修改；追加版要求共享借用跨过修改，产生冲突。引用绑定的作用域和借用需要持续的范围不同。
- 下一步检查：用自己的话解释为什么删除最后一次读取会改变合法性；判断将追加版中的 push_str 移到创建 view 之前是否可行。
- 掌握情况：已给出反馈，尚未得到学习者重新解释或迁移回答，不能标为掌握。

### 下次起点

阅读 copy-clone-owned.md，区分 ToOwned、Clone、Copy 与迭代器/Option 的 copied/cloned。M04-R 已答对，不重复布置；后续按需求巩固 API 与方法实现，不自动扩展高级生命周期主题。

### E01-D：可修改绑定与可变借用

- 学习者原始判断：“不能通过，共享作用从view定义开始到最后一个println结束，可变借用从text定义开始到print text结束，两者有交叉范围”。
- 正确部分：view 的共享借用需要供最后一次 println 使用。
- 发现的误区：将 let mut text 视为从定义开始持续存在的可变借用；将打印 text 视为可变借用的结束位置。
- [实际代码](exercises/01-reference-validity/case-d-mutate-first.rs)：导师用 rustc 1.98.0、Rust 2024 edition 编译，退出码 0；运行退出码 0，输出三行 rust!。临时构建产物已清理。
- 修正解释：let mut text 创建可修改的所有者绑定，不创建引用。push_str 为调用临时取得可变借用，调用结束后该借用结束；之后 as_str 创建共享借用，不与其重叠。println 格式化 text 只需共享借用，多个共享借用可以共存。
- 教学调整：先区分所有者绑定、共享借用、可变借用，再回到借用有效范围。尚未确认学习者掌握，不推进 L02。
- 待回答：let mut text、let view = &text、let edit = &mut text，哪些语句真正创建借用？作为三个独立场景判断。

### E01-E：基础分类反馈

- 学习者原始回答：“1 创建所有者，没有借用；2 创建共享借用；3 创建可变借用”。
- 反馈：三项分类均正确。补充确认：第 1 行的 mut 表示允许修改该绑定持有的值，本身不创建引用。
- 掌握证据：已能正确分类显式所有者绑定与两类借用。尚未独立重做 C/D，因此不据此宣称已掌握借用范围判断。

### L02 / E02：函数的生命周期关系

- 已提供 longest 的签名和关系解释，强调标注不延长值的生命，也不要求输入值同时创建或销毁。
- 迁移练习：给只返回第一个参数的函数补充生命周期，判断备注参数是否应约束返回值。
- 学习者首次提交：`fn keep_first<'a>(x: &'a str, note: &str) -> &str`。
- 正确部分：为 x 声明 'a，note 未与之关联；遗漏部分：输出 &str 未标为 &'a str，签名未表达返回值来自 x。
- [原始签名尝试](exercises/02-return-dependency/attempt-01.rs)：导师补上题目原函数体及调用后编译，退出码 1，报 E0106；诊断指出返回类型未说明借用自 x 还是 note。
- [导师补全版](exercises/02-return-dependency/fixed.rs)：仅将返回类型改为 &'a str，编译退出码 0，运行退出码 0，依次输出“只是一条备注”和 rust。内层 note 已销毁时仍可在外层读取结果。rustc 1.98.0、Rust 2024 edition；临时构建产物已清理。
- 已反馈：返回值也须标出 'a 才能连接输入与输出。note 未命名不等于没有生命周期。
- 下一步：将 note 也关联到 'a，预测相同调用是否还能通过，检验签名约束的理解；尚未作答或编译。

### E02 变式与教学方式调整

- 学习者原始判断：“能够通过；不会约束范围，因为没有返回note”。
- 实际验证：[过度关联版](exercises/02-return-dependency/overconstrained.rs) 使用 rustc 1.98.0、Rust 2024 edition 编译，退出码 1，报 E0597；note 在内层块末尾销毁，返回引用在外层继续使用。临时构建产物已清理。
- 误区：根据函数体只返回 x，忽略签名中 note 与输出的关联。已补充“调用者按签名检查，实现单独满足契约”的解释。
- 学习者明确反馈：学习内容不详细，'a 缺少使用方式和原理；每次内容太少、反复等待回复导致效率低。
- 调整：讲义补齐完整 M02 模块（生命周期参数原理、常见写法、签名契约、省略规则、局部引用与 static 边界）；练习改为一组 3 题一次提交、集中验证反馈。同步更新继续学习提示词。
- 当前不宣称误区已消除；等待 M02 的新条件判断与独立标注。

### M02 整组提交与机制追问

- M02-1 原始回答：“都能通过，返回值生命周期与outsize关联；打印移动后都能通过，返回值生命周期与outsize关联能够引用到”。
- 反馈：A 外层通过；B 外层不通过，不能忽略 inside 与输出同为 'a 的签名约束。打印移入内层时 A/B 都通过，但 B 仍受两个输入共同约束，不能解释为只关联 outside。
- M02-2 原始回答：“a不需要，关联s；b需要；c不需要，返回不是引用；d不需要，关联self”。四项正确。
- M02-3 原始签名：`fn pair<'a, 'b>(x: &‘a str, y: &'b str) -> (&'a str, &'b str)`；解释：“不会改变销毁时间，仅是关联生命周期”。依赖关系与解释正确；x 的标注使用了弯引号，保存代码时改为 ASCII 单引号。
- 导师实际验证：exercises/03-module-check/ 下 A/B × 内外打印四种源码分别编译：a-outer、a-inner、b-inner 退出码 0；b-outer 退出码 1，报 E0597。pair-and-elision.rs 将 pair 与省略规则示例补为完整可调用实现，编译退出码 0，运行断言退出码 0。环境 rustc 1.98.0、Rust 2024 edition；临时产物已清理。
- 学习者追问：生命周期关联究竟是什么操作，编译器/运行时分别做什么；<'a> 为什么需要声明，是否像模板、是否生成多份函数实现。
- 已基于 Rust Reference 与 Rust Compiler Development Guide 补充 compiler-mechanism.md，区分类型契约、region 约束求解、擦除以及类型泛型单态化；没有把引用生命周期解释为运行时延寿操作。
- 掌握判断：省略规则与独立输出依赖有正确作答证据；共享参数的调用点约束仍有反复误判，不标为已掌握。

### 追问：生命周期关系是否只适用于函数输入输出

- 学习者问题：根据“既能由两个输入支持，又足以覆盖返回引用的使用”，询问生命周期关联是否仅用于函数输入输出。
- 教学表述修正：之前的句子是具体函数例子的解释，不能作为生命周期适用范围的定义。
- 补充内容：局部引用的推断、结构体字段借用、多个字段的独立参数、方法返回对 self 的借用与返回字段携带外部借用的区别、'long: 'short 及 T: 'a 的含义。
- 导师验证：exercises/04-struct-borrow/data-outlives-wrapper.rs 编译退出码 0、运行断言退出码 0，输出 rust；self-borrow-escape.rs 编译退出码 1，报 E0597，excerpt 失效后仍使用关联到 self 的返回引用。rustc 1.98.0、Rust 2024 edition，临时构建产物已清理。
- 两个例子是导师讲解和演示，不算学习者独立完成练习。L04 尚待应用检验。

### 追问：不同位置的 'a 如何确定覆盖方向

- 学习者问题：不同位置的 'a，编译器如何确定谁需要被 a 覆盖、谁需要覆盖 a。
- 补充解释：参数名没有方向；方向由来源类型满足目标类型的要求、引用使用位置及显式 outlives 约束产生。分别展开调用时传参、函数体返回、调用后使用三个检查边界，并说明参数作用域与变型的适用边界。
- 导师演示：exercises/05-constraint-direction/missing-bound.rs 返回 &'out str 却只提供 &'src str，未声明关系，编译退出码 1，提示添加 'src: 'out；with-bound.rs 加上约束后编译退出码 0、运行断言退出码 0。rustc 1.98.0、Rust 2024 edition，临时产物已清理。
- 本次集中解释机制，未要求逐题回复，不将演示结果记作学习者掌握证据。

### 追问：如何识别 'a 的借用来源与实际使用

- 学习者问题：如何判断哪些是 'a 的借用来源，哪些是实际使用。
- 补充说明：'a 是有效性参数而非唯一来源标签；区分最初的数据所有者、当前提供引用的表达式和接收/使用位置。借用来源与使用不是互斥的变量分类，同一个引用可在一次检查中被使用、在下一次检查中成为提供者。
- 新增完整 relay 示例逐行追踪，说明方法隐式借用、实参、尾表达式、保存返回值与打印的角色；note 即使被读取，也不会在未声明关系时自动关联输出的 'a。
- 解释已记入 compiler-mechanism.md 第 9 节，基于已验证 E02 案例展开；未把重命名教学示例宣称为新的独立运行记录。

### 追问：识别检查点与检查内容的完整流程

- 学习者请求：说明编译器如何实现检查，给出识别检查点与检查内容的流程。
- 新增 check-workflow.md：从 MIR/控制流、初始化与移动、借用记录、使用需求与类型约束，到 region 传播、通用参数关系检查、访问/失效冲突检查与诊断。
- 用已验证的 M02 B 外层打印案例标记 P1–P6，列出 Rx: Rc、Ry: Rc、Rc: Rr、P5 ∈ Rr，并推导后续使用如何要求 inside 的借用跨过销毁点。
- 区分 region 需求传播与在销毁点报告局部借用失效，避免暗示所有错误都是求解器无法选出某个长度。补充概念固定点与实际 SCC/DAG 实现的对应关系。
- 本次复用已有实验结果；没有声称 P/R 编号来自真实 MIR dump，也未声明已阅读本机编译器对应版本源码。

### 精确追问：a: b 如何从语法/IR 中产生

- 学习者以 wrong 为例追问：a: b 是否依赖 x 是函数参数；语法位置有无关系；约束从程序/IR 的哪条规则产生。
- 前面教学缺口：说“来源覆盖要求”仍未展开类型关系规则，容易被理解为按参数/返回位置套规则。
- 新增 ir-to-constraints.md：尾表达式 → 返回槽赋值 → RHS <: LHS → &'a str <: &'b str → 生命周期协变 → a: b。区分约束生成与通用参数契约验证，区分语义操作位置与类型结构中的变型。
- 核对 Rust 1.98.0 官方源码 type_check/mod.rs 的 visit_statement/Assign 分支，确有取 rv_ty/place_ty 后调用 sub_types(rv_ty, place_ty, ...)；同时注明 nightly region 关系实现文档可能非同一版本。
- 新实验：exercises/06-type-relation/local-assignment.rs 普通局部引用赋值编译退出码 1，提示 a: b；forward-with-bound.rs 带约束以 lib 形式 emit MIR 成功，保存文本 forward-with-bound.mir，实际含 _0 = copy _1; return。普通 emit 未显示命名 region，未将手工标注的生命周期伪装成真实 dump。
- 讲解不再让学习者连续猜题；当前仍按提问补齐机制理解，尚未记录新的独立迁移证据。

### 追问：MIR 所在阶段与声明/调用约束的生成

- 学习者问题：MIR 是否 Machine IR，为什么这么晚检查；函数声明和调用怎样生成生命周期关系。
- 补充 ir-to-constraints.md 第 8、9 节：MIR 是 Mid-level IR；借用检查在机器码生成前，使用简化语法、显式控制流和移动/销毁语义，部分名称/省略问题更早检查。
- 区分声明提供的参数、输入/输出类型及显式/隐含界限；实现用声明条件证明操作产生的要求；调用将被调用者的界限实例化为义务。
- 完整推导：forward 的 a/b 在一次调用中实例化为 A/B，实参匹配生成 p: A，显式界限实例化为 A: B，输出匹配生成 B: q，合起来需要 p: q。
- 新实验：07-call-constraints/caller-missing-bound.rs 以 lib 形式编译退出码 1，诊断提示 p: q；caller-with-bound.rs 添加 p: q 后 emit MIR 退出码 0，保留小型文本 MIR，其中有对 forward 的调用及返回目的地 _0。环境 rustc 1.98.0、Rust 2024 edition；失败构建临时产物已清理。
- 以上均为导师原理演示，不作为学习者已掌握新机制的证据。

### 继续学习：M03 应用模块

- 学习者反馈：“大概理解了，继续学习”。记录为主观理解反馈，不替代新条件下的应用证据。
- 已补充完整模块：借用/拥有的数据结构选择、构造函数与 Self、关联 self 或数据的两类方法、to_owned 快照、动态文本返回 String、字面量 static、结构体借用下的 NLL。
- 已提供 M03 四道整组练习，其中 M03-1 回访 note 过度关联，M03-4 回访 mut 绑定与借用使用范围。题目未提前执行或填答案。
- 导师讲义演示 exercises/08-application/lesson-demo.rs：rustc 1.98.0、Rust 2024 edition 编译退出码 0，运行断言退出码 0，输出 snapshot=rust, default=default；临时产物已清理。演示中先结束视图包装、再读外部借用；之后销毁 owner、再读独立 String 快照。
- 当前等待学习者集中提交，不因演示通过而标注 M03 已完成。

### M03 整组回答与集中反馈

- M03-1 原始回答：A 通过、B 不通过，B 的 view.text 引用已结束生命周期的 owner；note 关联到同一个 a 后 A 不通过，因为 note 生命周期需要覆盖返回值生命周期。判断与原因正确，说明此前共同参数约束已能应用到新结构体例子。
- M03-2 原始回答：`fn raw(&self) -> &str { text }`；字段为 String 时“返回切片关联到接受返回值的变量”。两处需要修正：字段访问应为 self.text；省略输出关联 self，不能支持包装先销毁后的使用，应显式返回 &'a str。字段为 String 时，输出由 &self 借用支持，不由接收变量提供有效性；接收方使用只能提出要求，不能延长数据存活。
- M03-3 原始提交：`fn greeting<'a>(name: &'a str) -> &'a str { let message = format!("Hello, {name}!"); message.as_str() }`；解释 static 无法修改实际生命周期。static 的解释正确，但命名 a 也不能让局部 message 的数据活过函数返回。应返回拥有的 String，将新生成数据的所有权交给调用者。
- M03-4 原始回答：原版通过，追加打印后失败；push_str 的可变借用与后续 view.text 所需的共享借用重叠。判断正确；补充精确位置为 push_str 调用产生可变借用，mut 绑定本身不产生借用。
- 完整诊断与运行结果保存于 exercises/08-application/attempts/validation.md。导师在 rustc 1.98.0、Rust 2024 edition 下验证 11 个独立版本：01-a、02-external-fixed、02-owned-accessor、03-owned-fixed、04-original 编译运行通过；01-b/01-a-constrained/02-self-contract 报 E0597；02-original 报 E0425；03-original 报 E0515；04-later-use 报 E0502。临时产物已清理。
- 对原始 raw 先记录确切 E0425，再以 self.text 的版本隔离省略输出契约问题，不把拼写错误与生命周期错误混为一谈。函数体/main 为导师按答案补齐，不声称学习者独立写了所有工程。
- 下一步用 M03-R 三种返回方式做整组迁移，重点确认所有权转移与借用返回的区别。

### 追问：self 输出省略规则与 impl 生命周期参数

- 学习者问题：方法有 self 时输出不是默认关联 self 吗，为什么还需要给 impl 设置生命周期。
- 反馈：省略规则理解正确。显式返回 &'data str 表达不同契约；默认关联 self 不是错误，只是不满足本题允许包装先销毁的要求。
- 补充两参数展开：impl 的 data 表示 View 字段携带的外部借用，方法的 s 表示本次 self 借用；对比返回 &'s str 与 &'data str。impl<data> 声明类型实现使用的泛型参数，不是给 impl 块或 self 增加数据存活期。
- 说明命名参数仅在需要引用该关系时使用；普通默认方法可写 impl View<'_>，并强调结构体定义与 impl 的参数作用域各自独立。
- 本次复用已验证的 self-contract/external-fixed 对比解释，没有新增运行实验，也没有将尚未完成的 M03-R 标为已答。

### 追问：如何用代码表达保留字段的外部借用

- 学习者询问“返回值保留字段已有的外部借用关系”具体如何由代码表达。
- 新增显式双参数展开及局部类型标注：字段 text: &'data str，方法借用 &'s self，输出 &'data str，局部 result: &'data str = self.text。逐步展示字段表达式类型与目标类型相同，不是用短 self 借用凭空产生长 data 保证。
- 对比默认方法仍从相同字段读取，但输出契约缩短到 s；区分 self.text（取出共享引用）与 &self.text（借用引用字段本身）。未新增独立运行实验，相关方法对比已有验证。

### 继续学习：M04 收尾模块

- 学习者表示“好的，继续学习”，未提交 M03-R。将其合并入新整组练习，避免丢失尚待确认的所有权返回误区。
- 新讲义覆盖：借用参数与拥有参数、返回拥有值的 move、块结果移出局部绑定、动态生成文本独立于输入、临时 String 所有者、self 与 &self 的能力区别。
- 已验证导师讲义演示 exercises/09-ownership-transfer/lesson-demo.rs，rustc 1.98.0、Rust 2024 edition 编译与运行退出码 0，输出 rust; block result; Hello, Rust!，临时构建产物已清理。
- 综合题包含三个返回方式判断、临时值借用修复、Document 的查看/快照/消耗 API。尚未作答或编译，不将讲义演示当作学习者验收结果。

## 第 2 次学习 · 2026-10-21

### M04 整组提交

- 第 1 题原始回答：A 通过，输入实参拥有、输出借用传递；B 不通过，所有权进入 s，但输出借用，修复可返回 String；C 通过，所有权进入 s 后返回转移。核心判断正确。补充：A 的底层数据仍由调用者一侧持有，函数仅接收引用；B 是函数结束时局部 s 被销毁，不是“所有权本身消失”。
- 第 2 题原判断：不能通过，“String所有权不满足”。方向正确，精确原因为临时 String 在初始化语句结束时销毁，而 result 在下一条语句读取。实际 E0716。
- 保留借用的提交：先 let ori = String::from("  rust  ")，再 label(ori.as_str())，然后打印；正确，编译运行输出 rust。
- 独立文本的原提交：`fn label(input: String) -> String { input.trim() }`，main 将 String 按值传入。trim 返回 &str，函数要求 String，报 E0308；接收拥有值不会自动把每个方法结果变成拥有值。导师修复为 input.trim().to_owned()，输出独立 String，运行输出 rust。
- 第 3 题原始方法：`fn view(&self) -> &str { text.as_str() }`、`fn snapshot(&self) -> String { text.copied() }`、`fn into_text(&mut self) -> String { text }`。
- 先隔离字段访问：三个 text 都应为 self.text，原样编译 E0425；仅修正字段后，view 通过；snapshot 报 E0599，String 没有 copied 方法；into_text 报 E0507，不能从借来的 &mut self 直接移出 String 字段。
- 导师修复：view(&self) -> &str 返回 self.text.as_str()；snapshot(&self) -> String 返回 self.text.as_str().to_owned()（也可 self.text.clone()）；into_text(self) -> String 返回 self.text。
- 导师验证共 12 个版本，记录在 exercises/09-ownership-transfer/attempts/validation.md。正确版本编译运行/断言均通过；失败版本分别记录 E0515、E0716、E0308、E0425、E0599、E0507。环境 rustc 1.98.0、Rust 2024 edition，构建产物已清理。
- 最新完整提交取代中断前未完成输入，只记录本次最终答案为学习者正式尝试。

### 当前证据与下一步

- 有正确作答证据：输入借用继续传递、拥有参数返回所有权、局部拥有值不能返回借用、绑定原始 String 保留借用、共同参数约束与 NLL（见上一轮）。
- 仍需应用确认：trim 的借用结果转换为 String；字段访问语法；共享/可变借用与消耗所有权的 API 选择。
- 已集中反馈并提供 M04-R 综合题，尚未作答，不据导师修复或原理复述自动标为已掌握。

### M04-R 综合回访与复制 API 追问

- 学习者回答：原版可以通过，borrowed 依赖 doc，saved 是自己拥有的 String；追加 borrowed 打印则不能，因为 doc 已销毁。两项判断正确。
- 精确反馈：原版 borrowed 最后使用在 drop(doc) 之前，借用无需跨过销毁；变式在 drop(doc) 处就因仍需借用而拒绝，实际 E0505，不是允许销毁后等到读取才运行时失败。
- 本机实际验证：10-copy-clone-owned/review-original.rs 编译/运行退出码 0，输出两行 rust；review-later-use.rs 编译退出码 1，E0505。新 API 演示 conversion-demo.rs 编译运行断言通过。环境 rustc 1.98.0、Rust 2024 edition，临时产物已清理。
- 学习者追问：to_owned 是什么，何时有 copied 与 clone。
- 新增 copy-clone-owned.md：ToOwned 的关联 Owned 类型、Clone 返回 Self、Copy 标记 trait、不统一深复制、迭代器/Option 同名方法的接收类型与元素约束。核查官方 std 文档，并以本机演示验证。
- 证据更新：NLL 与独立快照在综合场景中已能正确判断；API 原理当前是导师讲解，尚未据此判定学习者可独立写出所有用法。
