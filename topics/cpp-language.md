# C++ Language

## Value category

lvalue: 有实体和地址，资源不允许转移。

xvalue：有实体和地址，资源允许转移。

prvalue: 值，没有实体和地址。

glvalue, rvalue

## auto 和 decltype

auto: 与`template<typename T>`中的匹配类似，是为了推断一个值的类型，区别在于auto可以推断成initialize_list类型。

1. array/function 退化到pointer。
2. 去除最外层const/valetile, 内层的会保留。
3. 去除&。

最后剩下的类型。

auto&& 会引用折叠，只有&& + && -> &&。

decltype: 查原始定义的类型。

1. `decltype(var)` 直接在AST上查找var定义的类型，不做修改。
2. `decltype(expr)` 根据expr类型，lvalue -> T&, prvalue -> T, xvalue -> T&&。

decltype(auto): 用`decltype(expr)`的方式推断auto。

## Constructor

1. 3 rule：析构函数、拷贝构造函数、拷贝赋值函数，在c++11之前需要一起考虑。
2. 5 rule：c++11之后，析构函数、拷贝构造、拷贝赋值、移动构造、移动赋值一起考虑。用户定义了析构/拷贝构造/拷贝赋值，编译器不再自动提供移动构造/赋值，包括提供`=default`这种默认。注意移动构造添加noexcept，否则vector等可能为了异常安全，而选择在扩容等操作时，使用拷贝构造。
3. 0 rule：RAII管理，不写任何上述函数。

| 你声明 | implicit default ctor | implicit copy ctor | implicit copy assign | implicit move ctor | implicit move assign |
| --- | ---: | ---: | ---: | ---: | ---: |
| 普通 ctor | ❌ | ✅ | ✅ | ✅ | ✅ |
| default ctor | 你已有 | ✅ | ✅ | ✅ | ✅ |
| copy ctor | ❌ | 你已有 | ✅ | ❌ | ❌ |
| copy assign | default ctor仍看有没有ctor | ✅ | 你已有 | ❌ | ❌ |
| move ctor | ❌ | deleted / 不可正常 copy | deleted/受影响 | 你已有 | 不自动生成 |
| move assign | default ctor规则独立 | copy受影响 | copy受影响 | 不自动生成 | 你已有 |
| destructor | default ctor仍可隐式 | ✅ | ✅ | ❌ | ❌ |

## Template

### 基础知识

1. 类中的函数也只有使用才被实例化，不是实例化类的时候同时实例化所有函数。
2. 非类型参数，不能使用浮点数、class类型对象和内部链接对象（如string，后续展开）作为实参。
3. 依赖模板参数的名称前添加关键字typename。

```
template <typename T>
class MyClass {
    // 防止被解读为成员乘法
    typename T::SubType * ptr;
};
```

4. 一个模板本身可以作为模板参数，称之为模板的模板参数。

```
template <typename T,
// 注意使用template关键字
          template <typename ELEM,
// 注意不能缺少模板参数，即使有默认实参
                    typename ALLOC = std::allocator<ELEM>>
// 注意class关键字
                     class CONT == std::deque>
class Stack{
    CONT<T> elems;
};
```

### ADL Argument-Dependent LookUp

对非限制名字的函数调用，根据实参类型，去所关联的class、namespace可以进行查找。

模板类型参数 A::X 也会带入对应关联 namespace。

```
namespace A { struct X {}; }
namespace B { template<class T> struct Box {}; }
B::Box<A::X> b;
foo(b);
```

如果普通 unqualified lookup 已经找到了某些类型的声明，ADL 会被抑制。例如找到：

- class member；
- block scope function；
- 非 function/function template 的声明，例如变量。

### Two-phase name lookup

不依赖模板参数的名字，在定义阶段查；依赖模板参数的名字，部分查找推迟到实例化阶段。

| 情况 | 主要 lookup 时间 |
| --- | --- |
| 普通非模板名字 | 出现位置 |
| 模板里的 non-dependent name | template definition |
| dependent qualified name | 主要到 instantiation 才完整确定 |
| dependent function call 的普通 lookup | definition context |
| dependent function call 的 ADL | 可受 instantiation type 影响 |
| `typename` | 告诉 parser dependent name 是类型 |
| `template` | 告诉 parser dependent member/name 是模板 |
