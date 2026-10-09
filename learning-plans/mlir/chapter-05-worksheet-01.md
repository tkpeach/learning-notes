# 第 05 章答题稿 01：Operation、Value 与 def-use

请直接在“作答”栏补关键词或短句。示例和提示已提供；不用重抄题目。完成后把文档保存，告诉我已完成，或直接粘贴答案。

## A. 结构层级

贯穿示例：

```mlir
module {
  func.func @compute(%x: i32) -> i32 {
    %a = arith.addi %x, %x : i32
    %b = arith.muli %a, %x : i32
    return %b : i32
  }
}
```

提示：从外向内填写 Operation → Region → Block；函数体 Block 中还有参数和操作。

- `module` 的直接内容：Block
- `func.func` 持有：Operation
- 函数体 Block 参数：%x
- 函数体 Block 中的操作（按顺序）：arith.addi, arith.muli

## B. Operation 各部分

提示：Operand 是输入位置；Result 是 SSA 结果；常量字面值属于 Attribute；Type 标注值的类型。

| IR | Operation 名 | Operands | Results | Type | 显式 Attribute |
| --- | --- | --- | --- | --- | --- |
| `%a = arith.addi %x, %x : i32` |  |  |  |  |  |
| `%c1 = arith.constant 1 : i32` |  |  |  |  |  |

`Location` 的作用（一句话）：题目中好像没有Location，但是Location应该是保存了debug信息

## C. 定义与使用

提示：每个 Operand 位置算一次使用；同一个值出现在两个参数位置，就算两次。

| SSA 值 | 定义来源 | 使用位置 | 使用次数 |
| --- | --- | --- | --- |
| `%x` |  |  |  |
| `%a` |  |  |  |
| `%b` |  |  |  |

在 `arith.addi %x, %x` 中，`%x` 是几个 use？2个

## D. 名称与值

- `%c1` 这个文本名称对应：Operand（提示：MLIR IR 中的值实体）
- 后续操作要使用常量操作的结果，引用：%c1（提示：带 `%` 的 SSA 名称）
- 消费端直接引用 Attribute `1`，还是引用常量操作的 Result？常量操作的 Result

## E. 本段自检

用一句话说明：为什么“一个 SSA 值只定义一次”不代表它只能使用一次？

作答：SSA值定义一次是为了方便后续优化，使用没有这个限制

## 检查反馈（按反馈修订上面的答案）

- A：`module` 的直接内容是 Region（module body），Block 位于 Region 内；`func.func` 持有 Region；函数体操作顺序还要包含最后的 `return`。
- B、C：目前表格仍空着，请补齐。可只写关键字和计数。
- C：Location 可提供源码位置，用于诊断、追踪等；它不等同于“调试信息”，也不一定在普通文本输出中显示。
- D：`%c1` 对应 SSA Value；Operand 是操作中引用 Value 的输入位置。两者相关但不是同一概念。
- E：关键理由是“一次定义”约束定义次数，没有约束使用次数；同一 SSA Value 可以流向多个 Operand/use。SSA 有利于分析和优化是它的好处，不是 use 次数限制的原因。

### 修订作答（只改需要修改或补充的项目）

- A `module` 直接内容：Region ；`func.func` 持有：Region ；函数体操作：arith.addi, arith.muli
- B `arith.addi`：Operands %x, %x ；Result %a ；Type i32 ；显式 Attribute 无
- B `arith.constant`：Operands 无 ；Result %c1 ；Type i32 ；显式 Attribute 1
- B Location：源码位置信息
- C `%x`：定义来源 函数参数 ；使用位置 arith.addi operands；次数 2
- C `%a`：定义来源 %a = arith.addi %x, %x : i32 ；使用位置 arith.muli operand；次数 1
- C `%b`：定义来源 %b = arith.muli %a, %x : i32 ；使用位置 return operand；次数 1
- D `%c1` 对应的 IR 实体：Value
- E 一次定义、可多次使用的原因：SSA值定义一次是为了方便后续优化，使用没有这个限制

### 复核结果

- A 修订时仍漏了 `return`；函数体 Block 的完整操作顺序是 `arith.addi`、`arith.muli`、`return`。
- C `%x` 还被 `arith.muli` 使用一次，因此总计 3 次：`arith.addi` 的两个 Operand 位置，以及 `arith.muli` 的一个 Operand 位置。
- 其余修订项正确。E 可进一步精确表述为：SSA 规定每个值只有一个定义，但允许该值被任意多个 Operand 位置引用；便于优化是 SSA 的优势之一。
