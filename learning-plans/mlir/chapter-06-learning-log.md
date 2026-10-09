# 第 06 章：基础 Dialect、类型、属性与符号

状态：学习进行中。

## 本章路线

1. 阅读 `func` 与 `arith` 的基础操作，区分 Operand、Result、Type 和 Attribute。
2. 学会函数符号 `@name`、直接调用 `func.call` 与 SSA 值 `%name` 的区别。
3. 理解 MLIR 标准整数类型是 signless；比较操作通过 predicate 选择 signed/unsigned 解释。
4. 完成函数调用、未定义符号诊断和 signed/unsigned 比较练习。
5. 逐行阅读新函数，说明运算语义选择，并整理本章验收记录。

## 工具与资料

- 学习当时未通过 PATH 发现 `mlir-opt`；2026-10-09 配置了已有 Homebrew LLVM 22.1.8 的 PATH，之后补做了本章 IR 解析、符号诊断和常量折叠。
- 官方参考：`func` Dialect、`arith` Dialect、Symbols and Symbol Tables。

## 第 1 段：函数符号、调用与值的类型

教学方式调整：先完成结构化讲解，再集中练习；之前准备的答题稿 01 暂作为讲解后的检查材料，不要求在讲解中途立即作答。

### 讲解示例

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

- `@inc` 是 SymbolRef 对应的函数名，由 `func.func` 定义；`func.call` 通过符号引用找到 callee。
- `%x`、`%one`、`%result` 是 SSA 值；它们不是函数名。
- `i32` 是类型。常量操作中的 `1` 是 Attribute；`%one` 是常量操作产生的 SSA Result。
- 直接调用的输入和返回类型要与被调函数签名一致。改成未定义的 `@missing` 会造成符号解析问题。

### 学习记录

- 学习者回答与反馈：待填写
- 工具验证：待执行/待环境确认

## 答题稿 01 复核

- 函数符号与 SSA 值部分正确：`@inc` 是 SymbolRef，`%x` 是 SSA 值；未解析 `@missing` 应检查符号查找。
- signed/unsigned 预测正确，但需修正：本题中的 `i32` 是 signless；`0xFFFFFFFF` 按 unsigned 解释的十进制数是 `4294967295`；`arith.cmpi` 结果类型是 `i1`（1-bit integer/布尔条件），不是写作 `boolean` 的独立 MLIR Type。
- `arith.cmpi` 快速标注：两个 Operand 是 `%minus1` 和 `%one`；Result 是 `%signed`；`slt` 是 Predicate Attribute。
- 结果状态：概念练习完成，答案经反馈修正。后续使用 LLVM 22.1.8 的 `mlir-opt --canonicalize` 成功解析 inc/caller 与比较函数，并将 signed 比较折叠为 `true`、unsigned 比较折叠为 `false`；将 callee 改为 `@missing` 时 verifier 报告它不是有效函数引用。此为 IR 变换/验证，不是函数数值执行。
