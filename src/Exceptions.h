// Exceptions.h —— 自定义异常类（加分项）
// 继承标准库的 std::runtime_error，复用其保存错误信息的能力，
// 通过 what() 方法可以统一获取错误描述
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

// 节点异常：空节点名、重复节点注册等
class NodeException : public std::runtime_error {
public:
    explicit NodeException(const std::string& msg) : std::runtime_error(msg) {}
};

// 话题异常：向不存在的话题转发消息等
class TopicException : public std::runtime_error {
public:
    explicit TopicException(const std::string& msg) : std::runtime_error(msg) {}
};

// 消息异常：发布空消息等
class MessageException : public std::runtime_error {
public:
    explicit MessageException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif