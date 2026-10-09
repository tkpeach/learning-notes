# MLIR 学习环境记录

更新日期：2026-10-09

## 主机与工具

- 主机：macOS，Apple Silicon (`arm64`)
- 包管理器：Homebrew，prefix `/opt/homebrew`
- 已有工具：Homebrew `llvm` 21.1.8、`llvm@22` 22.1.8
- 本学习固定使用：LLVM/MLIR 22.1.8
- 工具目录：`/opt/homebrew/opt/llvm@22/bin`
- `mlir-opt`：`/opt/homebrew/opt/llvm@22/bin/mlir-opt`

## PATH 配置

`llvm@22` 是 keg-only formula，原先已安装但未在默认 PATH 中。已在 `/Users/ych/.zprofile` 加入：

```sh
export PATH="/opt/homebrew/opt/llvm@22/bin:$PATH"
```

新 zsh 登录 shell 中验证：

```sh
command -v mlir-opt
mlir-opt --version
```

当前 Codex 命令执行器不总是自动读取用户 shell profile；必要时使用完整路径，或通过 `zsh -lc 'mlir-opt --version'` 执行。

## 已完成的工具检查

- `mlir-opt --version` 输出 Homebrew LLVM version 22.1.8。
- `mlir-opt --help` 包含 `--canonicalize`、`--verify-each`、`--convert-scf-to-cf`。
- 一个 `scf.for` 求和 IR 在 `--verify-each` 下通过 `--convert-scf-to-cf`；输出中可见循环头 Block 参数和回边。
- 同一个求和函数依次通过 `--convert-scf-to-cf --convert-arith-to-llvm --convert-cf-to-llvm --convert-func-to-llvm --reconcile-unrealized-casts`，再由 `mlir-runner -e=sum_five --entry-point-result=i32` 执行并输出 `10`。
- 第 06 章的常量比较在 `--canonicalize` 后折叠为 `true` 与 `false`。
- 将 `func.call` 的目标改为不存在的 `@missing` 时，验证器报告其不是有效函数引用。

求和函数已通过 `mlir-runner` 完成真实数值执行；其他示例仍需按各自路径分别记录验证层级。

## 后续常用命令

```sh
mlir-opt --verify-each input.mlir -o /dev/null
mlir-opt --canonicalize input.mlir
mlir-opt --verify-each --convert-scf-to-cf input.mlir
```
