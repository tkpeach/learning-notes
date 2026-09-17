# Control-Flow Integrity

CFI（Control-Flow Integrity，控制流完整性）是一类编译器安全保护：程序只能沿着“编译期允许的控制流边”执行，尤其限制间接调用。

clang 提供一系列选项添加对应的插桩保护，需要在链接时由库提供插桩所引用符号的具体实现。

编译器会在间接调用前插入类型校验；当无法在本地直接完成校验时，调用 CFI runtime 的 `__cfi_slowpath`。

| 选项 | 会检查出的问题 | 示例 |
|---|---|---|
| `-fsanitize=cfi-vcall` | 虚函数调用的对象类型被破坏、伪造或发生类型混淆。 | `Base* p = reinterpret_cast<Base*>(attackerMemory); p->Run();`。若 `p` 的 vtable 不属于 `Base::Run()` 的合法目标集合，检查失败。 |
| `-fsanitize=cfi-icall` | 函数指针、回调或函数表的真实签名与调用点期望签名不一致。 | `using Callback = void (*)(int); void Wrong(const char*); Callback cb = reinterpret_cast<Callback>(Wrong); cb(1);`。调用点要求 `void(int)`，实际目标是 `void(const char*)`，检查失败。 |
| `-fsanitize-cfi-cross-dso` | 回调或虚调用跨 `.so` 时，目标地址不属于该调用点允许的类型集合。 | `libA.so` 按 `void (*)(int)` 调用回调；`libB.so` 经强制转换传入 `void Wrong(const char*)`，跨 DSO 校验失败。 |
| `-fsanitize=cfi-derived-cast` | 基类指针被错误地下转为不匹配的派生类。 | `Base* p = new Image(); auto* text = static_cast<Text*>(p); text->SetFontSize(16);`。实际对象是 `Image`，而不是 `Text`，检查失败。 |
| `-fsanitize=cfi-unrelated-cast` | 多态对象被强制转换为无继承关系的另一类型。 | `Image* image = ...; auto* text = reinterpret_cast<Text*>(image); text->SetFontSize(16);`。`Image` 与 `Text` 无兼容继承关系，检查失败。 |
| `-fsanitize=cfi-nvcall` | 使用错误对象类型调用非虚成员函数。 | `Base* p = new Image(); static_cast<Text*>(p)->Text::NonVirtualMethod();`。对象实际不是 `Text`，检查失败。 |
| `-fsanitize=cfi` | CFI 总开关；具体检查类别由 `cfi-vcall`、`cfi-icall`、`cfi-derived-cast` 等子选项决定。 | 当前工程先关闭默认 CFI 集合，再单独启用 `cfi-vcall` 与 `cfi-icall`。 |
| `cfi_vcall_icall_only = true` | 只检查虚函数调用和间接函数调用，不额外检查错误下转或无关类型转换。 | 能拦住伪造 vtable 和错误回调；不会启用 `cfi-derived-cast`、`cfi-unrelated-cast`、`cfi-nvcall`。 |
