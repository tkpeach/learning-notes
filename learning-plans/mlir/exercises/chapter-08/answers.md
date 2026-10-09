# 第 08 章集中练习：Tensor、MemRef 与 Affine

填写关键结论即可；不用抄写题目。可以直接编辑本文件。配套 MLIR 文件位于本目录：`01_tensor.mlir`、`02_memref.mlir`、`03_affine.mlir`。

## 1. Tensor：更新前后的值

运行 `01_tensor.mlir` 后，手工沿 SSA 值追踪：

```text
%t 表示：________
%t2 表示：________
返回的 %old = ____，%new = ____
tensor.insert 是否改写了 %t？____；理由：________________
```

## 2. MemRef：写入与生命周期

运行 `02_memref.mlir` 后填写：

```text
第一次 store 后的两个元素：________
第二次 store 后的两个元素：________
第三次 store 后的两个元素：________
load 读到：____
memref.store 是否产生 SSA 结果 / 新 memref？________
读取发生在 dealloc 之前吗？____；为什么需要注意顺序？________
与 tensor.insert 最关键的语义差别：________________
```

## 3. Affine map：输入分类与求值

对应 `03_affine.mlir`：

```text
d0、d1 绑定到：________、________
s0 绑定到：________
当 %i=2、%j=3、%N=10 时，结果为：________
%N 必须是编译期常数吗？____；这里称为 symbol 的原因：________
```

判断下面表达式能否放进普通 affine expression，并简述原因：

| 表达式 | 合法？ | 一句话理由 |
| --- | --- | --- |
| `2*d0 + d1 + 3` | ____ | ____ |
| `d0*d1` | ____ | ____ |
| `d0 floordiv 4` | ____ | ____ |
| `d0 floordiv s0` | ____ | ____ |

## 4. 验证记录

按环境记录使用 LLVM/MLIR 22.1.8。执行目录为仓库根目录：

```sh
mlir-opt --verify-each learning-plans/mlir/exercises/chapter-08/01_tensor.mlir -o /dev/null
mlir-opt --verify-each learning-plans/mlir/exercises/chapter-08/02_memref.mlir -o /dev/null
mlir-opt --verify-each learning-plans/mlir/exercises/chapter-08/03_affine.mlir -o /dev/null
```

如果当前终端没加载 PATH，可将 `mlir-opt` 换为 `/opt/homebrew/opt/llvm@22/bin/mlir-opt`。

```text
三个命令退出码：____ / ____ / ____
这是哪一层验证（解析验证 / Pass 变换 / 数值执行 / 性能测量）：________
它能证明：________________
它不能单独证明：________________
```

语义预期（尚不等于执行结果）：Tensor 返回 `(1, 9)`；MemRef load 读到 `9`；Affine 输入 `2,3,10` 时计算 `24`。若需要报告真实数值，必须实际执行程序并记录运行工具和输出；`mlir-opt --verify-each` 只负责解析/验证此处的 IR。

## 5. 本章验收

```text
Tensor 是在构造新值还是原地修改？________
MemRef 的 store 对什么产生影响？________
shape 描述什么；layout/stride 描述什么？________________
verifier 通过为什么不等于证明所有索引运行时都安全？________________
```
