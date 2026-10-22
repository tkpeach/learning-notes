# 第 09 章集中练习：遍历、创建与验证 IR

这次以改 C++ 代码和检查输出为主，不复述讲义段落。工程骨架在当前目录：`CMakeLists.txt`、`main.cpp`。先自己完成 TODO，再填下面的简要记录。

## 开始前：本机 API 速查

版本：LLVM/MLIR 22.1.8。下面是实现 TODO 所需的调用形态；它说明 API 如何使用，但不提供完整计数函数或完整函数体。

| 任务 | 用法形态 | 声明/查找位置 |
| --- | --- | --- |
| 遍历模块内 Operation | `module.walk([&](mlir::Operation *op) { /* inspect */ });` | `mlir/IR/Operation.h`；ModuleOp 包含 Operation walk 能力 |
| 判断/取得类型化 Op | `llvm::isa<mlir::arith::AddIOp>(op)`；或 `if (auto add = llvm::dyn_cast<mlir::arith::AddIOp>(op)) { ... }` | `mlir/Support/LLVM.h`、`llvm/Support/Casting.h`；类型化 Arith Op 在 `mlir/Dialect/Arith/IR/Arith.h` |
| 创建函数类型 | `builder.getFunctionType({inputTypes...}, {resultTypes...})` | `mlir/IR/Builders.h` |
| 创建 `func.func` | `builder.create<mlir::func::FuncOp>(loc, "name", functionType)` | `mlir/Dialect/Func/IR/FuncOps.h` |
| 按签名创建 entry Block | `mlir::Block *entry = function.addEntryBlock();` | FuncOp 实现 FunctionOpInterface；可从 `mlir/Interfaces/FunctionInterfaces.h.inc` 查到接口声明 |
| 设定创建位置 | `builder.setInsertionPointToStart(entry);` | `mlir/IR/Builders.h` |
| 取得第一个函数参数 | `entry->getArgument(0)` | `mlir/IR/Block.h` |
| 用 Builder 创建具体 Op | `builder.create<OpType>(loc, operands...)` | `mlir/IR/Builders.h` 和各 Dialect 的 Op 声明 |
| 验证并打印 | `mlir::verify(module.getOperation())`；`module.print(llvm::outs())` | `mlir/IR/Verifier.h`、`mlir/IR/Operation.h` |

可以在安装头文件中直接搜索，不必靠猜名字：

```sh
rg -n 'walk\(' /opt/homebrew/opt/llvm@22/include/mlir/IR/Operation.h
rg -n 'addEntryBlock' /opt/homebrew/opt/llvm@22/include/mlir/Interfaces/FunctionInterfaces.h.inc
rg -n 'create\(.*FunctionType' /opt/homebrew/opt/llvm@22/include/mlir/Dialect/Func/IR/FuncOps.h.inc
```

典型创建顺序是先定函数签名、创建函数和 entry Block、把 Builder 插入该 Block，再创建 body Operations 和 terminator。每次 `builder.create` 都要确认当前插入点正确、operands 已定义且类型匹配。

## 环境与构建

本机已确认 LLVM/MLIR 22.1.8、MLIR CMake 配置、头文件、MLIR 库和 CMake 均存在。执行目录是仓库根目录：

```sh
cmake -S learning-plans/mlir/exercises/chapter-09 \
  -B /tmp/mlir-chapter-09-build \
  -DLLVM_DIR=/opt/homebrew/opt/llvm@22/lib/cmake/llvm \
  -DMLIR_DIR=/opt/homebrew/opt/llvm@22/lib/cmake/mlir
cmake --build /tmp/mlir-chapter-09-build
```

如果 CMake 找不到配置文件，先确认 `LLVM_DIR` 和 `MLIR_DIR` 指向 22.1.8 的 `lib/cmake/llvm` 与 `lib/cmake/mlir`，不要混用 21 与 22 的头文件和库。

## 1. 给陌生 IR 计数

输入已嵌入 `main.cpp`：`@mix` 中有两条 `arith.addi` 和一条 `arith.muli`；`@difference` 还包含一条 `arith.subi`。在 `countTargetOps` 中完成遍历与类型筛选。

运行：

```sh
/tmp/mlir-chapter-09-build/chapter09_exercises count
```

```text
输出：________________
你用什么条件分别识别两类 Op？________________
为什么 `arith.subi` 和 `func.return` 不会增加计数？________________
```

## 2. 用 Builder 创建函数，再迁移一次

先完成 `buildAddOne`，生成 `i32 @add_one(i32)`，函数返回参数加 1。运行：

```sh
/tmp/mlir-chapter-09-build/chapter09_exercises build \
  > /tmp/mlir-chapter-09-add-one.mlir
mlir-opt --verify-each /tmp/mlir-chapter-09-add-one.mlir -o /dev/null
```

```text
构造顺序：Module → FuncOp → entry Block → 运算/常量 → ReturnOp
实际打印的函数签名：________________
verifier 退出码：____
```

**迁移题：**不要复制另一个完整函数。把生成目标改为 `i32 @triple(i32)`，返回参数乘以 3；修改函数名、常量和运算 Op，重新构建并验证。

```text
迁移时改动的三个 IR 要素：________________
第二次 verifier 退出码：____
哪些 Builder/类型/插入点代码可以保留？________________
```

## 3. 生命周期与修改边界

针对程序中的对象，各用一句话说明：

```text
谁拥有解析得到的 module？________________
`module.walk` 回调拿到的 Op wrapper 是所有者还是借用句柄？________
`buildAddOne` 返回后，Builder 和 Module 的生命周期关系是什么？________________
如果在遍历时删除当前 Operation，至少需要额外考虑什么？________________
```

## 4. 结果分层

```text
计数程序的输出证明：________________
`mlir-opt --verify-each` 通过证明：________________
它们都不能单独证明：________________
```

## 5. 费曼复述：用自己的话教回来

先暂时不看讲义，用 3—5 句话向一位刚学 MLIR 的同学解释本章的核心流程。请用练习中一个新例子串起结构遍历或 IR 构造，并说明为什么类型化 Op wrapper 不拥有 Operation。

```text
我的讲解（可简短）：
____________________________________________________________
____________________________________________________________

导师追问/发现的一个边界或漏洞：
____________________________________________________________

修正后的关键句：
____________________________________________________________
```

这不是背讲义：若解释和练习中的代码行为不一致，先指出是哪一条理解需要修正，再改代码或用新例子验证。

## 导师核对区

待学习者完成后填写；不要提前查看答案。
