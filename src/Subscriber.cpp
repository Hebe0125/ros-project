// Subscriber.cpp —— Subscriber 的实现
#include "Subscriber.h"
#include <iostream>

using namespace std;

Subscriber::Subscriber(const string& nodeName, const string& topicName)
    : Node(nodeName), topic(topicName) {}

void Subscriber::init() {
    cout << "[订阅者 " << name << "] 初始化完成，订阅话题: " << topic << endl;
    // M5 阶段：这里会改成向 ROS 核心注册订阅
}

void Subscriber::shutdown() {
    cout << "[订阅者 " << name << "] 已关闭" << endl;
}

void Subscriber::onMessage(const Message& msg) {
    cout << "[订阅者 " << name << "] 收到消息: " << msg.getContent()
         << "  [" << msg.getTimeStamp() << "]" << endl;
}
