# 示例、练习与复现

[学习入口](../README.md) · [讲义](../lesson.md) · [学习日志](../learning-log.md)

四个正常程序是教学起点，断言用于验证关键语义，不是性能测试。失败文件保持独立，不纳入普通构建。

| 文件 | 观察点 | 已核对的输出/诊断 |
| --- | --- | --- |
| [01-basic.cpp](01-basic.cpp) | 相同业务逻辑的 virtual 与 Proxy 路径 | `proxy=37 virtual=37` |
| [02-ownership.cpp](02-ownership.cpp) | 借用、共享、独立值、独占移动、view、空状态 | `borrow=3 shared=11 value=20/21 unique=30`；`empty=false stored-null=true` |
| [03-expressions.cpp](03-expressions.cpp) | ADL 自由函数、direct 与 indirect、4.1 invoke | `reading:42 owners=2` |
| [04-erasure-model.cpp](04-erasure-model.cpp) | 手写单能力借用类型擦除 | `erased=37` |
| [05-constraints-fail.cpp](05-constraints-fail.cpp) | 四类约束失败 | 四个 CASE 都应编译失败，原因见下文 |

## 环境与取得依赖

2026-10-20 实际环境：macOS arm64；Apple Clang `17.0.0 (clang-1700.0.13.5)`；CMake `4.2.3`。依赖为官方 Proxy `4.1.0`，提交 `1c7ca609aba6d73df06183c14db9d2d210399af3`。本次通过官方源码目录集成，没有验证 vcpkg/Conan 安装。

上游 README 列的最低版本为 GCC 13.1、Clang 16.0.0、MSVC 19.31、NVIDIA HPC 24.1、Intel oneAPI 2024.0；Apple Clang 版本号不能直接当成上游 Clang 版本号。实际工具链还需试编译。

从仓库根目录执行：

```bash
git clone --depth 1 --branch 4.1.0 https://github.com/ngcpp/proxy.git /private/tmp/learning-proxy-4.1.0
git -C /private/tmp/learning-proxy-4.1.0 rev-parse HEAD
cmake -S learning-plans/cpp-proxy/examples -B /private/tmp/learning-proxy-build -DPROXY_SOURCE_DIR=/private/tmp/learning-proxy-4.1.0 -DCMAKE_BUILD_TYPE=Debug
cmake --build /private/tmp/learning-proxy-build -j 4
ctest --test-dir /private/tmp/learning-proxy-build --output-on-failure
```

依赖目录已经存在时跳过 clone，先核对提交，不覆盖已有目录。临时路径被清理后再取得。Windows/Linux 可换成自己的源码和构建路径。CMake 最低 3.28，示例目标通过上游 `msft_proxy4::proxy` 接入；Debug 保留 assert 检查。

实际结果：4/4 通过。**C++20 模式构建有警告**：Apple Clang 报上游 `PRO4D_STATIC_CALL` 使用 static call operator 是 C++23 扩展。源码按 `__cpp_static_call_operator` 选择此优化分支；本机该特性宏在 C++20 模式也可见。本次没有修改依赖或屏蔽警告，不能把结果说成严格无扩展 C++20 验证。启用 `-Werror` / 严格语言诊断的项目要单独处理工具链兼容性。

只想直接编译一个例子：

```bash
clang++ -std=c++20 -I/private/tmp/learning-proxy-4.1.0/include learning-plans/cpp-proxy/examples/01-basic.cpp -o /private/tmp/proxy-basic
/private/tmp/proxy-basic
```

## 编译失败实验

先自己判断每种 CASE，再执行。以下命令的非零退出是预期行为，但仍需核对错误原因。将 `CASE=1` 分别改成 2、3、4；每次把完整诊断保存到临时文件也可以。

```bash
clang++ -std=c++20 -fsyntax-only -ferror-limit=3 -I/private/tmp/learning-proxy-4.1.0/include -DCASE=1 learning-plans/cpp-proxy/examples/05-constraints-fail.cpp
```

<details><summary>实际验证的诊断与解释（做完预测后展开）</summary>

| CASE | 原因 | 本机诊断核心 |
| --- | --- | --- |
| 1 | Missing 没有 read | `required convention not implemented` |
| 2 | Throws::read 不是 noexcept，无法满足声明的无抛出能力 | `required convention not implemented` |
| 3 | unique_ptr 不能满足可复制 facade | `insufficient copyability` |
| 4 | 默认 Readable 的 proxy 不可复制，复制构造不可用 | `no matching constructor`，约束中 copyability 不满足 |

四次退出码均为 1。CASE 1/2/3 还伴随 immediate function / constant expression 诊断；先定位上游 static_assert 的根因，不被派生错误带偏。四种 CASE 都伴随上述扩展警告，警告不是本实验预期失败的原因。
</details>

## 练习保存规则

题目在[四章路线](../README.md#四章路线)。基线示例保持能运行；新尝试按编号另存，例如 `a2-triangle.cpp`、`b2-unique-fail.cpp`、`b2-fixed.cpp`。记录输入、预测、实际结果和解释。构建产物继续放临时目录。

未执行：其他编译器、严格无扩展 C++20、模块集成、跨动态库 ABI、性能基准、内存/线程 sanitizer。当前通过只能证明所列程序在本机的这些语义观察成立。
