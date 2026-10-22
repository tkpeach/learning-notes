# Proxy 讲义

[学习入口](README.md) · [示例](examples/README.md) · [证据与资料](resources.md)

## M01：改变的是接口与实现的绑定方式

有一组异构对象，都能求面积。你希望运行时决定它们的具体类型，又让调用方只依赖“能求面积”这个接口。

传统方式是 `struct Shape { virtual double area() const = 0; ... };`，实现类继承它，调用方拿 `Shape*` 或智能指针。接口参与了实现类型的定义；对不能修改的第三方类型，通常需要适配器。

Proxy 允许使用方在类定义之外声明所需表达式，再把满足要求的对象句柄装进同一种包装类型。实现类不需要知道这个接口。它是 C++20 库，以模板生成适配和分派设施；不是新的语法或新的对象模型。

**关键转变：从“你继承了哪个基类”，转向“这个句柄支持哪些操作表达式”。**这些表达式在接入时做编译期检查，通过后，调用方仍能在运行时处理不同具体类型。无继承的类型擦除早已存在，Proxy 把这套机制做成通用库，并显式纳入指针语义。

不要误解为动态语言的运行时找方法：一个不支持 `area()` 的类型通常在构造 Proxy 时就编译失败。也不要误解为运行时多态从此零开销：通用调用仍可能需要函数指针间接跳转。

## M02：四个术语与最小用法

本节代码对应 [01-basic.cpp](examples/01-basic.cpp)，已保存完整可执行版。

```cpp
PRO_DEF_MEM_DISPATCH(MemArea, area);
struct Shape : pro::facade_builder
    ::add_convention<MemArea, double() const noexcept>
    ::build {};

struct Square {
  double side;
  double area() const noexcept { return side * side; }
};

pro::proxy<Shape> p = pro::make_proxy<Shape, Square>(5.0);
double result = p->area();
```

| 术语 | 含义 | 本例 |
| --- | --- | --- |
| dispatch | 把某种表达式编码为可调用的类型 | `MemArea` 表达调用成员 `area` |
| overload | 此能力允许的函数类型，包括限定符 | `double() const noexcept` |
| convention | dispatch、overload 集合及 direct/indirect 的组合 | 默认在被指对象上调用的面积能力 |
| facade | 一组 conventions、反射与存储/生命周期约束的编译期描述 | `Shape` |
| proxy | 擦除具体句柄类型后的运行时包装 | `pro::proxy<Shape>` |

`facade_builder` 的 `::add_...::build` 是模板别名链，逐步累积类型信息；没有运行时 builder 对象。虽然定义 facade 使用了继承语法，业务实现 `Square` 并未继承接口；库内部使用继承组合访问器也不矛盾。

宏用于生成具名访问器等样板；C++20 模板无法凭任意标识符自动生成方法名。它不是通过字符串反射找方法。一般从成员 dispatch 学起，再看自由函数和运算符。

对 `area_of(const pro::proxy<Shape>&)` 而言，各实现的具体类型已经在接入边界被隐藏，因此函数本身无需成为模板。模板工作仍发生在接入和分派适配代码中，并没有消失。

