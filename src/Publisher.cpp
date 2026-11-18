// Publisher.cpp —— Publisher 的实现
#include "Publisher.h"
#include "Message.h"
#include <iostream>

using namespace std;

Publisher::Publisher(const string& nodeName, const string& topicName)
    : Node(nodeName), topic(topicName) {
    // 先执行 Node(name)（父类部分造好），再初始化自己的 topic
}

void Publisher::init() {
    cout << "[发布者 " << name << "] 初始化完成，话题: " << topic << endl;
    // M5 阶段：这里会改成向 ROS 核心注册
}

void Publisher::shutdown() {
    cout << "[发布者 " << name << "] 已关闭" << endl;
}

void Publisher::publish(const string& msgData) {
    Message msg(msgData);   // 把字符串包装成 Message（时间戳自动生成）
    cout << "[发布者 " << name << "] 发布消息 -> " << msg.getContent()
         << "  [" << msg.getTimeStamp() << "]" << endl;
    // M5 阶段：这里会改成调用 RosCore 的 sendMessage 转发
}