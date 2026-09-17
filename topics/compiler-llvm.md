# Compiler & LLVM

## LLVM 工具

- clang: `-emit-llvm -S` 生成IR; `-Xlang -ast-dump`
- llvm -ccl

## SSA 生成

### 经典方法

Dominate Tree -> Donimate Frontier (Donimate 关系破裂位置，也即边缘）-> 创建phi -> rename

### 优化方法 Lazy, Backward

创建map: `M[var][BB] = val/phi` -> read var -> 多个前驱，则创建phi，从每个前驱read var。

- 防止phi产生循环：多个前驱下先创建 `M[var][BB] = phi`，再查找每个前驱。
- BB unsealed 也可以做，也即生成AST过程中生成IR，对unsealed ir产生空phi，前驱生成后加入phi。

优点：可以直接产生直接消除的phi，对汇合后没有被读取的phi可以直接不生成。

```
AST / bytecode -> generate instruction -> SSA CFG under construction -> use(x) -> readVariable(x, B)

current definition exists -> return it
unsealed block -> incomplete φ
one predecessor -> recurse
multiple predecessors -> φ(read(x,p1), read(x,p2), ...) -> remove trivial φ
```

## Dominance

- Dominant Tree(DT): 优化常用。
- Dominant Frontier。
- 反Dominant。

## TableGen

生成inc文件用于LLVM后续，包含多个records。

第一步：前端解析成records规则。

第二步：不同后段可以分别使用规则，指导不同阶段内容。

`build/bin/llvm-tblgen RISCV.td --print-records`：`--print-records`生成records用于查看。

`build/bin/llvm-tblgen RISCV.td -gen-instr-info`：`-gen-instr-info`生成Target相关信息，需要td文件中带有Target。

### 语法

- class: 类似template
- def: 生成class实例，后续生成records
- let: 修改class内默认值
- multiclass: 生成一系列def的template
- defm: 生成一系列def
- bits<N>: 多个bit
- a{31,10}: 截取
- dag: operator + arguments，frontend做记录，由backend解读

```
class Instr<bits<4> op, string desc> {
bits<4> opcode=op;
string name=desc;
}
multiclass RegInstr {
def rr : Instr<0b1111,
"rr">;
def rm : Instr<0b0000,
"rm">;
}
defm MyBackend
_
:RegInstr;
```

### 完整流程

```
XXX.td -> TGLexer / TGParser -> RecordKeeper
  -> Instruction Records / Register Records / Pattern Records / ...
  -> 不同 TableGen backend
  -> InstrInfoEmitter / RegisterInfoEmitter / DAGISelEmitter / GlobalISelEmitter / AsmMatcherEmitter / ...
  -> XXXGen*.inc -> LLVM C++代码 #include
```

### Pattern / Pat

```
let Pattern = [(set GPR:$rd, (Op GPR:$rs1, GPR:$rs2))];
```

- 整理成Matcher。
- 读取所有Matcher，匹配指令生成。

`-gen-instr-info`：主要生成“这条机器指令是什么”。

`-gen-dag-isel`：主要生成“什么时候选择这条机器指令”。

## Instruction Selection

Instruction Selection（指令选择）解决的是：给定一段 target-independent IR，以及目标 CPU 的 ISA，选择一组语义等价的目标机器指令来实现这段 IR，并尽量让最终代码更好。

在编译器中的位置：

```
Source -> Frontend -> IR -> Optimizer -> Instruction Selection
-> Instruction Scheduling -> Register Allocation -> Assembly / Machine Code
```

### 建模

- Macro Expansion：按照最简单的指令先做生成，然后合并。
- Tree Covering: 抽象命令组织成树状，每个节点枚举可能的covering及对应children子树cost之和，用DP算法。
- DAG: 现实IR很少能用Tree表示，比如一个变量（节点）被不同位置使用，DAG表示范围变大，NP hard。
- Graph: DAG表示限制仍然很多，如跨BB，需要使用一般Graph，NP hard。

### Tree Covering

从叶子节点开始计算，增加nonterminal，作为不同使用位置（machine grammar）的标志，从而将一个复杂指令拆分成多个（逻辑上，非物理）的简单指令。

nonterminal 不是 IR node。它是 grammar 给一个 subtree 附加的“语义状态”。理解成：如果父 instruction 要使用这个 subtree，那么这个 subtree 能以什么形式交付结果？

如 `add（*addr+offset，reg)` 可以拆分成一个目标r的add和一个目标mem的add，从而在匹配时候可以从mem或reg达到最终的add。

进一步的，将部分计算过程放置在编译器生成阶段，也就是在tablegen的td中，描述从不同目标到不同目标的增量代价，编译期间直接查表代替临时计算。

假设 compiler 正在编译：

```
add(mul(a,b),c)

mul node:
cost[r] = 1
cost[m] = 0

add node:
try ADD:  1 + child0.cost[r] + child1.cost[r] = 2
try MADD: 1 + child0.cost[m] + child1.cost[r] = 1
```

也就是说：这些 arithmetic cost calculations 发生在“编译用户程序”的时候。

### 从 Tree 到 DAG

真实的IR组织无法是Tree，只能用DAG表示。实际上ISA中部分命令也无法用Tree表示，但是当前先不考虑。

- Split：将DAG在汇合节点split，强行分成多棵树，缺点是汇合点无法参与指令覆盖的优化。
- Duplicate：将DAG在汇合节点duplicate，复制一份子树，这样汇合点可以参与优化，缺点是会导致子树重复生成指令。
- 将DAG看作Tree来遍历：在汇合点看nonterminal，如果一致则说明子树之间是一致的，可以接受；缺点是每个子树局部最优不一定是全局最优。
- 在上一步的基础上，汇合点位置进行代价评估，未详细学习。
- LLVM使用：greedy DAG-to-DAG rewriting，TableGen 将 target descriptions 展开并生成 matcher，patterns 按 complexity/cost 等排序；找到一个 match 后就 greedily 选择并替换匹配 subgrap。

### ISA 使用 DAG

指令产生多个输出，需要使用DAG，无法用Tree表示；另外的例子是SIMD，一个指令没有共同Root。

- 指令DAG拆分成Register Transfer（RT），分别都是Tree Pattern，分别匹配后再合并RT。
- 在上述基础上，形成多种RT合并组合，把指令替换做成conflict graph。

### 整体进化路线

```
Chapter 3
Program Tree / Machine Tree Pattern
局部子问题独立 -> DP / BURS

Chapter 4.3
Program DAG / Machine Tree Pattern
shared computation -> share / duplicate / fold -> 一般 optimal selection NP-hard

Chapter 4.4
Program DAG / Machine DAG/Multi-output Pattern
除了 shared computation，还必须联合选择多个 observable effects
RT splitting / recombination -> IP / CP / MWIS
```

### FRT

FRT，将指令表达拆分成Tree以及不能满足所有情况，FRT是一种更加丰富的指令描述。

可以描述包括指令在什么硬件上运行，什么寄存器组上运行，以及指令拆分成FRT之后产生的限制，等。

| 字段 | 含义 |
| --- | --- |
| `Op` | 当前 DFG node 的 operation，例如 `+`, `*` |
| `D` | 结果最后落在哪里 |
| `U_i` | 每个 operand 从哪里取得 |
| `F` | functional unit |
| `C` | cost，论文中主要是执行 cycle 数 |
| `T` | machine instruction **type** |
| `CS` | 上述变量之间的约束 |

FRT的拼接也不仅仅是一个指令选择问题，而是：

```
每个 operation 的：storage choice / instruction-type choice / FU choice / cost choice / virtual-intermediate choice
全部先保持未定
通过跨 operation 的 transfer / virtual-storage / resource / instruction-type constraints
最终形成普通 instructions 或形成可以 compact 成 complex instruction 的 RT chain
```

### 从 DAG 到 graph

DAG 无法表示环，也就只能在BB中进行识别，无法跨BB进行完整优化。加入环进行function级别优化，需要升级到一般graph表示。

一般graph无法继续拆解成tree进行匹配，需要进行子树匹配。

- 一般穷举方法：将每一种子树匹配进行覆盖尝试，运算量过大，但是其他方法都是对穷举方法的运算量优化。
- Ullmann：对每一个指令提供一个机器pattern，构造一个“pattern 节点 × program graph 节点”的候选矩阵：

```
             program nodes
           n1 n2 n3 n4 n5 ...
pattern p1  1  0  1  0  0
pattern p2  0  1  0  1  0
pattern p3  0  0  1  0  1
```

表示指令每一个part可以对应program中哪些指令，逐渐对被排除的指令选择进行删除。

- VF2：强调“从一个已经匹配的局部区域向外扩展”，更换constraints的表达方式。

```
Ullmann: 维护“每个 pattern node 可以对应整个 program 中哪些 node”，全局候选矩阵逐渐收缩。
VF2: 先绑定一小部分，从当前 partial match 的边界向外长，失败就 backtrack。
```

- 所有以上方法都需要对最后剩余的constraints进行选择，covering表达保证没有遗漏，需要使用CP（未深入了解）。
- CP的替代方案PBQP：graphic node连接增加cost matrix，主要适合：（未深入了解）

```
每个 node 选一个 choice
+
node 本身有 cost
+
edge 两端 choice combination 有 cost
```

## SelectionDAG

### 构建

逐个BB将IR转换为SDNode和SDValue。

`SelectionDAGISel::SelectBasicBlock()` 会遍历一个 LLVM IR basic block：

```
for (...) {
    SDB->visit(*I);
}
```

operator -> SDNode，图的节点。

value -> SDValue，图节点的输入/输入，edge上流动SDValue，type信息在Node中。

```
SDValue = {
    SDNode *Node;
    unsigned ResNo;
}
```

即：

```
哪个 node
+
这个 node 的第几个 result
```

### 特殊 SDValue

#### Chain

chain，表示值的依赖关系，MVT::Other 类型。

全 DAG 的副作用可达性/排序骨架。

一个普通 load 可以抽象成：

```
                  +---------+
chain-in ───────→ |         | ─────→ result #0 : i32
p        ───────→ |  LOAD   |
                  |         | ─────→ result #1 : MVT::Other
                  +---------+
```

其中 Entry node 的 opcode 是：`ISD::EntryToken`。它是 chain DAG 的起点。

#### Glue

glue，表示几个SDNode需要一起调度，MVT::Glue类型。

glue 基本上是线性的。

| | Chain | Glue |
| --- | --- | --- |
| 类型 | `MVT::Other` | `MVT::Glue` |
| 表达 | effect/order | tight scheduling relation |
| 常见于 | load/store/call/ret | target-specific coupled operations |
| 是否允许中间插其他节点 | 通常可以 | 通常不希望/被 grouped |
| 是否可汇合 | 可以，`TokenFactor` | 通常线性 |
| scheduler 含义 | dependency edge | glued nodes 成一个 SUnit |

### 整体流程

```
LLVM IR -> SelectionDAGBuilder -> initial subject DAG -> Combine
-> Type Legalization -> Combine -> Operation Legalization -> Combine
-> 真正 instruction selection -> DoInstructionSelection() -> Target::Select(Node)
-> handwritten special cases 或 generated SelectCode(Node) -> root opcode dispatch
-> structural/type/predicate matching -> ComplexPattern checks -> foldability checks
-> Emit/Morph MachineSDNode -> replace old DAG uses -> selected Machine DAG
```

#### 各阶段职责

- Combine: 对DAG进行简单优化，如常量传播，x+0=x，等，让其他pass专注于自己要做的事情。
- Type Legalization：对于instruction无法处理的type进行处理，标注Custom，后续拆分等等。
- Operation Legalization：对于type合法，operation整体不合法的情况处理，标注Custom。

#### Targer::Select

- 带有手写和TableGen的混合在一起。
- 所有Pattern会进行排序，按照顺序进行match。
- 没有其他约定的情况下，跨sharing node进行优化将不进行，也就是Node的use多于1个，就不能成为一个复杂指令的中间步骤被淹没，也就不会duplicate。
- 不同平台可以通过override LLVM的方法，实现对sharing node的处理，一般是把决策推迟到 MachineIR/MachineInstr 层，用 target scheduling model、critical path 和 resource pressure 做局部 alternative evaluation。

```
第一层：SelectionDAG matcher
shared producer -> 默认 hasOneUse -> 不 duplicate
```

这是最便宜、最稳定的 baseline。X86 甚至自己的 IsProfitableToFold() 仍然首先直接拒绝 `!N.hasOneUse()`。

```
第二层：all-users analysis
shared producer -> 分析所有 uses -> 如果所有 uses 都可以一起转成复杂指令 -> 整体 contraction
```

AMDGPU 的 FMA/FMAD handling 是很好的现实例子。

```
第三层：MachineCombiner
已有 MachineInstr -> 产生 alternative sequence -> 真实 target scheduling model
-> critical path / resource pressure / register pressure / code size -> 决定是否替换
```

AArch64 / PowerPC 都在使用这套机制。PowerPC甚至只在 aggressive optimization 下启用部分昂贵的 FMA MachineCombiner 逻辑。

5. chain和glue信息会在DAG中保留，直到scheduleing结束。
6. glue不会保证命令在优化后完全挨在一起，需要的话可以定制虚拟的instruction进行覆盖来实现。

## GlobalISel

### 表示

用MIR表示，其中包含CFG，MathineInstr和vreg等，一个function可以完整表示（vs：SelectDAG 只能逐个BB表示）。

MathineInstr可以是相对抽象的，也可以是机器码，优化和lowering过程在同一个ir上完成，可以分开不同步骤。

```
MachineFunction
├── MachineBasicBlock bb0
│    ├── MachineInstr
│    │      ├── opcode
│    │      ├── MachineOperand
│    │      ├── MachineOperand
│    │      └── MachineMemOperand*
│    ├── MachineInstr
│    └── MachineInstr
├── MachineBasicBlock bb1
│    └── ...
├── MachineRegisterInfo
│    ├── virtual registers
│    ├── register classes/banks/types
│    └── def-use chains
├── MachineFrameInfo
└── target/subtarget information
```

其中MachineBasicBlock中的MachineInstr是一个有序的list，因此不再需要chain/glue等关系表示。

### 基础原理

仍然以单个MachineInster和greedy算法为中心，但是表示能力比SelectIDAG高级。

```
Legalizer -> RegBankSelect -> InstructionSelect -> MachineCombiner -> Scheduler -> RA
```

representation scope = global / whole MachineFunction

optimization scope = mostly local/greedy
