// Publisher.cpp —— Publisher 类的实现
#include "Publisher.h"
#include "RosCore.h"
#include "Message.h"
#include "Logger.h"

using namespace std;

Publisher::Publisher(const string& nodeName, const string& topicName)
    : Node(nodeName), topic(topicName) {}

void Publisher::init() {
    RosCore::getInstance()->registerNode(this);   // 向 ROS 核心注册
    Logger::log(LOG_INFO, "发布者 " + name, "初始化完成，话题: " + topic);
}

void Publisher::shutdown() {
    Logger::log(LOG_INFO, "发布者 " + name, "已关闭");
}

void Publisher::publish(const string& msgData) {
    Logger::log(LOG_INFO, "发布者 " + name, "发布消息: " + msgData);
    RosCore::getInstance()->sendMessage(topic, msgData);   // 交给 ROS 核心转发
}

void Publisher::publish(const Message& msg) {
    Logger::log(LOG_INFO, "发布者 " + name, "发布消息: " + msg.getContent());
    RosCore::getInstance()->sendMessage(topic, msg);   // 消息对象原样交给核心转发，保留其实际类型
}
