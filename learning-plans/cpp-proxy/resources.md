# 资料与使用现状

[学习入口](README.md)。核查日：**2026-10-20，Asia/Shanghai**。以下区分发布者陈述、公开状态和基于证据的判断。

2026-10-21 补充：[业界采用专项调查](adoption-2026-10-21.md)。新增 FISCO-BCOS release 分支的已合并实际接入证据，并区分项目集成、讨论提议和生产部署；以下保留原日快照。

## 现状快照（2026-10-20）

| 问题 | 公开证据 | 可以得出的结论与边界 |
| --- | --- | --- |
| 还在微软维护吗？ | [微软仓库](https://github.com/microsoft/proxy)显示 2026-01-29 归档，README 明示迁移至 ngcpp | 微软组织下只读；归档不等于项目停止 |
| 现在去哪里？ | [ngcpp/proxy](https://github.com/ngcpp/proxy)声明由 Next Gen C++ Foundation 维护 | 学当前接口、提 issue 应看新仓库；历史资料保留旧链接 |
| 稳定版本？ | [4.1.0 发布页](https://github.com/ngcpp/proxy/releases/tag/4.1.0)，2026-06-24；本地检出固定提交成功 | 本专题以 4.1.0 为基线；不把 main 上未发布改动混入示例 |
| 有生产使用吗？ | [微软 Proxy 3 公告](https://devblogs.microsoft.com/cppblog/announcing-the-proxy-3-library-for-dynamic-polymorphism/)称 Windows 自 2022 年使用 | 是发布者关于生产使用的陈述；并非可独立核查的 Windows 内部模块清单或覆盖率 |
| 是否已普及？ | 旧仓库页面约 3k stars、225 forks，新仓库约 168 stars、14 forks；[vcpkg](https://vcpkg.io/en/package/proxy)显示包 4.1.0，Used By 当时为无其他包 | 关注度、包可用性不能证明真实部署量；vcpkg 反向依赖也不涵盖私有用户。此次没有找到足以支持“业界主流”的公开采用统计 |
| 包管理器支持？ | [vcpkg 包页](https://vcpkg.io/en/package/proxy)、[ConanCenter](https://conan.io/center/recipes/proxy)均列出 4.1.0 | 可集成，不代表本机已经安装这些包；本文未执行包管理器安装 |
| 进标准了吗？ | [P3086R5](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/p3086r5.html)及[提案跟踪 issue](https://github.com/cplusplus/papers/issues/1741)；核查时 issue 为 Open、LEWGI、C++29 目标标签 | 仍按第三方库学习；目标标签不是接纳承诺，不能写成 C++26 已有 `std::proxy` |

**本专题的判断：**它有生产应用依据，值得用于学习类型擦除、表达式接口和所有权设计；是否引入实际项目，要单独验证维护、语义及成本。没有证据支持“全面替代 virtual”。

页面数字可能来自缓存，且随时间变化，仅保留为本次查询快照；不用于衡量迁移后活跃度下降。此次没有对第三方项目做全面代码搜索，也没有访问内部用户数据。

## 阅读顺序与用途

1. [当前 README（固定 4.1.0）](https://github.com/ngcpp/proxy/blob/4.1.0/README.md)：先看 API 形状、工具链要求和构建集成。不要一次读全部规范。
2. [4.1.0 发布说明](https://github.com/ngcpp/proxy/releases/tag/4.1.0)：只记这几项学习相关变化：`invoke`/`reflect` 改用 ADL hidden friends；旧 `proxy_invoke`/`proxy_reflect` 弃用；组合转换有 `add_facade_with_substitution`。普通业务代码优先访问器。
3. [固定版本 docs/spec](https://github.com/ngcpp/proxy/tree/4.1.0/docs/spec)：语义的主要核查材料。当前 ngcpp 文档站本次网页工具未能打开，改从同一版本仓库阅读 Markdown；不是假定站点永久不可用。
4. [微软时期规范](https://microsoft.github.io/proxy/spec/)和[FAQ](https://microsoft.github.io/proxy/faq/)：用于术语和历史设计背景，不能单独据此确认 4.1 新 API。
5. [固定版本实现目录](https://github.com/ngcpp/proxy/tree/4.1.0/include/proxy/v4/detail)：跟着[源码导读](implementation.md)阅读，避免从宏开头逐行啃。
6. [2024 性能分析](https://devblogs.microsoft.com/cppblog/analyzing-the-performance-of-the-proxy-library/)：研究实验方法。文章比较多个编译器、对象大小和生命周期策略，结论属于其 Proxy 3 时代工作负载，不是 4.1.0 在本机的结果。
7. [2025 Proxy 4 公告](https://devblogs.microsoft.com/cppblog/announcing-proxy-4-the-next-leap-in-c-polymorphism/)：解释从 3 到 4 的设计演进，按需阅读。
8. [P3086R5](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/p3086r5.html)：最后看动机与标准化边界。提案核心与实现库的工厂、builder、skills 范围不同；不要把提案措辞当成所有实现 API 的规范。

## 本地材料复现

依赖固定提交：`1c7ca609aba6d73df06183c14db9d2d210399af3`；tag：`4.1.0`；许可证：MIT。官方源码下载到 `/private/tmp/learning-proxy-4.1.0`，不复制到笔记目录。示例为本专题编写。临时目录可能被系统清理，重取方法见[示例说明](examples/README.md)。

维护规则：更新版本时，先记录新 tag、commit、日期，再运行正常示例与约束失败案例，核查所有权及调用主路径；不能只根据 API 能编译就宣称行为等价。需要离线源码归档时另行选择保存位置，目前笔记中的解释、练习、命令和验证记录均已本地保存。
