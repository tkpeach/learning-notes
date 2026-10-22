# M04 集中验证 · 2026-10-21

环境：rustc 1.98.0 (88d9e12ae 2026-08-18) (Homebrew)；Rust 2024 edition。完整调用及断言由导师补齐。用户原始提交、仅修正字段访问的隔离版本、完整修复版分别保存；不把导师代码记为学习者独立实现。构建产物位于临时目录并已清理。

## 01-pass

编译退出码：0。

运行退出码：0。

## 01-slice

编译退出码：1。

```text
error[E0515]: cannot return value referencing function parameter `s`
 --> learning-plans/rust-lifetimes/exercises/09-ownership-transfer/attempts/01-slice.rs:1:38
  |
1 | fn slice<'a>(s: String) -> &'a str { s.as_str() }
  |                                      -^^^^^^^^^
  |                                      |
  |                                      returns a value referencing data owned by the current function
  |                                      `s` is borrowed here

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0515`.
```

## 01-transfer

编译退出码：0。

运行退出码：0。

## 02-temporary-original

编译退出码：1。

```text
error[E0716]: temporary value dropped while borrowed
 --> learning-plans/rust-lifetimes/exercises/09-ownership-transfer/attempts/02-temporary-original.rs:2:30
  |
2 | fn main() { let result=label(String::from("  rust  ").as_str()); println!("{result}"); }
  |                              ^^^^^^^^^^^^^^^^^^^^^^^^          -            ------ borrow later used here
  |                              |                                 |
  |                              |                                 temporary value is freed at the end of this statement
  |                              creates a temporary value which is freed while still in use
  |
help: consider using a `let` binding to create a longer lived value
  |
2 ~ fn main() { let binding = String::from("  rust  ");
3 ~ let result=label(binding.as_str()); println!("{result}"); }
  |

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0716`.
```

## 02-borrow-user-fixed

编译退出码：0。

运行退出码：0。

```text
rust
```

## 02-owned-user-attempt

编译退出码：1。

```text
error[E0308]: mismatched types
 --> learning-plans/rust-lifetimes/exercises/09-ownership-transfer/attempts/02-owned-user-attempt.rs:1:37
  |
1 | fn label(input: String) -> String { input.trim() }
  |                            ------   ^^^^^^^^^^^^ expected `String`, found `&str`
  |                            |
  |                            expected `String` because of return type
  |
help: try using a conversion method
  |
1 | fn label(input: String) -> String { input.trim().to_string() }
  |                                                 ++++++++++++

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0308`.
```

## 02-owned-fixed

编译退出码：0。

运行退出码：0。

```text
rust
```

## 03-user-original

编译退出码：1。

```text
error[E0425]: cannot find value `text` in this scope
 --> learning-plans/rust-lifetimes/exercises/09-ownership-transfer/attempts/03-user-original.rs:3:26
  |
3 | fn view(&self) -> &str { text.as_str() }
  |                          ^^^^
  |
help: you might have meant to use the available field
  |
3 | fn view(&self) -> &str { self.text.as_str() }
  |                          +++++

error[E0425]: cannot find value `text` in this scope
 --> learning-plans/rust-lifetimes/exercises/09-ownership-transfer/attempts/03-user-original.rs:4:32
  |
4 | fn snapshot(&self) -> String { text.copied() }
  |                                ^^^^
  |
help: you might have meant to use the available field
  |
4 | fn snapshot(&self) -> String { self.text.copied() }
  |                                +++++

error[E0425]: cannot find value `text` in this scope
 --> learning-plans/rust-lifetimes/exercises/09-ownership-transfer/attempts/03-user-original.rs:5:37
  |
5 | fn into_text(&mut self) -> String { text }
  |                                     ^^^^
  |
help: you might have meant to use the available field
  |
5 | fn into_text(&mut self) -> String { self.text }
  |                                     +++++

error: aborting due to 3 previous errors

For more information about this error, try `rustc --explain E0425`.
```

## 03-view-field-fixed

编译退出码：0。

运行退出码：0。

## 03-snapshot-field-only

编译退出码：1。

```text
error[E0599]: `String` is not an iterator
   --> learning-plans/rust-lifetimes/exercises/09-ownership-transfer/attempts/03-snapshot-field-only.rs:2:58
    |
  2 | impl Document { fn snapshot(&self) -> String { self.text.copied() } }
    |                                                          ^^^^^^ `String` is not an iterator
    |
   ::: /opt/homebrew/Cellar/rust/1.98.0/lib/rustlib/src/rust/library/alloc/src/string.rs:353:1
    |
353 | pub struct String {
    | ----------------- doesn't satisfy `String: Iterator`
    |
    = note: the following trait bounds were not satisfied:
            `String: Iterator`
            which is required by `&mut String: Iterator`
            `str: Iterator`
            which is required by `&mut str: Iterator`

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0599`.
```

## 03-into-field-only

编译退出码：1。

```text
error[E0507]: cannot move out of `self.text` which is behind a mutable reference
 --> learning-plans/rust-lifetimes/exercises/09-ownership-transfer/attempts/03-into-field-only.rs:2:53
  |
2 | impl Document { fn into_text(&mut self) -> String { self.text } }
  |                                                     ^^^^^^^^^ move occurs because `self.text` has type `String`, which does not implement the `Copy` trait
  |
help: consider cloning the value if the performance cost is acceptable
  |
2 | impl Document { fn into_text(&mut self) -> String { self.text.clone() } }
  |                                                              ++++++++

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0507`.
```

## 03-fixed

编译退出码：0。

运行退出码：0。

```text
rust
```
