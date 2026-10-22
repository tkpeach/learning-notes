# Proxy 复习卡

[学习入口](README.md)。这些是待自测的问题，不表示已经掌握。先闭卷回答，再展开。

1. Proxy 所谓新多态，新在哪里？

<details><summary>核对</summary>

使用方以表达式能力描述接口，已有实现类型无需继承该接口；接入时检查能力，调用时擦除具体句柄类型。它是库，不是新的 C++ 语法；类型擦除本身也并非新发明。
</details>

2. facade、dispatch、convention、proxy 分别负责什么？

<details><summary>核对</summary>

dispatch 表达一种操作；convention 把 dispatch、overloads 和 direct/indirect 属性组合；facade 汇集能力及存储/生命周期约束；proxy 保存具体句柄和分派元数据，提供运行时入口。
</details>

3. 同类型的两个 proxy，一个拥有对象、一个借用对象，可能吗？

<details><summary>核对</summary>

可能。相同 facade 下可装裸指针或拥有型 P；F 限制允许的句柄与能力，未必固定唯一所有权策略。公共 API 必须写清存活约定。
</details>

4. `support_copy` 是深拷贝开关吗？

<details><summary>核对</summary>

不是。它要求并启用 P 的复制；裸指针复制地址，shared_ptr 共享目标，make_proxy 的拥有值策略可复制目标值。unique_ptr 无法满足可复制要求。
</details>

5. `has_value()` 为真，是否就可以调用？

<details><summary>核对</summary>

不能保证。装着一个空裸指针的包装仍存在 P；悬垂指针同样无法靠 has_value 检测。需要保证目标有效且满足调用前置条件。
</details>

6. `make_proxy` 是不是总不分配？

<details><summary>核对</summary>

不是。编译期检查内联 P 的大小、对齐与生命周期等约束，不符合则选择分配型句柄。即使库内联存储，T 的构造也可能自己分配。
</details>

7. `p->describe()` 与 `p.use_count()` 在示例中分别操作谁？

<details><summary>核对</summary>

前者是 indirect convention，分派到 describe(*P)，经 ADL 找到自由函数；后者是 direct convention，调用 P.use_count()。访问器的名字不证明第三方类型真的有该成员。
</details>

8. 类型在何时已知，何时被隐藏？

<details><summary>核对</summary>

接入时模板知道 P，并生成检查、分派及生命周期代码；消费者只知道 proxy&lt;F&gt;。运行时经元数据进入 P 专属适配函数，恢复 P 后执行表达式。
</details>

9. Proxy 与 virtual 的元数据位置有什么差别？是否保证更快？

<details><summary>核对</summary>

常见 virtual ABI 在目标对象里放 vptr；Proxy 在包装侧持有/引用分派元数据，实现对象无需改变布局。缓存、内联对象和加载路径可能获益，但优化与工作负载会改变结果，不能保证更快。
</details>

10. 不支持方法、违反 noexcept、unique_ptr 要求复制，这三类错误在什么时候出现？

<details><summary>核对</summary>

通常在编译期接入检查出现。不同原因需核对诊断，不应统称运行时不兼容。[失败案例](examples/05-constraints-fail.cpp)可复现。
</details>

11. 现在应该看哪个仓库？它已是标准库吗？

<details><summary>核对</summary>

2026-10-20 核查：微软仓库归档，当前维护在 ngcpp/proxy；本专题基于 4.1.0。P3086 仍按提案对待，不能把它当作已提供的 std::proxy。状态变化需重查[资料页](resources.md)。
</details>

12. 如何证明引入它有价值？

<details><summary>核对</summary>

先说明需要解决的接口耦合或手写类型擦除问题；以现有正常链路核对所有权、复制、异常和生命周期，再做公平实验。同时衡量构建、体积、运行成本和维护，不凭宣传数字重构全部层次。
</details>

迁移自测：为一个不允许修改的第三方缓存类型定义“读取大小、清空”能力，分别设计借用参数、拥有型返回值。解释 copy、const、noexcept 和线程安全约定，再选择模板/virtual/variant/Proxy。只有能解释选择和反例，才标记该模块掌握。
