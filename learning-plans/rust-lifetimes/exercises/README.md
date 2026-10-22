# Rust 生命周期练习

[学习入口](../README.md) · [讲义](../lesson.md) · [学习记录](../learning-log.md)

## E01：引用有效性判断

输入：[case-a.rs](01-reference-validity/case-a.rs) 和 [case-b.rs](01-reference-validity/case-b.rs)。所需语法见讲义 L01。

先不编译，分别回答：

1. 能否通过编译？
2. 哪个变量拥有字符串数据？它在哪里失效？
3. 哪次引用使用决定了你的判断？

记录预测后，分别执行下列命令验证。执行目录是本练习目录 `learning-plans/rust-lifetimes/exercises/`；临时目录每次新建，构建产物不进入仓库。

```sh
rust_lifetime_build_dir=$(mktemp -d /tmp/rust-lifetimes.XXXXXX)
rustc --edition=2024 --crate-name lifetime_case_a 01-reference-validity/case-a.rs -o "$rust_lifetime_build_dir/case-a"
rustc --edition=2024 --crate-name lifetime_case_b 01-reference-validity/case-b.rs -o "$rust_lifetime_build_dir/case-b"
```

每条命令单独观察退出状态及诊断。若失败，定位到借用来源、数据失效、后续使用三处；需要修复时另存 `case-*-fixed.rs`，保留原题。若提示 rustc 不存在，先排查工具环境。

预期观察：两个案例只改变引用使用的位置，检查编译器是否接受。具体答案在首次预测后反馈。

通过标准：能解释两例的有效性，结合诊断修复拒绝的案例，并在改变打印位置后重新判断。导师实际编译与学习者独立判断分别记录。

### E01-C：借用必须持续到块末尾吗？

输入：[case-c.rs](01-reference-validity/case-c.rs)。

补充语法：`mut` 允许修改绑定持有的值；`String::push_str(&mut self, ...)` 需要独占的可变借用。对同一数据，共享借用需要保持有效期间不能进行与之冲突的可变借用。

先判断 C 是否通过编译，并说明 `view` 在哪里最后一次被读取。再判断：如果在程序末尾追加 `println!("{view}");`，结果是否改变？先记录预测，再分别验证两个版本；追加版本保存为独立文件，不覆盖原题。

首次作答后已保存[追加版本](01-reference-validity/case-c-later-use.rs)，反馈见讲义与学习记录。

纠错后迁移：在追加版本中，将 push_str 移到创建 view 之前。判断是否通过，并用“共享借用需要持续到哪里”解释；先口头回答，再验证。

迁移回答后已保存 [D：先修改再借用](01-reference-validity/case-d-mutate-first.rs)，实际结果和反馈见学习记录。

### E01-E：区分绑定与借用

以下三行作为独立场景判断，不要按从上到下连续执行理解：

1. `let mut text = String::from("rust");`
2. 已有 text：`let view = &text;`
3. 已有可修改的 text：`let edit = &mut text;`

哪些行真正创建借用？分别是什么借用？第 1 行的 mut 表达什么？这是语义分类题，不以编译退出码作为理解证据。

## E02：只返回第一个参数

以下为待修复的函数签名；函数体只打印备注并返回 x。

```rust
fn keep_first(x: &str, note: &str) -> &str {
    println!("{note}");
    x
}
```

任务：

1. 补上必要的生命周期声明与标注，避免让 note 约束返回引用。
2. 说明返回值为何依赖 x，以及 note 是否需要与返回值关联。

以下调用作为条件变化检验：note 的 String 在内层销毁，结果在外层读取。补好签名后，判断该调用能否通过，并解释。

```rust
fn main() {
    let text = String::from("rust");
    let result;
    {
        let note = String::from("只是一条备注");
        result = keep_first(text.as_str(), note.as_str());
    }
    println!("{result}");
}
```

本题先在对话中提交签名和理由，再保存实际尝试到 E02 代码目录并编译。尚未实际执行；预期约束在首次回答后反馈，不预填答案。

验证方式：将函数与 main 合并，用 `rustc --edition=2024 --crate-name lifetime_e02 <源码路径> -o <临时目录>/e02` 编译，成功后运行。若拒绝，依据诊断检查是否意外把 note 的有效期关联到了返回值。

通过标准：能写出所需依赖关系，并解释为何内层 note 的销毁不会使来自外层 text 的返回引用失效；随后对比把两个参数均关联到同一个生命周期时的行为。

### 首次尝试与后续变式

- [首次签名尝试](02-return-dependency/attempt-01.rs)：保留学习者签名，导师补上原题函数体与调用。
- [导师补全版](02-return-dependency/fixed.rs)：返回类型补上 'a，已编译运行；结果见学习记录。
- 待预测变式：把补全版的 note 改成 &'a str，其余代码不变。内层 note 销毁后在外层读取 result 是否仍能通过？先预测并解释，再保存变式并验证。

