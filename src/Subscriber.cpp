// Subscriber.cpp —— Subscriber 类的实现
#include "Subscriber.h"
#include "RosCore.h"
#include "Logger.h"

using namespace std;

Subscriber::Subscriber(const string& nodeName, const string& topicName)
    : Node(nodeName), topic(topicName) {}

void Subscriber::init() {
    RosCore* ros = RosCore::getInstance();
    ros->registerNode(this);               // 向 ROS 核心注册节点
    ros->registerSubscriber(topic, this);  // 登记订阅关系：本节点订阅 topic 话题
    Logger::log(LOG_INFO, "订阅者 " + name, "初始化完成，订阅话题: " + topic);
}

void Subscriber::shutdown() {
    Logger::log(LOG_INFO, "订阅者 " + name, "已关闭");
}

void Subscriber::onMessage(const Message& msg) {
    Logger::log(LOG_INFO, "订阅者 " + name, "收到消息: " + msg.getContent()
                + "  [" + msg.getTimeStamp() + "]");
}
