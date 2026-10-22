# M03 导师验证记录

环境：2026-10-20，rustc 1.98.0，Rust 2024 edition。完整函数和 main 由导师根据提交补齐；不是学习者独立编写全部实现的证据。原题、尝试与修复版本分文件保存。构建产物位于临时目录并已清理。

## 01-a

编译退出码：0。

运行退出码：0。

```text
message
```

## 01-b

编译退出码：1。

```text
error[E0597]: `owner` does not live long enough
 --> learning-plans/rust-lifetimes/exercises/08-application/attempts/01-b.rs:5:54
  |
5 |  { let owner = String::from("message"); view = build(owner.as_str(), "note"); }
  |        -----                                         ^^^^^                    - `owner` dropped here while still borrowed
  |        |                                             |
  |        binding `owner` declared here                 borrowed value does not live long enough
6 |  println!("{}", view.text);
  |                 --------- borrow later used here

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0597`.
```

## 02-original

编译退出码：1。

```text
error[E0425]: cannot find value `text` in this scope
 --> learning-plans/rust-lifetimes/exercises/08-application/attempts/02-original.rs:2:45
  |
2 | impl<'a> View<'a> { fn raw(&self) -> &str { text } }
  |                                             ^^^^
  |
help: you might have meant to use the available field
  |
2 | impl<'a> View<'a> { fn raw(&self) -> &str { self.text } }
  |                                             +++++

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0425`.
```

## 02-external-fixed

编译退出码：0。

运行退出码：0。

## 02-owned-accessor

编译退出码：0。

运行退出码：0。

## 03-original

编译退出码：1。

```text
error[E0515]: cannot return value referencing local variable `message`
 --> learning-plans/rust-lifetimes/exercises/08-application/attempts/03-original.rs:3:2
  |
3 |  message.as_str()
  |  -------^^^^^^^^^
  |  |
  |  returns a value referencing data owned by the current function
  |  `message` is borrowed here

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0515`.
```

## 03-owned-fixed

编译退出码：0。

运行退出码：0。

```text
Hello, Rust!
```

## 04-original

编译退出码：0。

运行退出码：0。

```text
rust
rust!
```

## 01-a-constrained

编译退出码：1。

```text
error[E0597]: `note` does not live long enough
 --> learning-plans/rust-lifetimes/exercises/08-application/attempts/01-a-constrained.rs:5:76
  |
5 |  { let note = String::from("temporary note"); view = build(owner.as_str(), note.as_str()); }
  |        ----                                                                ^^^^            - `note` dropped here while still borrowed
  |        |                                                                   |
  |        binding `note` declared here                                        borrowed value does not live long enough
6 |  println!("{}", view.text);
  |                 --------- borrow later used here

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0597`.
```

## 02-self-contract

编译退出码：1。

```text
error[E0597]: `view` does not live long enough
 --> learning-plans/rust-lifetimes/exercises/08-application/attempts/02-self-contract.rs:5:55
  |
5 |  { let view = View { text: owner.as_str() }; result = view.raw(); }
  |        ----                                           ^^^^        - `view` dropped here while still borrowed
  |        |                                              |
  |        binding `view` declared here                   borrowed value does not live long enough
6 |  assert_eq!(result, "message");
  |  ----------------------------- borrow later used here

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0597`.
```

## 04-later-use

编译退出码：1。

```text
error[E0502]: cannot borrow `owner` as mutable because it is also borrowed as immutable
 --> learning-plans/rust-lifetimes/exercises/08-application/attempts/04-later-use.rs:6:2
  |
4 |  let view = View { text: owner.as_str() };
  |                          ----- immutable borrow occurs here
5 |  println!("{}", view.text);
6 |  owner.push_str("!");
  |  ^^^^^^^^^^^^^^^^^^^ mutable borrow occurs here
7 |  println!("{owner}");
8 |  println!("{}", view.text);
  |                 --------- immutable borrow later used here

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0502`.
```
