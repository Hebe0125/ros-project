// Node.h —— 节点抽象基类：规定所有节点的统一接口
#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
protected:
    std::string name;   // 节点唯一名称，子类可以直接访问

public:
    explicit Node(const std::string& nodeName);
    virtual ~Node();    // 虚析构函数，见下方讲解

    std::string getName() const;

    virtual void init() = 0;      // 纯虚函数：子类必须实现自己的初始化
    virtual void shutdown() = 0;  // 纯虚函数：子类必须实现自己的关闭
};

#endif