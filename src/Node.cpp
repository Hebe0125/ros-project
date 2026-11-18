// Node.cpp —— Node 基类的实现
#include "Node.h"
#include "Exceptions.h"

Node::Node(const std::string& nodeName) {
    // 校验节点名：空名字的节点不允许创建，抛出节点异常
    if (nodeName.empty()) {
        throw NodeException("节点创建失败：节点名不能为空");
    }
    name = nodeName;
}

Node::~Node() {}

std::string Node::getName() const { return name; }