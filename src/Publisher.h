// Publisher.h —— 发布者：继承 Node，负责向话题发布消息
#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "Node.h"

class Message;   // 前向声明：publish 重载使用其引用，无需完整定义

class Publisher : public Node {
private:
    std::string topic;   // 本发布者绑定的话题

public:
    Publisher(const std::string& nodeName, const std::string& topicName);

    void init() override;      // 实现 Node 的合同
    void shutdown() override;

    void publish(const std::string& msgData);     // 发布一条文本消息
    void publish(const Message& msg);             // 发布一个消息对象（支持自定义消息类型）
};

#endif