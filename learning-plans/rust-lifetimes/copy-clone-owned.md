# to_owned、clone、copied 与 cloned

[学习入口](README.md) · [学习记录](learning-log.md) · [复习笔记](../../topics/rust-lifetimes.md)

2026-10-21，针对学习者关于“函数是什么意思、何时可调用”的追问。此页区分类型/trait 提供的方法，不按英文名字猜行为。

## 1. to_owned：取得类型对应的拥有形式

定义在 std::borrow::ToOwned trait，核心形态为：

```rust
trait ToOwned {
    type Owned; // 简化示意：实际定义还有 Borrow<Self> 约束
    fn to_owned(&self) -> Self::Owned;
}
```

Owned 是该实现选定的结果类型，并非总与 Self 相同。对字符串：实现面向 str，Owned 是 String；对切片 [T]（T: Clone），Owned 是 Vec<T>。

```rust
let borrowed: &str = "rust";
let text: String = borrowed.to_owned();
let slice: &[i32] = &[1, 2];
let numbers: Vec<i32> = slice.to_owned();
```

对这些例子会复制内容，原数据不被消耗。对一般类型应看实现；ToOwned 也为 Clone 类型提供同类型结果的 blanket implementation，不能理解成只对 &str 存在，也不能保证任意类型都会做深复制。

本课 `input.trim().to_owned()` 的类型链是 String → 借用的 str 切片（&str）→ 新 String。最后一步创建了拥有文本，不是生命周期标注变化。

来源：[ToOwned](https://doc.rust-lang.org/std/borrow/trait.ToOwned.html)。

## 2. clone：显式创建同一个 Self 类型的新值

```rust
trait Clone: Sized {
    fn clone(&self) -> Self;
}
```

类型实现 Clone 时可以使用对应 clone 方法。String::clone 创建独立的 String 文本，Vec<T> 的 Clone 要求 T: Clone，自定义结构体可在字段都能 Clone 时使用 #[derive(Clone)]。原值仍然存在。

```rust
let first = String::from("rust");
let mut second = first.clone();
second.push('!');
assert_eq!(first, "rust");
```

Clone 不等于统一深复制。共享引用本身实现 Clone，复制引用仍指向相同数据；Rc/Arc 的 clone 通常增加共享计数而非复制底层对象。判断需看选择了哪个 Self 的实现，以及返回类型。

对 &str 想得到 String，使用 to_owned()，不要假定 clone 一定复制字符。演示中用 `<&str as Clone>::clone(&text)` 明确选择共享引用的 Clone，结果仍是 &str。泛型中尤其要注意 T 与 &T 的不同，方法解析也可能自动解引用。

来源：[Clone](https://doc.rust-lang.org/std/clone/trait.Clone.html)。

## 3. Copy 与 copied 不是同一层东西

Copy 是标记 trait，表示值可以用简单位复制重复取得，例如 i32、bool、char、共享引用。String 不是 Copy，否则重复其拥有指针而不维护所有权会出问题。

Copy: Clone，因此实现 Copy 必须也实现 Clone；反过来不成立。Copy 不提供 copied() 或 copy() 方法。是否能调用 copied，取决于迭代器/Option 等接收类型及约束。

来源：[Copy](https://doc.rust-lang.org/std/marker/trait.Copy.html)。

## 4. Iterator::copied 与 Iterator::cloned

这两个是迭代器适配器，不是任意值上的通用方法。

| 当前迭代器输出 | 操作 | 约束 | 新迭代器输出 |
| --- | --- | --- | --- |
| &T | copied() | T: Copy | T |
| &T | cloned() | T: Clone | T |

```rust
let values = vec![1, 2, 3];
let own: Vec<i32> = values.iter().copied().collect();

let words = vec![String::from("rust")];
let own_words: Vec<String> = words.iter().cloned().collect();
```

iter() 分别提供 &i32 与 &String；copied 复制 i32，cloned 调用 String 的 Clone。copied/cloned 本身返回新迭代器，通常等 collect 等消费操作执行时才逐项转换。

String 不满足 Copy，所以 words.iter().copied() 不适用；但 cloned 适用。即使某个值实现 Copy，也不代表它自己有 copied() 方法。

若 T 自己又是引用，copied 结果仍可能是引用。例如从 &&str 复制一层后得到 &str，并没有创建 String；不能把 copied 理解成自动移除所有借用依赖。

来源：[Iterator::copied](https://doc.rust-lang.org/std/iter/trait.Iterator.html#method.copied)、[Iterator::cloned](https://doc.rust-lang.org/std/iter/trait.Iterator.html#method.cloned)。

## 5. Option 也有同名方法

```rust
let number = 7;
let input: Option<&i32> = Some(&number);
let output: Option<i32> = input.copied();

let text = String::from("rust");
let input: Option<&String> = Some(&text);
let output: Option<String> = input.cloned();
```

Some 包含一个值，None 表示没有值。Option 的 copied/cloned 把 Some 内的 &T 转成 T，None 保持 None；约束分别为 T: Copy / T: Clone。它们是 Option 上的方法，不是 Iterator trait 的同一方法，且这里不是惰性迭代器。

来源：[Option::copied](https://doc.rust-lang.org/std/option/enum.Option.html#method.copied)、[Option::cloned](https://doc.rust-lang.org/std/option/enum.Option.html#method.cloned)。

## 6. 如何判断一个方法能不能调用

先确定接收者的具体类型，再查该类型的固有方法或可用 trait 实现，最后检查 where 条件。例如：

- String：实现 Clone，可 clone；没有通用的 String::copied。
- &str：可用 str 的 ToOwned 获得 String；共享引用自身也可被 Copy/Clone，但不等于复制字符。
- iter<Item = &String>：可 cloned；不可 copied，因为元素目标 String 不实现 Copy。
- Option<&i32>：可 copied，结果 Option<i32>。

本课 snapshot 应写 self.text.clone() 或 self.text.as_str().to_owned()，两者均生成独立 String。

## 验证与版本

官方页面在核查时为 std 1.99.1，本机验证使用 rustc 1.98.0、Rust 2024 edition；本页用到的方法在本机均已验证。完整 [conversion-demo.rs](exercises/10-copy-clone-owned/conversion-demo.rs) 编译、运行断言通过，包含 str→String、slice→Vec、String clone、迭代器 copied/cloned、Option copied/cloned、显式共享引用 Clone。

同目录保存 M04-R 综合回访原版和追加借用读取版；前者编译运行通过，后者 E0505。见[实际验证](exercises/10-copy-clone-owned/validation.md)。API 演示由导师编写，不作为学习者独立写出所有 API 的证据。
