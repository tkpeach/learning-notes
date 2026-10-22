# 从 MIR 操作到生命周期约束

[学习入口](README.md) · [检查流程](check-workflow.md) · [学习过程](learning-log.md)

## 要回答的精确问题

```rust
fn wrong<'a, 'b>(x: &'a str) -> &'b str {
    x
}
```

为什么此处产生 'a: 'b？不是因为规定“函数参数生命周期必须覆盖返回生命周期”，而是函数返回的语义形成了一个有方向的类型兼容要求，类型关系再根据共享引用的变型规则生成 region 约束。

## 1. 声明先提供类型，不直接宣告覆盖关系

签名声明两个独立生命周期参数，并提供：x 的类型为 &'a str，返回位置要求 &'b str。单凭这个签名，并不能得出 a 覆盖 b。例如相同签名的函数体若返回字符串字面量，输出可以由 static 保证，而不必要求 a 覆盖 b。

因此必须结合函数体实际返回表达式，才能知道应比较哪两个类型。

## 2. 尾表达式降低为返回槽赋值

教学用、保留生命周期名称的 MIR 示意：

```text
_1: &'a str   // 参数 x 对应的局部变量
_0: &'b str   // 返回槽，类型来自函数声明

bb0:
    _0 = copy _1
    return
```

关键操作是 `_0 = copy _1`。Return 终结语句表示结束函数，返回引用类型兼容性的要求已经体现在对返回槽的赋值上。

本机对[带约束的可编译版本](exercises/06-type-relation/forward-with-bound.rs)执行 `rustc --edition=2024 --crate-type lib --emit=mir`，实际得到[文本 MIR](exercises/06-type-relation/forward-with-bound.mir)，确有 `_0 = copy _1; return;`。普通 emit 输出未展示命名生命周期，不把上方生命周期名称宣称为真实 dump 内容，也不把该输出当作借用检查前的 region dump。

## 3. 赋值操作产生子类型要求

对本例这个简单引用拷贝，要求如下：

```text
右侧表达式类型 <: 左侧存放位置类型

type(copy _1) <: type(_0)
&'a str      <: &'b str
```

<: 表示“是其子类型”，此处含义是右侧提供的值可用于左侧要求的位置，不是数值比较。

已核对 Rust 1.98.0 的 type_check/mod.rs：visit_statement 的 StatementKind::Assign 分支读取 place_ty 和 rv_ty，调用 sub_types(rv_ty, place_ty, ...)。赋给 RETURN_PLACE 时会将约束归为 Return，普通赋值则为 Assignment 等类别。类别帮助记录来源和诊断，右侧到左侧的类型关系才是本例方向的来源。

