# 第 08 章集中练习：Tensor、MemRef 与 Affine

填写关键结论即可；不用抄写题目。可以直接编辑本文件。配套 MLIR 文件位于本目录：`01_tensor.mlir`、`02_memref.mlir`、`03_affine.mlir`。

## 1. Tensor：更新前后的值

运行 `01_tensor.mlir` 后，手工沿 SSA 值追踪：

```text
%t 表示：tensor初始化结果
%t2 表示：tensor修改后结果
返回的 %old = 1，%new = 9
tensor.insert 是否改写了 %t？没有；理由：SSA不能多次赋值
```

## 2. MemRef：写入与生命周期

运行 `02_memref.mlir` 后填写：

```text
第一次 store 后的两个元素：1, ?
第二次 store 后的两个元素：1, 2
第三次 store 后的两个元素：9, 2
load 读到：9
memref.store 是否产生 SSA 结果 / 新 memref？false
读取发生在 dealloc 之前吗？是；为什么需要注意顺序？dealloc后读取会产生undefined behavior
与 tensor.insert 最关键的语义差别：tensor相关为赋值语义，memref为直接操作存储
```

## 3. Affine map：输入分类与求值

对应 `03_affine.mlir`：

```text
d0、d1 绑定到：%i、%j
s0 绑定到：%N
当 %i=2、%j=3、%N=10 时，结果为：24
%N 必须是编译期常数吗？false；这里称为 symbol 的原因：可以带入替换
```

判断下面表达式能否放进普通 affine expression，并简述原因：

| 表达式 | 合法？ | 一句话理由 |
| --- | --- | --- |
| `2*d0 + d1 + 3` | 是 | ____ |
| `d0*d1` | 否 | ____ |
| `d0 floordiv 4` | 是 | ____ |
| `d0 floordiv s0` | 否 | ____ |

## 4. 验证记录

按环境记录使用 LLVM/MLIR 22.1.8。执行目录为仓库根目录：

```sh
mlir-opt --verify-each learning-plans/mlir/exercises/chapter-08/01_tensor.mlir -o /dev/null
mlir-opt --verify-each learning-plans/mlir/exercises/chapter-08/02_memref.mlir -o /dev/null
mlir-opt --verify-each learning-plans/mlir/exercises/chapter-08/03_affine.mlir -o /dev/null
```

如果当前终端没加载 PATH，可将 `mlir-opt` 换为 `/opt/homebrew/opt/llvm@22/bin/mlir-opt`。

```text
三个命令退出码：0 / 0 / 0
这是哪一层验证（解析验证 / Pass 变换 / 数值执行 / 性能测量）：解析验证
它能证明：mlir格式正确
它不能单独证明：功能与预期一致
```

语义预期（尚不等于执行结果）：Tensor 返回 `(1, 9)`；MemRef load 读到 `9`；Affine 输入 `2,3,10` 时计算 `24`。若需要报告真实数值，必须实际执行程序并记录运行工具和输出；`mlir-opt --verify-each` 只负责解析/验证此处的 IR。

## 5. 本章验收

```text
Tensor 是在构造新值还是原地修改？构造新值
MemRef 的 store 对什么产生影响？存储
shape 描述什么；layout/stride 描述什么？shape描述tensor/mem维度数量和每一维大小，layout/stride 描述引用如何计算下标
verifier 通过为什么不等于证明所有索引运行时都安全？这里只是静态的安全，无法完全检查所有可能输入
```

## 导师核对与验证记录（2026-10-10）

- 三个文件都由本机 MLIR 22.1.8 的 `mlir-opt --verify-each` 验证通过，退出码分别为 `0 / 0 / 0`。这是解析与 IR verifier 检查，不是函数数值执行。
- Tensor：`%t` 是 `[1,2]`，`%t2` 是 `[9,2]`；返回语义值为 `(1,9)`。`tensor.insert` 创建新 SSA 值，所以原 `%t` 仍可读取。你对 SSA 不能重定义的解释正确；可补上“插入操作的结果绑定到另一个 SSA 名 `%t2`”。
- MemRef：第一次 store 后第 1 项为 `1`，第 2 项尚未初始化；不能把它当作一个确定的 `?` 数值读取或使用，不过这个示例后续在读取前已将第 2 项初始化。第二次后为 `[1,2]`，第三次后为 `[9,2]`，load 得到 `9`。`store` 没有 SSA 结果；它写入 `%m` 指向的存储。load 在 dealloc 之前，顺序正确；释放后继续访问该分配的内存会导致未定义行为。
- MemRef 与 Tensor 的措辞建议：Tensor 操作表达“产生新的不可变值”；MemRef store 表达“写入可变内存”。“Tensor 是赋值语义”容易与变量赋值混淆。
- Affine：`d0/d1` 绑定 `%i/%j`，`s0` 绑定 `%N`；代入 `2,3,10` 得 `2 + 3*4 + 10 = 24`。`%N` 不必为编译期常量；它作为当前分析区域内不随迭代坐标变化的参数。常数也可以是 symbol，但 symbol 的核心含义是这种参数角色，而不只是“可以替换”。
- 表达式判断全部正确：`2*d0+d1+3` 合法（变量只乘常数并相加）；`d0*d1` 不合法（变量与变量相乘）；`d0 floordiv 4` 合法（正整数常量除数）；`d0 floordiv s0` 不属于普通 affine expression（除数不是正整数常量）。
- 验收补充：shape 给出 rank（维度个数）和每维 extent；layout/stride 给出逻辑坐标如何映射到线性存储位置。Verifier 检查 IR 规则，但对未知的动态索引通常不能证明每次运行都在边界内。
