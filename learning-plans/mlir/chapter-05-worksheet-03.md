# 第 05 章答题稿 03：综合验收

只填关键词或短句。示例用于人工阅读，不要求机器执行。

## A. 分析同一段 IR

```mlir
func.func @combine(%cond: i1, %x: i32) -> i32 {
  %v = scf.if %cond -> (i32) {
    %a = arith.addi %x, %x : i32
    scf.yield %a : i32
  } else {
    %b = arith.muli %x, %x : i32
    scf.yield %b : i32
  }
  %r = arith.addi %v, %x : i32
  return %r : i32
}
```

- 函数体 Block 参数：%cond, %x
- 函数体顶层的操作（按顺序）：scf.if, rith.addi, return
- `scf.if` 包含的 Region 数：2
- `%a` 和 `%b` 分别在哪里定义？then Region, else Region
- 哪个 Operation 把分支值变成外层可用的结果？其 Result 是：scf.if, %v
- `%x` 的 Operand use 总次数：5（提示：逐个 Operand 位置计数）
- `%v` 的定义来源、使用位置：%v = scf.if, %r = arith.addi %v, %x : i32
- 直接把 `return %a : i32` 放在函数外层是否合法？原因：否，函数需要一个返回值

## B. 判断支配

控制流示意（伪图，不是可执行 MLIR）：

```text
          ┌──> then: 定义 %d ──┐
entry ────┤                    ├──> join: 使用 %d
          └──> else ───────────┘
```

- `%d` 支配 join 中的使用吗？ 否
- 判断依据：从else分支可以到达join，但是未定义%d
- 一种修复思路：定义%d在entry（提示：把分支计算结果沿控制流边传到 join）

## C. 一句话总结

- 结构树与数据流图分别回答什么问题？前者是逻辑结构，后者是数据结构
- SSACFG 与 Graph Region 的关键区别：

## 检查反馈

- A：顶层操作中 `rith.addi` 是拼写遗漏，应为 `arith.addi`。`%x` 的 5 次 use 计数正确。
- A：`return %a` 不合法的关键原因是 `%a` 只在 then Region 中定义，外层不可见；应经 `scf.yield` 交给父 `scf.if`，再使用外层结果 `%v`。函数返回值要求是签名约束，但不是此处跨 Region 错误的核心。
- B：不支配判断正确，因为 else 路径绕过 `%d` 的定义。若分支只在 then 计算 `%d`，一般应将 then/else 的值作为前驱分支参数传给 join block（或在结构化写法中通过 yield/result 传递）；只有在值确实可提前无条件计算时，才可把定义移到 entry。
- C：结构树回答“谁包含谁”，数据流图回答“值从哪里定义、被哪些操作使用”；SSACFG/Graph 的区别参考上一答题稿反馈。

第 05 章综合验收：人工阅读部分完成，核心概念达标；工具 verifier 验收待本地 MLIR 环境确认。
