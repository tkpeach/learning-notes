# 第 05 章：Operation、Region、Block 与 SSA

状态：学习进行中。本文从第二部分开始记录学习材料、练习过程和验收结果；尚未完成的内容不记为已掌握。

学习节奏调整：单次学习覆盖一组相关概念并集中反馈；多项或较长练习使用独立答题文档，提供短提示和填空格式，学习者填写关键结论即可。

## 章节路线

1. 建立 SSA 与控制流阅读基础，准备贯穿示例。
2. 看懂 Operation、Region、Block 的包含关系及 Operation 的组成部分。
3. 追踪 Value 的定义、使用、作用域与支配关系；完成定义和使用练习。
4. 观察并修复跨 Region 引用；用 `scf.if` 结果和 `scf.yield` 传递值。
5. 用新例子完成合法性判断和支配关系验收。

## 第 1 段：SSA 与控制流阅读基础

### 本段目标

- 能区分一个 SSA 值的定义与使用。
- 知道函数入口参数也是可供操作使用的 SSA 值。
- 知道 SSA 名字是文本表示中的标签，不是可变变量。
- 为后续结构树和数据依赖分析准备同一段 IR 示例。

### 工具与版本记录

- 学习当时未通过 PATH 发现 `mlir-opt`，所以对应练习只做了人工追踪；2026-10-09 回溯检查发现 Homebrew 已安装 LLVM 21/22，之前只是其 keg-only bin 目录未加入 PATH。后续工具环境已配置，不能把配置后的验证倒记为当时已验证。
- 计划使用 MLIR Compiler Explorer：https://mlir.godbolt.org/ 。打开页面仅能确认 Compiler Explorer 页面可访问；本次未确认其实际 MLIR 编译器条目、版本或运行结果。使用前仍需记录实际选择的工具和版本。

### 贯穿示例

```mlir
module {
  func.func @compute(%x: i32) -> i32 {
    %a = arith.addi %x, %x : i32
    %b = arith.muli %a, %x : i32
    return %b : i32
  }
}
```

### 学习记录

- 学习者的标注与解释：`%x` 是函数参数，在 `arith.addi` 中使用两次、在 `arith.muli` 中使用一次，共三次；`%a` 是第一条算术操作的结果，在 `arith.muli` 中使用一次；`%b` 是第二条算术操作的结果，在 `return` 中使用一次。
- 反馈：标注正确。原回答中的 `arith.multi` 按示例应为 `arith.muli`。
- 验证方式和结果：本步为人工数据流追踪，尚未进行该练习的 MLIR 工具解析验证；本机工具当时因 PATH 不可见，现已配置 LLVM 22 PATH。
- 尚未解决的问题：继续学习 Operation、Region、Block 的结构与组成。

## 第 2 段：IR 结构层级

### 示例的结构树

```text
module operation
└── region
    └── block
        └── func.func @compute operation
            └── region
                └── block (argument: %x)
                    ├── arith.addi operation (result: %a)
                    ├── arith.muli operation (result: %b)
                    └── return operation
```

### 学习记录

- 学习者对结构层级的复述：待填写
- 问题与反馈：待填写

### 学习者回答与反馈

- 回答：`func.func` 包含函数体 Region；`%x` 是 Block 参数。
- 反馈：正确。
- 尚未解决的问题：继续区分 Operation 的 Operand、Result、Type、Attribute 与 Location。

### Operation 组成标注

- 学习者回答：Operation 名 `arith.addi`；Operands `%x, %x`；Result `%a`；Type `i32`；无显式 Attribute。
- 反馈：概念标注正确；“Operandsk”为输入笔误，应为“Operands”。
- 验证方式和结果：文本阅读与人工标注；无机器验证。

### Attribute 与 SSA Result

- 学习者回答：在 `%c1 = arith.constant 1 : i32` 中，Result 是 `%c1`、Attribute 是 `1`、Type 是 `i32`；消费端引用 SSA 值。
- 反馈：正确。若后续操作使用该常量，会写 `%c1`；原贯穿示例的 `arith.addi` 则使用 `%x`，与常量示例无关。
- 尚未解决的问题：区分文本 SSA 名称与 Value、def-use 关系及 Region 的可见范围。

### 答题稿 01 复核

- Operation/Value/Attribute 的基本区分正确。
- 修订反馈：函数体操作列表应包括 `return`；`%x` 的总 use 数是 3（`arith.addi` 两个 Operand + `arith.muli` 一个 Operand）。
- Location 应理解为源码位置信息，可用于诊断与追踪，不等同于调试信息。
- 验证方式和结果：人工审阅答题稿；未进行 MLIR 工具解析验证。

## 第 3 段：Region 边界、支配与控制流表示

带结果的 `scf.if` 由父 Operation 持有分支 Region。分支内定义的 SSA Value 不能直接在 Region 外使用；分支通过 `scf.yield` 把值交给 `scf.if`，父 Operation 再产生外部可用的结果。各分支 yield 的值数量和类型需与父操作结果匹配。

支配关系适用于 SSACFG 控制流路径：若存在一条到达 use 的路径没有经过 def，则 def 不支配 use。Graph Region 不以普通 CFG 的 Block 边表达控制流，重点是操作间依赖，不能机械套用前驱/后继 Block 术语。

- 练习文档：[chapter-05-worksheet-02.md](chapter-05-worksheet-02.md)
- 学习者回答与反馈：能正确判断跨 Region 引用不合法，并说明定义绕过路径时不支配 use；已反馈需通过父 `scf.if` 结果 `%v` 传递，并补全 SSACFG/Graph Region 特征。
- 资料核对：[MLIR Language Reference](https://mlir.llvm.org/docs/LangRef/) 说明 SSACFG 表达 Block 间控制流，Graph Region 不要求 Block 控制流、限单 Block，且可表达循环依赖。

## 第 4 段：综合验收

- 答题文档：[chapter-05-worksheet-03.md](chapter-05-worksheet-03.md)
- 目标：综合标注 Operation/Region/Block、Value 与 def-use，判断跨 Region 合法性和支配关系，并说明 SSACFG 与 Graph Region。
- 执行验证状态：综合片段最初为人工阅读题；本机 LLVM 22 PATH 后续配置成功。该综合片段本身仍未逐条交给 verifier 验证。
- 学习者回答与反馈：待填写
