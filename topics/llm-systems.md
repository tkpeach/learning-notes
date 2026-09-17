# LLM Systems

## DeepSeek Harness

插件：基于Service，通过配置inject声明依赖关系；默认提供的插件中AgentLoop依赖于tools等基础功能插件。

生命周期：提供了一套类似RAII的生命周期管理，插件实例关联一个Fiber，通过`effect()`初始化资源，`effect()`返回一个用于资源销毁的函数，在Fiber unload时候销毁相应资源。

Context: 通过mixin代理管理Service, Event等, 管理插件。

Event: on, waterfall, emit, parallel等多种事件插入机制，供插件使用。

AgentLoop: 是一个插件，同时也是一个抽象类的具体实现，全局只能有一个类似的Loop插件。

## Jalapeño

OpenAI 设计的专为LLM推理优化的芯片，仅用于推理，不考虑训练、图形等。

core slice设计了local HBM，让设计尽量达到大量内存在local，减少搬移；同时减少整体shared mem带来的带宽无法充分利用的问题。

collective fabric 是一条专门为“多个计算单元协同交换数据”设计的通信快速路径，为AllReduce设计，可以在硬件上走单独的通道，原来的相关优化是软件上的。

如MoE场景下，不同core slice存储不同Experts，对应权重固定在local。

编程分层，相关复杂度通过API包装（无具体披露内容）。
