# Rust 生命周期讲义

[学习入口](README.md) · [学习过程](learning-log.md) · [练习](exercises/README.md)

## L01：引用什么时候有效

生命周期首先是引用有效性的约束。借用检查器在编译期间检查这些关系；不需要先写 `'a` 才有生命周期。

### 最少语法

```rust
let text = String::from("rust");
let view: &str = text.as_str();
println!("{view}");
```

- `String` 拥有字符串数据；这里 `text` 是所有者，离开作用域时释放资源。
- `&str` 是对字符串数据的共享借用，不拥有数据；`as_str()` 从 String 借用字符串切片，不复制文本。
- `let view = ...` 创建绑定；`println!("{view}")` 读取它。
- `{ ... }` 创建块作用域，内层可以使用外层仍然有效的值。

### 有效性判断

```rust
fn main() {
    let text = String::from("rust");
    {
        let view = text.as_str();
        println!("{view}");
    }
}
```

读到 `println!` 时，`text` 拥有的数据仍然有效，`view` 可以读取它。离开内层块后不再使用 `view`；离开外层块时 `text` 被销毁。

判断代码时依次问：

1. 谁拥有被引用的数据？
2. 数据在什么位置失效？本节先关注离开作用域，后续还要考虑 move 等情况。
3. 引用在哪里被使用？这些使用是否要求访问已经失效的数据？

不要简单把变量从声明到右花括号的整个范围，当成一次借用必须持续的时间。现代 Rust 的借用检查通常能根据控制流和引用的实际使用缩短借用范围；后面会用变式检验这一点。

### 本节任务

