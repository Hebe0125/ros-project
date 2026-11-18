// Subscriber.h —— 订阅者：继承 Node，接收并打印消息
#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "Node.h"
#include "Message.h"

class Subscriber : public Node {
private:
    std::string topic;   // 订阅的话题

public:
    Subscriber(const std::string& nodeName, const std::string& topicName);

    void init() override;
    void shutdown() override;

    void onMessage(const Message& msg);   // 回调：收到消息时被调用
};

#endif