源码：[Rust 1.98.0 MIR 赋值检查](https://github.com/rust-lang/rust/blob/1.98.0/compiler/rustc_borrowck/src/type_check/mod.rs)。检索 visit_statement、StatementKind::Assign、sub_types(rv_ty, place_ty。

## 4. 类型关系递归到引用，生成 outlives 约束

共享引用 &'r T 在 r 上协变。对当前相同被引用类型 str，规则是：

```text
要满足 &'a str <: &'b str
需要满足 'a: 'b
```

因此此例的链条是：

```text
尾表达式 x
  → 降低为给返回槽 _0 赋值
  → RHS 类型 <: LHS 类型
  → &'a str <: &'b str
  → 引用生命周期的协变规则
  → 记录 outlives 约束 'a: 'b
```

解释用伪代码（不是 rustc 原样源码）：

```text
check_assign(destination, expression):
    source_type = type_of(expression)
    target_type = type_of(destination)
    require_subtype(source_type, target_type)

require_subtype(&'a str, &'b str):
    emit_outlives('a, 'b)
```

参考：[Rust Reference：子类型与变型](https://doc.rust-lang.org/reference/subtyping.html)、[rustc 类型推断中的子类型义务与 region 约束](https://rustc-dev-guide.rust-lang.org/type-inference.html)。

官方编译器源码文档的 type_check/relate_tys.rs 中，regions 方法在协变分支调用 push_outlives(a, b, ...)，注释直接解释 &'a u8 <: &'b u8 对应 a: b。此页是滚动的 nightly 文档且抓取版本可能不同于 1.98.0，所以只用作规则的源码佐证，不声称它与上面的稳定版本文件来自同一构建。

[nightly region 类型关系实现](https://doc.rust-lang.org/nightly/nightly-rustc/src/rustc_borrowck/type_check/relate_tys.rs.html)。

## 5. 收集要求不等于能擅自补入 API 契约

函数体需要 a: b，但签名没有显式或可推出的关系。泛型函数必须对满足已声明条件的生命周期参数成立；其中包括 a 不能覆盖 b 的组合。因此实现不满足承诺，编译失败。

编译器不会替用户悄悄加入 a: b，因为这会改变调用者允许的参数关系。显式补成 `fn forward<'a: 'b, 'b>(x: &'a str) -> &'b str` 后，函数体才可以使用这个已知关系。

参考：[通用生命周期参数的关系验证](https://rustc-dev-guide.rust-lang.org/borrow-check/region-inference/lifetime-parameters.html)。

## 6. 用普通局部赋值隔离“参数/返回位置”因素

```rust
fn local_assignment<'a, 'b>(x: &'a str) {
    let src: &'a str = x;
    let _dst: &'b str = src;
}
```

最后一行没有返回引用，目标 _dst 也是普通局部绑定，但依然要求 `&'a str <: &'b str`，产生 a: b。本机实际编译失败，诊断在 `_dst` 类型标注处明确指出 a 必须 outlive b。

若改成把一个 &'b str 表达式赋给 &'a str 目标，则方向反过来，要求 b: a。方向由有向类型关系决定，不由生命周期名字决定。

## 7. 语法位置究竟有没有关系

有关系，但应分成两层：

1. **操作语义**：return、赋值、调用、字段初始化等决定哪一侧提供类型、哪一侧要求类型；省略规则也取决于函数/方法签名形式。降低到 IR 后，这些体现在具体操作和已确定的类型上。
2. **类型结构**：递归比较类型时，变型决定内部参数的约束方向。对本例 &'a str 的外层生命周期是协变；嵌套类型或比较函数指针类型时，不能机械复用同一方向。

这里没有在比较两个 fn 类型，因此不要把“函数类型的参数位置逆变”误套到“检查某个函数体如何返回 x”上。检查 x 是一个引用表达式，而非正在比较整个函数签名的子类型关系。

最终要找的不是“哪个生命周期语法位置天然更长”，而是：哪条 IR 操作触发哪种类型关系，比较到哪层类型构造器时产生了什么约束。

## 验证记录

2026-10-20，rustc 1.98.0、Rust 2024 edition：local-assignment.rs 编译退出码 1，提示 a: b；forward-with-bound.rs 以库形式成功 emit MIR，退出码 0。前者构建产物放入临时目录并已清理；后者仅保留小型文本 MIR 作为教学证据。示意 IR 与实测输出明确区分。

## 8. MIR 是中层 IR，为什么在这里检查

Rust 的 MIR 全称是 Mid-level Intermediate Representation，不是 Machine IR。教学用简化流水线：

```text
源码 → AST/HIR → 类型检查及 THIR → MIR（借用检查）
     → 后续优化、单态化及代码生成 → 机器码
```

这不是完整 pass 顺序，不表示借用检查前没有任何 MIR 变换。重点是借用检查仍位于保留 Rust 类型、引用、移动与销毁语义的中层阶段，并非等到机器指令生成后再判断。

选择 MIR 的原因：高层语法得到简化；分支、循环、临时变量、拷贝/移动与控制流更明确；适合数据流分析和 NLL，而不必为每一种复杂语法各写一套借用检查。编译器需要知道借用在哪些控制流位置仍然有效，这是比局部语法匹配更广的分析。

并非所有生命周期相关问题都等到这一阶段才发现。未声明的生命周期名、输出省略规则无法确定关系等问题可在更早阶段报告；MIR 借用检查承担基于函数体控制流、类型关系和数据流的检查。

参考：[MIR 简介](https://rustc-dev-guide.rust-lang.org/mir/index.html)、[选择 MIR 做借用检查的原因](https://rustc-dev-guide.rust-lang.org/borrow-check.html)。

## 9. 声明、实现和调用分别如何处理生命周期关系

### 9.1 声明：建立参数、类型与已知条件

```rust
fn forward<'a: 'b, 'b>(x: &'a str) -> &'b str {
    x
}
```

声明提供三类信息：

- 绑定通用生命周期参数 a、b。
- 定义输入/输出类型：x 是 &'a str，返回位置要求 &'b str。
- 记录显式界限 a: b。在实现内可作为已知条件，在调用点必须满足。

输入/输出类型落实到 MIR 局部变量与返回槽时，需要与声明保持一致，概念上 type(_1) 对应 &'a str，type(_0) 对应 &'b str。实际 MIR 检查可能使用新编号的 region，再用类型相等关系关联到签名参数，不是靠局部变量名称匹配。

声明两个独立参数不会自动生成 a: b。同一个参数在多处使用则是共享同一个参数，不需要再凭语法猜测方向。此外某些类型的良构性也能提供隐含界限，例如 &'a &'b str 要求 b 覆盖 a；本节示例的普通 &'a str 不会凭空提供 a 与 b 的关系。

参考：[隐含界限](https://rustc-dev-guide.rust-lang.org/traits/implied-bounds.html)。

### 9.2 实现：从操作产生要求，检查能否由条件证明

前文的返回槽赋值生成：

```text
&'a str <: &'b str → a: b
```

现在声明已经给出 a: b，实现的这项要求成立。没有该界限的 wrong 则不成立。这里不能因为某次调用碰巧可以选择合适 a/b，就免除对通用实现的检查。

### 9.3 调用：实例化签名，把条件变成调用者的义务

考虑包装调用者：

```rust
fn caller<'p, 'q>(s: &'p str) -> &'q str {
    forward(s)
}
```

本次调用为 forward 的 a、b 建立实例，教学记为 A、B。不要把它们当作固定等于 p、q；类型匹配只要求满足相应关系，可能允许缩短借用。

实例化后要处理：

```text
形参：&A str
输出：&B str
声明要求：A: B
```

教学用 MIR 示意（A/B/p/q 是补充的类型标注）：

```text
_1: &'p str
_0: &'q str
_0 = forward::<A, B>(copy _1) -> bb1
bb1:
    return
```

对这个调用点分别处理三件事：

| 来源 | 类型/界限要求 | 生成或实例化的 region 关系 |
| --- | --- | --- |
| 实参匹配 | &'p str <: &A str | p: A |
| 被调用者的显式界限 | 实例化 a: b | A: B |
| 调用结果匹配目标 | &B str <: &'q str | B: q |

由传递性得到：p: A: B: q，因此需要 p: q。caller 原声明没有给出这个条件，所以编译失败。改成 `fn caller<'p: 'q, 'q>(s: &'p str) -> &'q str` 后成立。

函数声明中的界限，在被调用者实现内是可使用的假设，在调用处是要证明的义务。这一区分是避免把“声明了”和“自动满足了”混在一起的关键。

### 9.4 没有显式界限、输入输出共用一个参数时

```rust
fn identity<'a>(x: &'a str) -> &'a str { x }
```

一次调用用 R 实例化 a，则在同样的 caller 环境下：

```text
实参匹配：&'p str <: &R str → p: R
输出匹配：&R str <: &'q str → R: q
所以仍需 p: q
```

两个输入共用 a 时，再分别生成每个实参 region 覆盖 R 的关系；这正是 earlier first 示例中第二个参数也能约束调用结果的原因。

### 9.5 实现入口与证据

公开的 MIR 类型检查源码中：check_call_inputs 对实参类型与形参类型调用 sub_types(op_arg_ty, fn_arg, ...)；check_call_dest 对签名输出与接收位置调用 sub_types(sig.output(), dest_ty, ...)。界限满足也属于泛型调用的检查义务，最终涉及 region 约束转换/求解，并非靠方法名识别谁长谁短。

参考：[调用输入/输出的类型检查源码](https://doc.rust-lang.org/nightly/nightly-rustc/src/rustc_borrowck/type_check/mod.rs.html)、[界限在使用时须满足](https://doc.rust-lang.org/reference/trait-bounds.html)。nightly 是滚动文档，不将其源码行号说成本机版本行号。

2026-10-20 本机验证：exercises/07-call-constraints/caller-missing-bound.rs 以库形式编译退出码 1，提示 p: q；caller-with-bound.rs 补上后 emit MIR 退出码 0，保存 caller-with-bound.mir。实际调用操作为 `_0 = forward::<'_, '_>(copy _1) -> ...`，普通 emit 输出没有显示 A/B 的具体 region 约束。所有教学推导与实际 dump 内容明确区分。
