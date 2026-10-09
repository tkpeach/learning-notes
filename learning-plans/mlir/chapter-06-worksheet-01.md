# 第 06 章答题稿 01：函数、符号与 signless 整数

请填关键词、类型或预测结果即可。本答题稿先考察结构和语义预测；工具实际执行状态单独记录。

## A. 函数符号与 SSA 值

```mlir
module {
  func.func @inc(%x: i32) -> i32 {
    %one = arith.constant 1 : i32
    %result = arith.addi %x, %one : i32
    return %result : i32
  }

  func.func @caller(%x: i32) -> i32 {
    %result = func.call @inc(%x) : (i32) -> i32
    return %result : i32
  }
}
```

- 定义 `@inc` 的 Operation：func.func
- `func.call` 中的 `@inc` 是 SymbolRef 还是 SSA 值？SymbolRef
- 调用参数 `%x` 是 SymbolRef 还是 SSA 值？SSA 值
- `func.call` 返回的 SSA Result 名：%result ；Result Type：i32
- `%one` 的定义来源：arith.constant；常量 Attribute：1；Type：i32
- 如果把调用目标改成 `@missing`，应检查的问题：SymbolRef无法查找到符号

## B. 比较同一位模式的两种解释

```mlir
%minus1 = arith.constant -1 : i32
%one = arith.constant 1 : i32
%signed = arith.cmpi slt, %minus1, %one : i32
%unsigned = arith.cmpi ult, %minus1, %one : i32
```

- `i32` 本身固定表示有符号还是无符号？有符号
- `slt`（signed less-than）比较结果预测：true
- `ult`（unsigned less-than）比较结果预测：false
- `-1` 的 i32 二进制位模式（可写十六进制）：0xFFFFFFFF
- unsigned 解释下 `%minus1` 对应的十进制数：0xFFFFFFFF的十进制
- 两个比较结果为什么不同？%minus1按照有符号/无符号解释
- 比较操作的结果类型：boolean

## C. 类型/属性/结果快速区分

在 `%signed = arith.cmpi slt, %minus1, %one : i32` 中：

- Operation：arith.cmpi
- Predicate Attribute：slt
- Operand：arith.cmpi
- Result：signed
- Result Type：boolean