变式已作答并保存为 [overconstrained.rs](02-return-dependency/overconstrained.rs)，实际报 E0597，详细反馈见讲义与学习日志。

## M02：整组练习（一次提交，集中反馈）

先阅读讲义模块 M02。无需逐题等待模型；可先集中写完，卡住的题标注疑问。预计约 10–15 分钟，不要求复述整份讲义。三个任务分别覆盖契约判断、省略规则和独立依赖。

### M02-1：按签名判断调用

函数实现均返回 x，区别仅在签名：

```rust
// 版本 A
fn first<'a>(x: &'a str, y: &str) -> &'a str { x }
// 版本 B（替换 A，不能同名并存）
fn first<'a>(x: &'a str, y: &'a str) -> &'a str { x }

fn main() {
    let outside = String::from("outside");
    let r;
    {
        let inside = String::from("inside");
        r = first(outside.as_str(), inside.as_str());
    }
    println!("{r}");
}
```

分别判断 A/B 是否通过并用一句话说明。再判断：若把最后的 println 移进内层块、放在调用之后，A/B 的结果各是什么？允许未使用 y 的警告，不把警告视为编译失败。

### M02-2：判断哪些签名需要显式生命周期

只判断生命周期关系是否能通过省略确定，不要求实现字符串算法。

```rust
// a
fn trim(s: &str) -> &str;
// b
fn select(x: &str, y: &str, take_x: bool) -> &str;
// c
fn count(x: &str, y: &str) -> usize;
// d：假定它位于结构体的 impl 内
fn label(&self, fallback: &str) -> &str;
```

对每项说明能否省略；若能且输出是引用，说明它关联哪个输入。以上是签名示意，不是可直接作为普通函数定义编译的源码。

### M02-3：两个输出分别依赖两个输入

给下面函数补充必要生命周期，保留两个输出各自独立的依赖，不把它们强制关联到同一个参数。

```rust
fn pair(x: &str, y: &str) -> (&str, &str) {
    (x, y)
}
```

写出函数签名即可，并用自己的话回答：生命周期标注会不会改变 x、y 背后数据的销毁时间？

验证计划：首次整组提交后保存独立源码，用本机 rustc 逐一检查 M02-1 的四种情况和 M02-3；M02-2 结合完整函数或方法验证，不直接编译上面的分号签名。结果、原始推理和修正集中写入日志。通过标准是能把输入/输出契约用于不同调用范围，不仅是照抄标注。

### M02 已完成的导师验证

| 源码 | 实际结果 |
| --- | --- |
| [A 外层打印](03-module-check/a-outer.rs) | 编译通过 |
| [B 外层打印](03-module-check/b-outer.rs) | E0597 |
| [A 内层打印](03-module-check/a-inner.rs) | 编译通过 |
| [B 内层打印](03-module-check/b-inner.rs) | 编译通过 |
| [pair 与省略示例](03-module-check/pair-and-elision.rs) | 编译、运行断言通过 |

这些文件由导师根据学习者答案补齐完整函数体/调用，用于验证；不当作学习者独立编写了所有实现的证据。原始判断及修正见学习记录。

## M03：借用型结构体与返回值设计（整组提交）

先阅读讲义模块 M03。以下公共定义供第 1、2、4 题使用；代码片段放在 main 中理解。未知函数调用均由本页给出定义，不要求猜 API。先预测/编写，再在提交后验证；卡点可统一标出。

```rust
struct View<'a> { text: &'a str }

fn build<'a>(text: &'a str, _note: &str) -> View<'a> {
    View { text }
}
```

### M03-1：结构体传递输入依赖

A：

```rust
let owner = String::from("message");
let view;
{
    let note = String::from("temporary note");
    view = build(owner.as_str(), note.as_str());
}
println!("{}", view.text);
```

B（与 A 是独立场景）：

```rust
let view;
{
    let owner = String::from("message");
    view = build(owner.as_str(), "note");
}
println!("{}", view.text);
```

分别判断 A/B 能否通过。再判断：仅把 build 中 _note 的类型改为 &'a str，A 的结果是否改变？每项一句理由，回访函数体并未返回 note 但签名仍有约束的情况。

### M03-2：写出保留外部借用的方法签名

补全 View 的方法，要求返回的字符串切片可在 View 包装值先销毁后使用，只要外部 String 仍有效：

```rust
impl<'a> View<'a> {
    // 在这里补出 raw 方法的完整签名和函数体
}
```

同时回答：若把 View.text 改成 String，能否照搬这个返回 &'a str 的思路？应把输出关联到什么？

### M03-3：修复函数内部生成文本的返回方式

```rust
fn greeting(name: &str) -> &str {
    let message = format!("Hello, {name}!");
    message.as_str()
}
```

