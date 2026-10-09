# 第 08 章学习记录：Tensor、MemRef、形状与 Affine

状态：学习进行中

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
| Tensor 替换元素并比较新旧值 | 待回答 | 起始文件 `exercises/chapter-08/01_tensor.mlir` |
| MemRef 初始化、写入、读取和释放 | 待回答 | 起始文件 `exercises/chapter-08/02_memref.mlir` |
| Affine 映射与一般索引表达式比较 | 待回答 | 起始文件 `exercises/chapter-08/03_affine.mlir`，答案文档含表达式分类 |
| 工具验证与运行结果 | 待验证 | 答案文档含 LLVM/MLIR 22.1.8 命令；尚未执行 |

## 小结

待学习后填写。