参考：[成员 dispatch 规范](https://github.com/ngcpp/proxy/blob/4.1.0/docs/spec/PRO_DEF_MEM_DISPATCH.md)、[convention 规范](https://github.com/ngcpp/proxy/blob/4.1.0/docs/spec/basic_facade_builder/add_convention.md)。

## M02 补充：为什么形式像 CRTP，机制却不同？

2026-10-21 学习者提问：整体格式像“奇异模板递归”，与 CRTP 差别在哪里，Proxy 有什么优势？这里的常见名称是“奇异递归模板模式”（Curiously Recurring Template Pattern）。

### 先看继承的双方是谁

CRTP 的典型结构是 **派生类型把自己作为模板参数传给基类**：

```cpp
template<class Derived>
struct ShapeBase {
  double area() const {
    return static_cast<const Derived&>(*this).area_impl();
  }
};

struct Circle : ShapeBase<Circle> {
  double radius;
  double area_impl() const { return 3.14159 * radius * radius; }
};
```

`ShapeBase<Circle>` 知道 Derived 就是 Circle；`area()` 静态转回该类型调用实现。另一个 `Square : ShapeBase<Square>` 会继承另一个基类实例。递归指的是类型定义形式，不是运行时递归调用。

Proxy 示例里，继承发生在 **facade 描述类型** 上：

```cpp
using ShapeSpec = pro::facade_builder
    ::add_convention<MemArea, double() const noexcept>
    ::build;
struct Shape : ShapeSpec {};
```

这相当于把之前的别名链拆开命名。`ShapeSpec` 描述所需能力及约束；它没有像 `ShapeBase<Circle>` 那样接收业务实现类型 Circle。具体对象类不用继承 Shape，也不用改成某个模板基类的派生类。这一段属于编译期类型构造，不能仅凭使用模板和继承就判定是 CRTP。

### 真正的区别在消费者是否仍知道具体类型

CRTP 单独使用时：

```text
ShapeBase<Circle>::area → Circle::area_impl
ShapeBase<Square>::area → Square::area_impl
```

函数可以用模板统一书写，但两种实例仍是不同类型；`ShapeBase<Circle>*` 不是指向任意 ShapeBase 实例的共同指针类型。若要在同一个运行时容器中处理 Circle/Square，还需要 variant、虚接口或类型擦除等额外机制。

Proxy 在接入处用模板生成适配函数，消费者则通过同一个 `proxy<Shape>` 类型处理对象：

```text
Circle 或 Square 的句柄
  → 构造 proxy<Shape>，绑定对应适配代码
  → 消费者只知道 proxy<Shape>
  → 调用时经元数据进入对应适配函数
  → 恢复具体句柄并调用目标 area()
```

例如 `std::vector<pro::proxy<Shape>>` 可以同时容纳两个类型的包装，而 `double sum(const std::vector<pro::proxy<Shape>>&);` 无需把 Circle/Square 列为模板参数。具体类型的适配代码仍在接入处实例化，并没有消除模板工作。

### Proxy 的优势与付出的代价

| 维度 | CRTP 单独使用 | Proxy |
| --- | --- | --- |
| 选择实现 | 编译期由具体实例决定 | 统一包装类型下可在运行时选择对象 |
| 调用者是否保留具体类型 | 保留 | 消费者只依赖 facade |
| 开放的异构容器 | 需要额外机制 | 可用同一个 proxy 类型承载 |
| 接入第三方类型 | 若要求 CRTP 基类，需改类或写适配器；普通模板约束也可非侵入接入 | 满足表达式和句柄约束即可，无需继承接口 |
| 拥有、借用策略 | 使用普通 C++ 所有权设施，CRTP 本身不统一擦除它们 | 可在相同操作接口下擦除不同 P；仍须明确存活契约 |
| 常见调用成本 | 静态直调，利于内联 | 一般有间接分派；优化器可能消除部分间接性 |

优势集中在“运行时可替换 + 统一接口 + 非侵入接入”，不是比 CRTP 更快。若调用点已知具体类型且适合模板化，普通 templates/concepts 或 CRTP 往往更直接，也更利于优化。Proxy 对消费者隐藏具体类型和依赖，但接入侧仍承担模板实例化及库维护成本。

两者还能组合：一个类内部用 CRTP 复用算法，外部通过 Proxy 暴露运行时接口。可以借此分离局部实现复用与跨模块的运行时抽象。

参考：[官方 FAQ 的 CRTP 比较](https://microsoft.github.io/proxy/faq/#how-does-proxy-compare-with-crtp-in-terms-of-performance-and-lifetime-management)、[固定版本 builder 源码](https://github.com/ngcpp/proxy/blob/4.1.0/include/proxy/v4/detail/facade_creation.h)。此处不引用微基准倍数推断本机性能；本次补充为机制讲解，未新增执行实验。

## M03：先分清 P 与 *P，再谈所有权

`proxy<F>` 存的是一个具体的 **pointer-like 类型 P 的值**。例如 `Cell*`、`unique_ptr<Cell>`、`shared_ptr<Cell>`，以及库工厂生成的内部句柄。正常业务能力一般作用在 `*P`，而生命周期操作作用在 P。

| 构造方式 | 存储的 P / 策略 | 销毁包装时 | 复制包装时（facade 允许复制才有意义） |
| --- | --- | --- | --- |
| `p = &cell` | 裸指针，借用 | 不销毁 cell | 复制地址，仍指同一 cell |
| `p = std::make_unique<Cell>(...)` | unique_ptr，独占 | unique_ptr 释放 cell | unique_ptr 不可复制，不能接入要求可复制的 facade |
| `p = std::make_shared<Cell>(...)` | shared_ptr，共享 | 减少引用计数 | 复制 shared_ptr，共享同一 cell |
| `make_proxy<F, Cell>(...)` | 库选择的拥有型句柄 | 销毁拥有值 | 此工厂的值复制策略可产生独立 cell，受类型及约束限制 |
| `proxy_view<F> view = &cell` | 明确的非拥有观察接口 | 不延长 cell 生命周期 | 复制观察关系 |

**复制的是 P；深浅复制由 P 的实现决定。** `support_copy<nontrivial>` 是允许并要求句柄可复制，不是“请给所有对象深拷贝”的开关。默认 builder 不启用复制；`shared_ptr` 本来能复制也不会让默认 facade 的 proxy 自动可复制。

[`proxy` 规范](https://github.com/ngcpp/proxy/blob/4.1.0/docs/spec/proxy/README.md)保证 P 自身存于包装足迹内，不为存放 P 另外分配；这不等于 P 所指对象不分配。比如 `make_unique` 已经在堆上构造对象。

[`make_proxy`](https://github.com/ngcpp/proxy/blob/4.1.0/docs/spec/make_proxy.md)先在编译期检查内联句柄能否满足全部约束，适合才内联；否则选择分配型句柄。大小不是唯一条件，还包括对齐、复制、relocation 和销毁要求。`make_proxy_inplace` 可用于要求库的存储不另行分配的场合，但 T 的构造函数仍可能自己分配，例如构造包含动态容器的对象。

生命周期边界有三点要单独记住：

- 裸指针及 view 都不负责延长被观察对象的生命周期。不要从函数返回观察局部对象的包装，也不能观察已被 `reset` 销毁的拥有对象。
- `has_value()` 表示包装里存在 P，不保证 P 指向有效对象。空包装与“装着一个空 `Cell*` 的包装”不同，后者不能解引用。示例 02 会验证这个区别。
- 包装的 `const` 不自动赋予裸指针目标深层 const；约束中的 const 首先影响传入 dispatch 的操作数，而 `const shared_ptr<T>` 解引用仍可得到 `T&`。需要只读 API 就只暴露只读能力；需要禁止修改目标时还要核查 `const T*` 等底层类型。

参考：[复制约束](https://github.com/ngcpp/proxy/blob/4.1.0/docs/spec/basic_facade_builder/support_copy.md)、[view 规范](https://github.com/ngcpp/proxy/blob/4.1.0/docs/spec/proxy_view.md)、[状态查询](https://github.com/ngcpp/proxy/blob/4.1.0/docs/spec/proxy/operator_bool.md)。

## M04：抽象的是表达式，不限于成员虚函数

[03-expressions.cpp](examples/03-expressions.cpp)使用一个第三方类型 `vendor::Reading`。自由函数 `describe(const Reading&)` 与它位于同一命名空间，通过 ADL（实参相关查找）找到。`PRO_DEF_FREE_AS_MEM_DISPATCH` 可以把自由函数表达式呈现为 `p->describe()`，并没有给 Reading 真的添加成员。

默认 `add_convention` 即 indirect：dispatch 得到 `*P`。`add_direct_convention` 则让 dispatch 得到 P 本身。例如同一个包装里：

```cpp
p->describe();  // 对 Reading 调用 describe(*P)
p.use_count(); // 对 shared_ptr 调用 P.use_count()
```

因此支持第二种能力的 facade 会排除没有 `use_count()` 的句柄；即便被指对象完全相同，换一种所有权句柄也可能不再满足接口。这是理解 `proxiable<P,F>` 为什么检查 P 的关键。

还可以使用 `operator_dispatch` 表达调用、下标或流输出等操作，以 `add_facade` 合并能力，以 skills 增加视图、弱观察、RTTI 或格式化等功能。这些按需求增加；能力越多不意味着设计越好。

4.1.0 的自定义访问器使用 ADL 找到 `invoke<Dispatch, Signature>(...)`；不是命名空间函数 `pro::invoke`。对 indirect 能力传 `*p`，对 direct 能力传 `p`。普通代码优先用具名访问器，示例 03 只为展示原理额外调用一次 direct `invoke`。

参考：[自由函数转成员访问器](https://github.com/ngcpp/proxy/blob/4.1.0/docs/spec/PRO_DEF_FREE_AS_MEM_DISPATCH.md)、[direct invoke](https://github.com/ngcpp/proxy/blob/4.1.0/docs/spec/proxy/friend_invoke.md)、[indirect invoke](https://github.com/ngcpp/proxy/blob/4.1.0/docs/spec/proxy_indirect_accessor/friend_invoke.md)。

## M05：选择哪一种多态

下面是工程判断框架，不是性能排名。

| 方案 | 具体类型集合 | 运行时异构容器 | 实现类型接入 | 主要代价/适用点 |
| --- | --- | --- | --- | --- |
| 模板 / concepts / CRTP | 每次实例化已知类型 | 单靠它们不能直接统一不同具体类型 | 结构满足约束或使用 CRTP | 利于内联；调用方可能模板化，代码实例多 |
| virtual + 智能指针 | 可开放扩展 | 容易 | 继承或适配器 | 成熟工具链；接口绑定类层次，通常间接调用 |
| variant + visit | 封闭备选集合 | 容易 | 列入备选类型 | 无需共同基类；加类型会影响 variant 与访问逻辑，大小受最大备选影响 |
| function / move_only_function | 按某个调用签名开放 | 同签名可统一 | 可调用对象 | 单调用抽象通常更直接；不适合任意多能力对象接口 |
| any | 开放 | 可以存异构值 | 可存放类型满足要求 | 擦除存储类型，但本身不提供 area 等领域操作 |
| Proxy | 对外一个 facade，具体 P 可开放扩展 | 容易 | 满足表达式与存储/生命周期约束 | 非侵入式、能组合表达式；引入模板设施和库依赖，仍需管理借用与分派成本 |

适合试用的场景：给现有或第三方类型定义统一运行时接口；接口依赖需要收敛到非模板函数；同一操作面需要多种拥有策略；原来手写了多个重复的类型擦除 wrapper。

优点主要是解耦和可组合性：实现类型无需嵌入业务接口，使用方能按需要组合能力；生命周期策略可由 P 表达；小值有机会内联，调用元数据有优化空间。

代价与限制需要结合场景看：

- 学习和诊断成本：模板、限定符、ADL 和宏访问器需要理解；接入失败可能涉及表达式、noexcept、布局或 relocation 的不同约束。
- 构建与体积：模板实例、分派适配函数和元数据可能增加编译时间与二进制大小。对外函数不模板化并不代表整个程序的实例化成本为零。
- 所有权可读性：相同 `proxy<F>` 可能拥有也可能借用。公共 API 应明确“返回的对象是否独立存活”；参数若只观察可考虑显式 `proxy_view`。
- 安全与线程：不会替你做借用检查，也不保证线程安全；shared_ptr 管的是共享生命周期，目标并发访问仍需自己的同步。
- ABI：实现类无需改变布局不等于任意跨编译器 ABI 稳定。facade 约束、库版本、编译器、标准库、异常/RTTI 设置都要统一评估；不把它自动当作永久插件 ABI。
- 维护与迁移：需要接受当前 ngcpp 的维护条件，固定依赖并能回退；已有稳定继承层次没有必要为了“更新写法”全量重构。

## M06：性能怎么学，工程怎么验证

[官方 2024 基准](https://devblogs.microsoft.com/cppblog/analyzing-the-performance-of-the-proxy-library/)报告在其测试中相对 virtual 和其他包装的优势。它展示了值得研究的机制：内联对象、分派元数据位置、不同生命周期成本。但不能推出“所有负载都更快”；业务方法耗时、缓存、分支预测、编译优化都会改变结果。本专题没有跑性能基准。

公平比较至少分开测两类问题：

1. **分派本身**：让两边都借用同样布局和访问顺序的对象，尽量统一分配与业务负载；阻止死代码消除，记录编译器、优化、LTO、类型分布和样本波动。
2. **端到端拥有型方案**：按实际工厂构造、复制、移动、销毁和遍历。此时内联与堆分配差异本来就是设计效果，但不能把全部收益说成一次间接调用更快。

同时记录编译时间、二进制大小、每包装字节数和分配次数。`sizeof(proxy<F>)` 是包装尺寸，不是包含堆上对象的总占用。只看单条汇编或一次微基准都不够。

迁移从一个 API 边界开始，以已知正常版本的完整行为为基线：构造 → 调用 → 复制/移动 → 销毁 → 错误传播。逐项核对别名共享、异常、空状态和借用存活时间，再决定是否扩大范围。新增 fallback 不能代替或绕过既有主路径。
