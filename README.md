# Engineering Learning Log

长期学习记录。

主要方向：

- C++ / 并发 / STL
- Compiler / LLVM
- EDA / Logic Synthesis
- Android / iOS / 系统开发
- AI / LLM

## Daily Learning

### 2026

- [2026-08](2026/08.md)

## Topic Notes

- [C++ Memory Model](topics/cpp-memory-model.md)
- [Logic Synthesis](topics/logic-synthesis.md)
- [Compiler & LLVM](topics/compiler-llvm.md)
- [EDA](topics/eda.md)

## Recording Rule

每日只记录最重要的少量结论：

1. 一个主题
2. 一句话核心结论
3. 最多 2～3 个关键点

例如：

```markdown
### CAS / compare_exchange

**CAS 失败时除了返回 false，还会把当前实际值写回 expected。**

- weak 允许伪失败，因此通常用于循环。
- failure memory order 约束失败时读取当前值的语义。
```

原则：

> 每天记录结论，不整理知识体系；积累到一定程度后，再整理成 Topic Note。
