# 综合回访与转换 API 验证 · 2026-10-21

环境：rustc 1.98.0，Rust 2024 edition。导师补齐完整源码。借用综合题在学习者作答后验证；转换 API 示例为导师讲义演示。临时构建产物已清理。

## review-original

编译退出码：0。

运行退出码：0。

```text
rust
rust
```

## review-later-use

编译退出码：1。

```text
error[E0505]: cannot move out of `doc` because it is borrowed
  --> learning-plans/rust-lifetimes/exercises/10-copy-clone-owned/review-later-use.rs:11:7
   |
 7 |  let doc=Document{text:String::from("rust")};
   |      --- binding `doc` declared here
 8 |  let borrowed=doc.view();
   |               --- borrow of `doc` occurs here
...
11 |  drop(doc);
   |       ^^^ move out of `doc` occurs here
12 |  println!("{saved}");
13 |  println!("{borrowed}");
   |             -------- borrow later used here
   |
note: if `Document` implemented `Clone`, you could clone the value
  --> learning-plans/rust-lifetimes/exercises/10-copy-clone-owned/review-later-use.rs:1:1
   |
 1 | struct Document { text: String }
   | ^^^^^^^^^^^^^^^ consider implementing `Clone` for this type
...
 8 |  let borrowed=doc.view();
   |               --- you could clone this value

error: aborting due to 1 previous error

For more information about this error, try `rustc --explain E0505`.
```

## conversion-demo

编译退出码：0。

运行退出码：0。

```text
to_owned/clone/copied/cloned assertions passed
```
