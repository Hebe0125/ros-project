// Node.cpp —— Node 基类的实现
#include "Node.h"

Node::Node(const std::string& nodeName) : name(nodeName) {}

Node::~Node() {}

std::string Node::getName() const { return name; }