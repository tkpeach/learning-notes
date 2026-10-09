# 第 05 章答题稿 02：Region 边界、支配与控制流

请直接在空格中补关键词或短句。答完保存并告诉我已完成。

## 1. 看懂带结果的 `scf.if`

```mlir
func.func @choose(%cond: i1) -> i32 {
  %v = scf.if %cond -> (i32) {
    %left = arith.constant 7 : i32
    scf.yield %left : i32
  } else {
    %right = arith.constant 9 : i32
    scf.yield %right : i32
  }
  return %v : i32
}
```

- `scf.if` 包含几个分支 Region？2
- `%left` 定义在哪个分支？它由什么传出 Region？if分支，由scf.yield到%v传出
- `%right` 定义在哪个分支？它由什么传出 Region？else分支，由scf.yield到%v传出
- 两个 `scf.yield` 的值类型应满足什么要求？i32的兼容类型
- 外层 `return` 使用的是分支内的 `%left`/`%right`，还是 `scf.if` 的结果？`scf.if` 的结果

## 2. 判断非法跨 Region 引用

假设在上面的 `return` 中写 `return %left : i32`：

- 问题：%left仅在if region中定义，如果else region则没有定义（提示：定义所在 Region 与使用位置）
- 最小修正：应该使用例子中的赋值形式（提示：使用父 Operation 的结果）

## 3. 支配关系与控制流

- 在同一 Block 中，普通操作结果要供后续操作使用，定义通常必须在使用之前：是/否 是
- 若某条控制流路径能到达 use，却没有经过 def，这个 def 支配该 use 吗？否
- 用一句话解释支配关系：从根节点到达被支配节点的路径，必然经过支配节点

## 4. SSACFG Region 与 Graph Region

提示：SSACFG 以 Block 和控制流边表达路径；Graph Region 以操作间的数据依赖组织，不直接表达普通分支/跳转 CFG。

- SSACFG 的控制流结构主要由什么组成？不知道
- Graph Region 更直接表达什么关系？不知道
- 读 Graph Region 时，为什么不能机械套用“前驱 Block/后继 Block”？因为是个更加通用的图，不保证无环

## 检查反馈

- `scf.if` 的两个 `scf.yield` 都把各自分支的值交给父 `scf.if`；外层得到统一结果 `%v`。对这个例子，yield 类型须与声明的结果类型 `i32` 相同。
- `%left` 仅在 then Region 内定义，外层不能引用；修正时用 `return %v : i32`，其中 `%v` 是父 Operation 的 Result。
- 支配关系的解释正确：到达 use 的每条控制流路径都要经过 def。若有一条路径绕过 def，则 def 不支配 use。
- SSACFG 的主要组成漏答：Block 与 Block 之间的控制流边（由终结操作引出）。
- Graph Region 的数据依赖组织漏答：Operation 是节点，Value 是连接定义操作与一个或多个使用位置的边。Graph Region 目前限制为单个 Block，不表示普通控制流；操作顺序不具控制流含义。它可以包含循环依赖，因此“可能有环”这一点答对了。

## 复核完成

概念练习完成。下一步用一个综合例子检查结构、def-use、支配与 Region 传值。MLIR 工具验证仍待后续环境确认。
