# Mini ROS 发布/订阅通信系统

C++ 课程大作业。基于发布/订阅（Pub/Sub）模型实现的轻量级节点通信系统，模拟 ROS 中 Node、Topic、Message 的核心机制。

## 功能特性

- 节点管理：支持多个发布者、订阅者节点的创建与注册，由 RosCore 统一管理，输出初始化日志
- 发布/订阅通信：发布者向话题发布消息，RosCore 根据话题与订阅者的映射关系，将消息转发给该话题下的所有订阅者，实现异步通信
- 全生命周期运行：节点按流程完成初始化、消息交互、关闭
- 异常处理：面对空节点名、重复节点注册、空消息发布、不存在话题转发等非法输入，抛出语义清晰的异常并捕获处理，程序禁止崩溃

## 项目结构

| 位置 | 说明 |
|------|------|
| docs/ | 需求文档、架构设计文档（含类图）、技术文档、测试用例、用户手册 |
| src/Message.h / .cpp | 消息类：内容 + 自动生成的时间戳 |
| src/Node.h / .cpp | 节点抽象基类：纯虚函数 init()/shutdown() |
| src/Publisher.h / .cpp | 发布者节点：继承 Node，publish() 发布消息 |
| src/Subscriber.h / .cpp | 订阅者节点：继承 Node，onMessage() 接收消息 |
| src/RosCore.h / .cpp | 核心单例：管理节点注册与话题-订阅者映射，负责消息转发与统一关闭 |
| src/Exceptions.h | 自定义异常类：NodeException / TopicException / MessageException |
| src/main.cpp | 入口：功能演示与异常场景验证 |
| .vscode/tasks.json | 一键编译运行配置 |
## 编译与运行

1. 使用 VSCode 打开项目文件夹
2. 按 Ctrl+Shift+B 执行编译任务，自动编译 src 目录下全部源文件，生成 ros.exe
3. 在 VSCode 终端中执行任务 run ros（或直接输入 .\ros.exe），运行程序查看输出

## 涉及的主要 C++ 知识点

封装（类与访问权限）、继承与多态（基类指针调用虚函数）、纯虚函数与抽象类、单例模式、STL 容器（map / vector）、异常处理（throw / try / catch）。