format! 生成一个拥有文本的 String。调用者需要把问候语保留到调用结束以后。修改函数签名与函数体以满足需求，并解释为什么把返回类型改成 &'static str 不能直接解决。保持动态包含 name，不将功能改成返回固定字面量。

### M03-4：回访共享借用与修改

```rust
let mut owner = String::from("rust");
let view = View { text: owner.as_str() };
println!("{}", view.text);
owner.push_str("!");
println!("{owner}");
```

判断能否通过。再判断：若末尾追加 `println!("{}", view.text);`，结果是否改变？说清楚哪一处操作创建/需要可变借用，以及 view 中的共享借用需持续到哪里。

本组预期约 10–15 分钟，可一次提交 M03-1 至 M03-4。首次作答后保存实际尝试与修正版，编译预测案例，运行问候语及方法用例，并把证据集中记入过程日志。目前只有讲义演示已运行，新练习未执行。

M03 首次整组提交后，实际尝试、导师修复与隔离实验已存入[attempts/](08-application/attempts/validation.md)；原始回答与反馈见学习记录，具体结果以该验证记录为准。

### M03-R：纠错后迁移，三个函数一次判断

以下为独立函数，不依赖彼此。对每个判断能否通过，并说明“数据由谁拥有、返回时是借用继续传递还是所有权转移”。若拒绝，给出保持其目的的修复方向，不用重复抄完整讲义。

```rust
// A：借用输入数据
fn pass<'a>(s: &'a str) -> &'a str {
    s
}

// B：接收拥有的字符串，再返回它的切片
fn slice<'a>(s: String) -> &'a str {
    s.as_str()
}

// C：接收拥有的字符串，再返回字符串
fn transfer(s: String) -> String {
    s
}
```

尚未作答或编译；等首次整组预测后再保存和验证。重点是返回绑定值与返回它的借用的区别，而不是在所有签名里寻找一个可以补上的 a。

## M04：收尾综合题（一次提交）

先阅读讲义 M04。本组第 1 题合并尚未回答的 M03-R，不要求重复作答两遍；第 2、3 题检验新场景。首次提交前不执行练习、不提前填答案。

### M04-1：三种返回方式

判断上述 M03-R 的 pass、slice、transfer 各能否通过，并说明所有者与返回时的动作（借用传递/所有权转移）。slice 若被拒绝，给出一种保持其使用目标合理的 API 调整方向，并说明为何改变了所有权契约。

### M04-2：没有命名所有者的借用

```rust
fn label(input: &str) -> &str {
    input.trim()
}

fn main() {
    let result = label(String::from("  rust  ").as_str());
    println!("{result}");
}
```

trim 去掉首尾空白，返回原字符串中的切片，不新建 String。

判断是否通过。指出底层所有者在哪里产生，后续读取是否需要它继续有效。给出两种修复方向：一种保留借用，一种让 result 拥有独立文本。要求都仍能打印 rust，不把动态处理改成固定字面量。

### M04-3：按目标设计 Document 方法

```rust
struct Document {
    text: String,
}
```

这是没有自定义 Drop 的简单结构体。为以下三个方法分别写出完整签名和函数体：

1. view：只读查看文本，不复制、不消耗 Document。
2. snapshot：保留 Document，生成可以独立保存的 String。
3. into_text：消耗 Document，把其 String 字段的所有权交给调用者，不复制文本。

提示：根据讲义选择 &self 或 self；对 &str 的 to_owned() 会复制文本，String::as_str() 返回借用。不要从 &self 直接移走 String 字段，也不要用 static 掩盖依赖。

通过标准：能够分别辨认借用/拥有、把临时值识别为数据所有者、根据目标选择方法的接收与返回类型。首次整组提交后按具体代码编译验证并集中反馈。

2026-10-21 已提交并验证，用户尝试、仅改字段访问的隔离版本、导师完整修复分别保存于[验证记录](09-ownership-transfer/attempts/validation.md)。学习者原始回答与掌握证据在学习日志中。

### M04-R：复制快照与借用范围的综合回访

使用集中反馈中已修复的 Document 三个方法。判断以下完整 main 能否通过，并说明 borrowed、saved 各自依赖哪些数据：

```rust
fn main() {
    let doc = Document { text: String::from("rust") };
    let borrowed = doc.view();
    let saved = doc.snapshot();
    println!("{borrowed}");
    drop(doc);
    println!("{saved}");
}
```

drop(doc) 消耗并销毁 doc。再判断：若在最后追加 println!("{borrowed}")，结果是否改变？解释 saved 是通过借用、复制还是移动得到数据的。先整组回答，再验证；当前题目未执行、不预填答案。

2026-10-21：学习者原版/变式两项判断正确；已验证原版通过、变式 E0505。源码和结果见[综合回访与转换 API 验证](10-copy-clone-owned/validation.md)。此题无需重复作答。
