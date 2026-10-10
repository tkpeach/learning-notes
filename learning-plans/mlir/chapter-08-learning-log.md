# 第 08 章学习记录：Tensor、MemRef、形状与 Affine

状态：已完成（IR 解析与 verifier 验证通过；未做数值执行）

本章学习从用户要求“继续”后开始。按其偏好，先完成结构化讲义，再逐步做练习；多题或长回答会提供带简洁填写框架的仓库文档。

## 学习材料

- [第 08 章讲义](chapter-08-lesson-01.md)

## 章节目标

- 分辨 Tensor 值语义与 MemRef 可变内存语义。
- 读出 rank、形状、元素类型、动态维度与布局。
- 理解索引、切片/视图、分配和生命周期。
- 初步判断 Affine map/循环的维度、符号和表达式约束。
- 认识解析验证、变换、执行、性能验证各自的结论边界。

## 练习与验收

集中练习与可编辑答案：[exercises/chapter-08/answers.md](exercises/chapter-08/answers.md)。

| 项目 | 状态 | 记录 |
| --- | --- | --- |
| Tensor 替换元素并比较新旧值 | 已完成 | 正确追踪 `%old=1`、`%new=9`，理解 insert 产生新 SSA 值 |
| MemRef 初始化、写入、读取和释放 | 已完成 | 读取值 9，了解未初始化位置与 dealloc 后访问的风险 |
| Affine 映射与一般索引表达式比较 | 已完成 | 正确代入 map 并判断四类表达式；已补充 symbol 的参数/不变性含义 |
| 工具验证与运行结果 | 已完成（限 IR 验证） | 本机 LLVM/MLIR 22.1.8 的 `mlir-opt --verify-each` 三个输入均退出码 0；没有声称完成数值执行 |

## 小结

Tensor 以不可变 SSA 值建模，`tensor.insert` 返回新值；MemRef 表示可变存储，`memref.store` 写入该存储且无结果。类型中的 shape 描述 rank 和各维 extent，layout/stride 描述坐标到线性位置的映射。Affine map 把迭代维度与区域内不变参数分开，以受限表达式支持静态分析。完整答案与逐项导师反馈见 [集中练习](exercises/chapter-08/answers.md)。