完成 [E01：引用有效性判断](exercises/README.md#e01引用有效性判断)。先做预测并解释理由，再编译。能说出结果但不能解释所有者与使用位置，仍需要继续练习。

### E01-C 反馈：绑定的作用域与借用持续时间

`view` 这个绑定仍在作用域内，不代表它的共享借用必须一直持续到块末尾。在本题的直线控制流中，原版 C 最后一次读取 view 是追加文本之前的打印；此后不再使用该引用，因此共享借用无需跨过 push_str，可变借用可以发生。实际编译通过，运行输出 rust 和 rust!。

若末尾再打印 view，共享借用必须保持有效直到这次读取，覆盖中间 push_str 对 text 的可变借用，产生冲突。追加版本实际报 E0502。

```text
原版：创建共享借用 → 读取 view（最后使用）→ 修改 text：允许
变式：创建共享借用 → 读取 view → 修改 text → 再读 view：冲突
```

这类基于实际使用及控制流推断借用范围的机制，通常称为非词法生命周期（NLL）。不要泛化成“看到最后一次使用，就能判断所有复杂控制流”；这里先掌握直线代码的判断。

修改 String 可能使底层缓冲区重新分配，但规则不依赖本次是否真的重新分配：即使剩余容量足够，也不能让冲突的共享借用和可变借用重叠。

### E01-D 反馈：可修改的所有者不是可变借用

```rust
let mut text = String::from("rust"); // 拥有数据，允许修改；不创建借用
text.push_str("!");                // 为此次调用临时借用 &mut text，调用后结束
let view = text.as_str();           // 创建共享借用，供后续读取使用
println!("{view}");
println!("{text}");                // 格式化显示 String 只需共享借用，不会移动它
println!("{view}");
```

此程序实际编译通过，运行输出三行 rust!。push_str 的可变借用发生在 view 创建之前，两者不重叠。多个共享借用可以同时存在，因此打印 text 与持有 view 不冲突。

区分三个概念：

| 形式 | 含义 |
| --- | --- |
| `let mut text = String::from("rust")` | text 是可修改的所有者绑定；mut 本身不创建引用 |
| `let view = &text` 或 `text.as_str()` | 创建共享借用 |
| `let edit = &mut text` | 创建可变借用 |

借用如何结束取决于使用与控制流，不能把所有方法调用的借用都视为在调用返回时结束。这里 push_str 返回 ()，不返回借用；as_str 返回 &str，其借用需要为后续读取保持有效。

## L02：函数为什么需要生命周期标注

### 从局部代码走到函数边界

```rust
fn longest(x: &str, y: &str) -> &str {
    if x.len() > y.len() { x } else { y }
}
```

函数返回一个借来的字符串切片，不复制字符串数据。函数体末尾的表达式就是返回值，不需要显式 return。问题是：签名有两个输入引用，却没有说明输出引用与哪个输入有关；省略规则无法为这里的输出确定关系，需要显式标注。

函数签名是调用者和实现分别检查的契约，不能只靠“读函数体猜结果来自谁”来替代这份约束。

### 标注语法与关系

```rust
fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() { x } else { y }
}
```

- `<'a>` 声明一个生命周期参数；名字可以换，关键是它在各处的关系。
- `&'a str` 表示该引用满足生命周期参数 'a 对有效期的要求。
- 两个输入和输出关联到同一个 'a：输出可能来自任意一个输入，因此调用时必须找到两个输入都能满足的有效范围。
- 不要求两个 String 所有者同时创建或同时销毁；标注不会延长它们的生命。
- 不是“运行时取到哪个就自动只受哪个约束”。调用者按签名检查，即使某次返回外层字符串，也不能据此忽略另一个输入的约束。

对 String 使用 as_str() 得到的引用，数据仍由原 String 拥有；从函数返回引用不会转移数据所有权。

### 避免过度关联

不要机械地给所有参数写同一个 'a。真正需要表达的是返回引用的来源依赖。若某个参数仅被打印、返回引用不会来自它，它未必需要关联到返回值。

完成 [E02](exercises/README.md#e02只返回第一个参数)，先自行标注并解释依赖，再验证。省略规则将在 L03 系统学习。

### E02 反馈：返回类型也要连接到输入

首次尝试为 `fn keep_first<'a>(x: &'a str, note: &str) -> &str`：正确地让 note 不关联到 'a，但输出未标注。存在两个输入引用时，仅给 x 命名不能让输出自动选择 x，实际报 E0106。

```rust
fn keep_first<'a>(x: &'a str, note: &str) -> &'a str {
    println!("{note}");
    x
}
```

返回值上的 'a 才把输出与 x 的有效性要求连接起来。note 虽然没写名字，也有自己的生命周期，并非没有生命周期。

补全版已实际编译运行：note 在内层作用域销毁后，仍能在外层读取返回值，因为返回值来自仍有效的 text。

下一步先预测：若把 note 也标为 &'a str，保持上述调用不变，会怎样？虽然函数体仍只返回 x，调用者也必须遵守签名中的约束。首次预测后再编译验证。

### E02 变式反馈：函数体不取消签名约束

给 note 同样的 'a 后，原调用实际报 E0597：note 在内层块末尾销毁，result 在外层读取。即使实现只返回 x，调用者也按签名检查，不能忽略 note 的约束。这个签名允许实现返回任一输入，因而对本函数表达了过强的要求。

## 模块 M02：生命周期参数与省略规则（完整讲解版）

本模块补全 L02 并覆盖 L03。先连续阅读，再完成一组练习；不要求逐小点回复。建议独立学习约 15–25 分钟，实际耗时自行记录。

### 1. 生命周期标注描述什么

区分“数据存活多久”与“某份借用需要有效多久”。String 所有者负责数据释放，借用检查器检查引用是否在使用时有效，以及借用是否冲突。'a 是编译期描述有效性关系的参数，不是秒数，也不是运行时计时器；标注不会分配内存、复制数据或延长 String 的存活。

`fn f<'a>(x: &'a str) -> &'a str` 声明一族可适用于不同有效范围的调用。每次调用根据调用处的值、后续使用等推断约束；不是在函数定义时把 'a 固定成某个局部块。

对本课的共享引用，可以理解为：输入引用能在 'a 要求的范围内有效，返回引用也可以在该范围内使用。数据实际活得更久没有问题，调用者可以用更短的借用满足要求。两个参数同为 'a 不等于两个所有者必须同时销毁。

### 2. 为什么调用者只按签名判断

调用者需要一份明确的输入/输出依赖契约。函数实现则单独接受检查：它必须保证返回值符合签名声明的关系。这样调用方的安全性不依赖猜测函数体的分支或运行时选择。

```rust
// 输出只依赖 x。note 有独立的、被省略的生命周期。
fn keep_first<'a>(x: &'a str, note: &str) -> &'a str {
    println!("{note}");
    x
}

// 输出的契约同时依赖 x 和 note，尽管实现只返回 x。
fn constrained<'a>(x: &'a str, note: &'a str) -> &'a str {
    println!("{note}");
    x
}
```

对第一个签名，note 的所有者可在调用后先销毁，只要 result 后续依赖的 x 仍有效。对第二个签名，result 在 note 销毁后使用不符合契约。实际验证见 E02 三个版本。

若返回值确实可能来自两个输入，例如 longest，则共同关联到 'a 合理。即使你知道某次外层字符串更长，也不能靠这次运行结果突破签名约束。

### 3. 常见写法

| 写法 | 含义与用途 |
| --- | --- |
| `fn id<'a>(x: &'a str) -> &'a str` | 输出借用关联到输入 x |
| `fn pick<'a>(x: &'a str, y: &'a str) -> &'a str` | 输出可能来自两个输入，使用受二者共同约束 |
| `fn two<'a, 'b>(x: &'a str, y: &'b str) -> (&'a str, &'b str)` | 两个输出分别依赖两个输入，无需把它们捆绑到同一个参数 |
| `&'a mut T` | 带生命周期参数的可变引用；独占规则仍适用，不是只有共享引用才有生命周期 |
| `struct Excerpt<'a> { text: &'a str }` | 结构体携带借用，其使用不能超出被借用数据允许的范围；L04 展开 |
| `&'static str` | 数据能在程序整个执行期间保持有效，例如字符串字面量；不表示某个引用变量必须一直存在 |

这些是语法模式，并非所有函数都需要写出命名生命周期。生命周期之间还能用 'a: 'b 表示有效期约束，后续需要时再学；本次先掌握上面的输入/输出关系，不展开复杂约束。

### 4. 省略规则：省略写法，不省略关系

对本课普通函数与方法，按以下顺序理解：

1. 每个省略生命周期的输入引用，先得到各自独立的生命周期参数。
2. 如果输入中只有一个生命周期参数，省略的输出引用关联到它。
3. 如果是方法，接收者为 &self 或 &mut self，省略的输出引用关联到接收者。
4. 若仍无法确定输出关系，就需要显式写出，不会通过分析函数体来猜。

```rust
// 只有一个输入生命周期：可以省略。
fn head(s: &str) -> &str { s }
// 对应：fn head<'a>(s: &'a str) -> &'a str

// 两个输入引用：各有独立生命周期，输出无法默认选一个。
// fn choose(x: &str, y: &str) -> &str { x } // 需要显式标注

// 无引用输出：通常不需要手写输入生命周期。
fn byte_len(s: &str) -> usize { s.len() }

// 一个引用输入 + 一个普通整数，不会产生两个输入生命周期。
fn unchanged(s: &str, _count: usize) -> &str { s }
```

方法示例：

```rust
struct Label { text: String }

impl Label {
    fn text(&self, _note: &str) -> &str {
        self.text.as_str()
    }
}
```

此处输出默认关联到 self 的借用，而非 note。若方法想返回 note，就需要显式关联到 note，不能仅靠函数体改变默认规则。

### 5. 标注无法解决什么

```rust
// 无法靠补标注修复：s 在函数返回时销毁。
// fn bad<'a>() -> &'a str {
//     let s = String::from("hello");
//     s.as_str()
// }

fn owned() -> String {
    String::from("hello") // 把数据所有权交给调用者
}

fn literal() -> &'static str {
    "hello" // 字面量的数据不由函数内局部 String 持有
}
```

返回拥有的 String 与返回借用是两种不同契约。不能把局部 String 的 as_str() 标成 &'static str 让它永久有效，也不应靠到处添加 'static 来压掉借用错误。

### 6. 判断步骤与检查边界

先找输出是否包含引用 → 找它依赖哪些输入或数据来源 → 检查省略规则 → 必要时用参数表达关系 → 在调用点检查所有相关数据是否覆盖输出的使用 → 检查共享/可变借用有无冲突。

本模块中的 E02 原始、补全、过度关联版本已实际验证；其他教学写法用于解释规则，不据此宣称所有示例已逐一执行。M02 练习待学习者整组提交后再保存尝试、编译与反馈。

M02 整组提交后，相关验证及编译机制解释已补充到[深入：生命周期关联、编译器约束与代码生成](compiler-mechanism.md)。练习进度与原始回答见学习记录。

## L04：生命周期关系不限于函数输入输出

更一般的理解是：生命周期参数与约束用于表达引用有效性要求，函数输入/输出只是其中一种出现位置。局部借用、保存引用的类型、方法、trait 及泛型约束也会涉及这些关系。

### 1. 局部引用：通常推断，不手写参数

```rust
let text = String::from("rust");
let view = text.as_str();
println!("{view}");
```

即使没有函数返回引用，view 的使用仍要受到 text 数据有效性和借用冲突规则约束。没有命名 'a 不等于没有生命周期检查。

### 2. 结构体字段：保存的是外部借用

```rust
struct Excerpt<'a> {
    text: &'a str,
}
```

Excerpt 本身不拥有字符串数据。'a 是字段引用的生命周期参数，不是要求 Excerpt 实例恰好存活 'a 那么久。结构体可以很快销毁，也可以在数据仍然有效的范围内继续使用；销毁 Excerpt 不会销毁它借用的 String。

如果外部数据已失效，就不能再通过结构体字段使用该引用。若改成 `struct OwnedExcerpt { text: String }`，结构体拥有字符串，不再需要这个借用生命周期参数。

### 3. 多个字段可以关联，也可以独立

```rust
struct PairView<'a, 'b> {
    first: &'a str,
    second: &'b str,
}
```

两个参数分别描述字段引用的要求。若改成一个 'a 用于两个字段，就是用同一个有效性参数约束二者；仍不要求两个字符串所有者同时销毁。不要把“结构体有生命周期参数”理解为整个结构体只有一个统一倒计时。

### 4. 方法中要区分数据借用与 self 借用

```rust
impl<'a> Excerpt<'a> {
    fn via_self(&self) -> &str {
        self.text
    }

    fn data(&self) -> &'a str {
        self.text
    }
}
```

impl<'a> 在实现块中声明参数，Excerpt<'a> 使用它。第一个方法按省略规则把输出关联到本次 &self 借用。它的关系可以展开理解为 `fn via_self<'s>(&'s self) -> &'s str`。第二个方法明确把输出关联到字段携带的 'a，而非本次 self 借用。

```rust
let owner = String::from("rust");
let result;
{
    let excerpt = Excerpt { text: owner.as_str() };
    result = excerpt.data();
}
println!("{result}");
```

此例可以通过：excerpt 先销毁，但 owner 仍有效；data 返回的是借来的外部字符串切片，不是对 excerpt 自身存储的借用。若将调用换成 via_self，则输出契约关联到 excerpt 的借用，不能越过它的销毁位置。两种情况已实际编译验证，见练习目录 04-struct-borrow。

这是特定共享引用字段的例子，不能据此认为所有结构体字段都能以 'a 返回。例如结构体自己拥有的 String，返回其切片就需要依赖 self 的借用。

### 5. 还能表达有效期之间的约束

`'long: 'short` 读作 long outlives short：long 覆盖 short 所要求的有效范围，不要求严格更长，也不是时间相减。

```rust
fn shorten<'long: 'short, 'short>(s: &'long str) -> &'short str {
    s
}
```

对共享引用，这是在已有较长有效性保证下提供较短的保证，不改变数据的销毁位置。还有 T: 'a，要求 T 中携带的生命周期满足相应 outlives 条件；它不是强制某个 T 类型的局部变量一定活到 'a 结束。本次先认出两种写法，不展开更复杂 trait 约束。

参考：[Rust Book：结构体与方法的生命周期](https://doc.rust-lang.org/book/ch10-03-lifetime-syntax.html)、[Rust Reference：生命周期约束](https://doc.rust-lang.org/reference/trait-bounds.html)。核查日期：2026-10-20。

### 追问：谁覆盖谁由什么决定

'a 本身没有方向。对直接的 &str，来源引用已有的有效性保证必须覆盖目标类型/使用的要求：传实参时，实参支持形参；返回表达式支持返回类型；返回类型的保证支持调用者后续读取。完整推导和结构体类比见[编译机制第 8 节](compiler-mechanism.md#8-覆盖方向从哪里来)。

## 模块 M03：把生命周期用于数据结构和 API 设计

建议约 15–25 分钟：先连续阅读，再一次完成 exercises/README.md 中的 M03 四题。承接 L04，并完成 L05 的核心内容。学习者已表示大概理解编译器机制；通过本轮应用检验，不预设原有误区全部消除。

### 1. 先选所有权，再写生命周期

```rust
struct TextView<'data> {
    text: &'data str,
}

struct OwnedText {
    text: String,
}
```

TextView 保存外部数据的视图，通常不复制字符串，使用依赖外部数据有效。OwnedText 持有字符串；移动 OwnedText 会移动所有权，销毁它会销毁字段。生命周期参数不替代所有权设计；若产物需要独立保存，拥有 String 往往更符合需求。

### 2. 从函数到结构体，依赖关系继续传播

```rust
impl<'data> TextView<'data> {
    fn new(text: &'data str) -> Self {
        Self { text }
    }
}
```

Self 在这里就是 TextView<'data>。输入 text 提供的引用要满足字段 &'data str 的要求。函数返回的是一个结构体值，但它内部携带借用，所以生命周期关系没有因“返回的不是 &str”而消失。

调用 TextView::new(...) 通常由编译器推断 data，不需要调用者人为指定一个作用域名。返回结构体不是复制字符串数据，只是创建含有引用字段的值。

### 3. 方法输出契约：本次 self 借用，或外部数据借用

```rust
impl<'data> TextView<'data> {
    fn tied_to_self(&self) -> &str {
        self.text
    }

    fn tied_to_data(&self) -> &'data str {
        self.text
    }
}
```

第一个方法按省略规则，可以展开理解为 `fn tied_to_self<'s>(&'s self) -> &'s str`。返回类型只承诺由本次 self 借用支持。第二个方法则返回字段已经携带的外部借用，不把输出有效性收窄到本次借用 self。

两者实现相同，但契约不同。由于 &'data str 是共享引用且可 Copy，第二个方法可以把字段中保存的引用复制出来。不能无条件推广到 &'data mut T 或结构体自己拥有的 String。

```rust
let owner = String::from("rust");
let result;
{
    let view = TextView::new(owner.as_str());
    result = view.tied_to_data();
}
println!("{result}");
```

view 先销毁，但返回引用指向 owner 的字符串数据，owner 仍有效，因此成立。若通过 tied_to_self 获取结果，签名会把输出关联到 view 的借用，此处不能跨过 view 的销毁。前一轮已分别验证。

### 4. 借用与拥有之间如何转换

```rust
impl<'data> TextView<'data> {
    fn snapshot(&self) -> String {
        self.text.to_owned()
    }
}
```

对 &str 调用 to_owned() 会复制文本，生成拥有数据的 String。snapshot 的返回值就不依赖 TextView 或其借用的数据；它有自己的数据与所有者。代价是复制及通常发生的内存分配，不是修改生命周期让原借用独立。

如果函数内部生成新字符串，例如 format!(...)，通常直接返回 String，把结果所有权交给调用者。返回局部 String 的 as_str() 会留下悬空引用，补 'a 无法修复。

### 5. &'static str 和 String 的边界

```rust
fn default_text() -> &'static str {
    "default"
}
```

字符串字面量的数据具有静态存储期，因此可以提供 static 保证。这不意味着保存该引用的局部绑定必须一直存在。

需要区分：

| 数据来源/需求 | 合适的结果形式 |
| --- | --- |
| 返回固定的字符串字面量 | &'static str |
| 从调用者输入中选取片段 | 与输入有关联的 &str 或借用型结构体 |
| 在函数内部生成新文本，调用者需要保留 | String |
| 借用结果需要变成独立保存的快照 | 复制为 String |

不要把 `&'static str` 当作“所有借用问题的统一解法”。调用者局部 String 的切片不能仅靠标注变成 static，且 static 也不表示允许任意修改。

### 6. 回访 NLL：结构体保存借用也一样看使用

若某个 TextView 保存了 text 的共享借用，在之后修改 text 时，要看该借用是否仍需供后续使用。如果修改之后还读取 view.text，则借用需要跨过修改，可能发生冲突；若最后一次使用已在修改之前结束，可以允许修改。mut 所有者绑定本身仍不创建可变借用。

判断时不能只找变量离开大括号的位置，也不能把“拥有结构体”误认为“拥有它所指的字符串”。

### 7. 本模块验证与作答安排

[完整讲义演示](exercises/08-application/lesson-demo.rs) 已用 rustc 1.98.0、Rust 2024 edition 编译运行，断言通过：视图包装先销毁后外部借用仍可读取；owner 销毁后，已复制的 String 快照仍可读取。输出 snapshot=rust, default=default。此为导师教学演示，不是学习者练习完成记录。

随后完成 M03 四题：输入依赖、方法签名、局部数据返回、借用与修改。新练习尚未编译或预填答案，首次整组提交后集中反馈并验证。

### M03 集中反馈：谁为返回值提供数据

首次整组回答中，输入约束与 NLL 两题正确；方法输出与动态字符串返回需要修正。

**方法字段访问与输出契约是两件事。** `fn raw(&self) -> &str { text }` 首先因 text 没有绑定而报 E0425；改成 self.text 后，省略的输出仍关联到 self。满足题目“包装先销毁，外部数据仍有效时输出可继续使用”的写法是：

```rust
impl<'a> View<'a> {
    fn raw(&self) -> &'a str {
        self.text
    }
}
```

若字段改成自己拥有的 String，切片借用的是结构体内部数据：

```rust
struct OwnedView { text: String }
impl OwnedView {
    fn raw(&self) -> &str {
        self.text.as_str()
    }
}
```

此时输出关联到 self，不能让结构体先销毁而后继续读取切片。接收返回值的变量只能产生“我还要在这里使用”的需求，不能为被引用数据提供存活保证。

**动态生成的字符串需要转移所有权。** 给 name 和输出标注同一个 a，只声称两者有关联，不会让实际从局部 message 借到的引用满足这个声称。

```rust
fn greeting(name: &str) -> String {
    let message = format!("Hello, {name}!");
    message
}
```

format! 创建新拥有的字符串；返回 message 把 String 的所有权移给调用者。局部绑定结束，不等于已移交给调用者的数据被释放。返回 message.as_str() 则只返回借用，message 所有权没有被移出，函数结束时局部 String 会被销毁。补 'a 或 static 都不能修复这条链路。

返回 String 的版本实际验证了：输入 name 的 String 在内层销毁后，外层仍可读取完整问候语，因为 format! 已生成独立文本。返回 String 可以继续写成 `format!(...)` 尾表达式。

详见[逐版本编译诊断与运行记录](exercises/08-application/attempts/validation.md)。进入 M03-R 集中迁移，不把已经讲出的修复当作学习者独立掌握的证据。

### 追问：既然输出默认关联 self，为什么还需要 impl<'a>

默认省略规则确实把 `fn raw(&self) -> &str` 的输出关联到本次 self 借用。它是一种省略写法的规则，不禁止显式声明另一个输出关系。

本题有两种不同的生命周期：

```rust
struct View<'data> {
    text: &'data str, // 外部字符串引用的有效性参数
}

impl<'data> View<'data> {
    fn by_self<'s>(&'s self) -> &'s str {
        self.text
    }

    fn by_data<'s>(&'s self) -> &'data str {
        self.text
    }
}
```

by_self 是默认 `fn by_self(&self) -> &str` 的关系展开；by_data 的输出显式使用字段携带的 data，self 借用只需支持方法执行。方法体都返回 self.text，但一个契约关联包装的借用，另一个保留外部借用的保证。

这里 impl<'data> 不是给 impl 块增加一个“存活期”，也不是要求 self 恰好活 data 那么久；它声明实现所使用的泛型参数，View<'data> 用该参数指明被实现的类型，方法才能在返回类型中引用它。结构体定义和 impl 各有自己的参数作用域，即使都叫 a 也不是全局变量；可以把 impl 参数改名为 data，只要在该实现块内一致使用。

若方法不需要显式提及字段的生命周期，可以使用 `impl View<'_> { fn raw(&self) -> &str { self.text } }`，不必手写命名参数。命名 data 的目的，是让方法契约能明确表达“输出使用字段保存的外部引用有效性”，而不是绕过省略规则。

默认关系本身完全合法，但不满足题目要求的更宽使用方式：View 包装在内层销毁、外部 owner 仍有效时，输出继续在外层使用。两种契约的对比已在 02-self-contract.rs 和 02-external-fixed.rs 实际验证。

结构体拥有 String 时，没有可直接复制出来的外部 &'data str 保证；输出通常必须关联 self，不能人为添加一个 impl<'data> 就让切片逃过所有者销毁。

### 追问：代码怎样表达“保留字段已有的外部借用关系”

这句话不是额外的语言操作，由字段类型、返回类型和实现的类型检查共同表达：

```rust
struct View<'data> {
    text: &'data str, // 字段已经携带 data 的有效性保证
}

impl<'data> View<'data> {
    fn raw<'s>(&'s self) -> &'data str { // 输出显式使用同一个 data
        let result: &'data str = self.text;
        result
    }
}
```

读取 self.text 需要 self 借用有效，但字段存的是一份共享引用，能把这份引用 Copy 出来。复制不创建新的字符串，也不是返回对字段存储位置的引用。self.text 的值类型是 &'data str，而不是因为经 self 访问就自动变成 &'s str。

手工类型检查：

```text
字段读取表达式 self.text：&'data str
局部 result 要求：        &'data str
返回类型要求：           &'data str
```

输出类型使用 data，把本次调用返回值的有效性与 View 的类型参数连接起来；构造 View 时该参数已经受字段初始化引用的约束。data 不记录运行时来源地址，返回值也不一定要指向字段当前指向的同一地址；实现必须提供一个满足 data 的引用，例如相应子切片也可。

默认写法 `fn raw(&self) -> &str { self.text }` 的输出则关联本次 self 借用 s。字段读取依旧能提供 data 的保证，但接口只承诺 s；只要类型的良构性支持 data 覆盖 s，就可以把较长保证缩短。这不说明默认方法返回了不同的底层指针。

还需区分两个表达式：self.text 取出字段内的字符串引用；&self.text 则新建对“引用字段本身”的借用，其类型关系可写成 &'s &'data str，外层依赖 self 的借用。本题应返回前者。

## 模块 M04：所有权转移、临时值与综合验收

这是本次入门的收尾模块，不扩展 HRTB、复杂变型或异步借用。目标是把“借用约束”与“数据由谁释放”连起来，纠正 M03 返回局部借用的误区。建议阅读和整组作答约 15–20 分钟；不是实际耗时记录。

### 1. 借用参数与拥有参数不是同一种输入

```rust
fn read(s: &str) -> &str { s }
fn take(s: String) -> String { s }
```

read 接收引用，没有获得底层 String 的所有权；返回继续借用的数据，输入输出按省略规则关联。take 接收拥有值，调用时所有权进入函数，返回 s 又把所有权交给调用者。

```rust
let first = String::from("rust");
let second = take(first);
println!("{second}");
// 此后不能再把 first 当作仍持有 String 的绑定使用。
```

返回 s 不需要复制字符串内容。不能把“参数绑定离开作用域”理解为“一切曾由它持有的数据都被释放”：所有权已经移出时，旧绑定不再负责释放该值。

### 2. 作用域结束与值被释放要分开

```rust
let output = {
    let local = String::from("block result");
    local
};
println!("{output}");
```

local 的 String 被作为块结果移动给 output，块结束后仍可读取。若块结果改成 local.as_str()，则只把借用交出，所有权仍在块内，不能在块外通过它访问数据。关键差别是返回表达式的类型与所有权语义，不是有没有生命周期名字。

### 3. 新生成的数据，不必依赖输入生命周期

```rust
fn make(name: &str) -> String {
    format!("Hello, {name}!")
}
```

name 仅在生成新文本时被读取，返回 String 拥有独立文本。name 的所有者可以在调用后先销毁，而返回值继续存在。若为了命名给输入加一个 a，也不会改变返回 String 自有数据的性质；这里无需手写它。

与借用型转换相对：`fn trim(s: &str) -> &str { s.trim() }` 返回原输入中的切片，不拥有数据，必须由输入支持后续使用。trim 返回的是切片，不是自动创建 String；需要独立保存时可以对切片调用 to_owned()。

### 4. 临时值：先找没被命名的所有者

String::from(...)、format!(...) 等表达式可以产生临时 String。即使代码没有写 let owner，借来的数据仍有所有者和销毁位置，不能只盯着命名变量。

```rust
let n = String::from("abc").len();
println!("{n}");
```

这里临时 String 只需支持 len 调用；结果 n 是 usize，不包含借用，不依赖字符串之后仍存在。

如果调用结果包含输入借用，就要检查其后续使用是否越过临时 String 的销毁。本课先分析普通语句中的调用链；Rust 还有特定的临时值延长规则，不能把“所有临时值都在分号处销毁”当成适用于任意语法的定律。本轮题目不依赖那些特殊规则。

通常可以通过先绑定 String 所有者来明确其作用域，或把借用结果复制为 String 以独立保存。修复应依据需求选择，不能先加 static。

### 5. 方法接收 self 还是 &self，也决定所有权能力

| 接收形式 | 方法得到什么 | 对 String 字段的典型能力 |
| --- | --- | --- |
| &self | 共享借用结构体 | 读取、返回借用、复制为独立 String；不能直接移走字段所有权 |
| &mut self | 可变借用结构体 | 在借用规则下修改；本次不展开替换字段操作 |
| self | 获得结构体所有权 | 对没有自定义 Drop 的简单结构体，可以把 String 字段移动出去 |

因此“借用查看”“不消耗原值地复制快照”“消耗原值取走数据”是三种不同 API 目标，应先明确目标再写签名，而不是试图让同一个 &str 返回值满足所有目标。

### 6. 讲义演示与验收

[完整所有权演示](exercises/09-ownership-transfer/lesson-demo.rs) 已在 rustc 1.98.0、Rust 2024 edition 编译运行，退出码均为 0，断言通过，输出 rust; block result; Hello, Rust!。该演示分别覆盖读取借用、转移拥有值、块结果移动、动态生成独立文本，不是学习者独立作答证据。

完成练习 M04 整组，包含尚未回答的 M03-R，以及临时值和 Document API 选择。之后依据真实作答与验证整理“已能应用/仍需复习”，不自动宣称掌握所有生命周期内容。

### M04 集中反馈：借用结果、复制结果与消耗接收者

2026-10-21，借用/移动的三项判断与绑定原始 String 的修复正确。其余问题不靠增加生命周期参数解决，而要明确每个表达式的类型和所有权操作。

```rust
fn label(input: String) -> String {
    input.trim().to_owned()
}
```

输入是 String，但 trim() 结果仍然是 &str；to_owned() 才把切片复制为拥有数据的 String。函数返回 String 并不会自动执行这个转换。需要只读输入也可写 fn label(input: &str) -> String，返回同样的复制结果；本次优先保留学习者原提交的拥有参数设计，只补必要转换。

Document 的三个目标对应：

```rust
impl Document {
    fn view(&self) -> &str {
        self.text.as_str()
    }

    fn snapshot(&self) -> String {
        self.text.as_str().to_owned()
    }

    fn into_text(self) -> String {
        self.text
    }
}
```

访问字段需写 self.text。snapshot 要创建独立数据，可使用切片的 to_owned() 或 String 的 clone()，String 没有这里所写的 copied() 方法。String 不是 Copy 类型，不能用隐式位复制替代独立拥有文本的复制语义。

&mut self 允许修改，但所有权仍属于调用者，方法结束时原对象必须保持合法。直接把 String 字段移走会留下未初始化字段，因此 self.text 不能从借用中直接移出。self 接收者则消耗整个 Document，对本题的简单结构体可把字段所有权移给调用者。借用期间通过替换字段取出旧值是另一种设计，本题不要求它。

收尾时对照三种操作：as_str() 提供借用；to_owned()/clone() 创建独立 String；返回拥有的 self.text 则转移已有数据的所有权。

完整编译诊断、隔离版本及断言见[本轮验证记录](exercises/09-ownership-transfer/attempts/validation.md)。
