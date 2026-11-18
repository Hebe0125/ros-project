// RosCore.cpp —— ROS 核心管理模块的实现
#include "RosCore.h"
#include "Node.h"
#include "Subscriber.h"
#include "Message.h"
#include "Exceptions.h"
#include <iostream>

using namespace std;

// 静态成员初始化：初始时不指向任何实例
RosCore* RosCore::instance = nullptr;

RosCore::RosCore() {}

RosCore* RosCore::getInstance() {
    if (instance == nullptr) {      // 首次调用时创建唯一实例
        instance = new RosCore();
    }
    return instance;                // 之后所有调用返回的都是同一个实例
}

void RosCore::registerNode(Node* n) {
    // 校验重复注册：已存在同名节点则抛出节点异常
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i]->getName() == n->getName()) {
            throw NodeException("节点注册失败：节点名 \"" + n->getName() + "\" 已存在");
        }
    }
    nodes.push_back(n);
}

void RosCore::registerSubscriber(const string& topic, Subscriber* s) {
    topic_subs[topic].push_back(s);   // 若该话题尚无记录则自动创建，再将订阅者加入列表
}

void RosCore::sendMessage(const string& topic, const string& content) {
    // 校验空消息：内容为空则抛出消息异常
    if (content.empty()) {
        throw MessageException("消息发布失败：消息内容不能为空");
    }

    // 校验话题是否存在：不存在则抛出话题异常
    // 用 find 而不是 topic_subs[topic]，后者会给不存在的话题凭空创建一条空记录
    if (topic_subs.find(topic) == topic_subs.end()) {
        throw TopicException("消息转发失败：话题 \"" + topic + "\" 不存在");
    }

    Message msg(content);   // 将内容包装为 Message，时间戳在构造时自动生成
    cout << "[RosCore] 话题 " << topic << " 收到消息，开始转发..." << endl;

    auto& subs = topic_subs[topic];   // 取出该话题的订阅者列表
    for (size_t i = 0; i < subs.size(); i++) {
        subs[i]->onMessage(msg);      // 通过基类指针调用 onMessage，体现多态
    }
}

void RosCore::shutdownAll() {
    cout << "========= RosCore 统一关闭所有节点 =========" << endl;
    for (size_t i = 0; i < nodes.size(); i++) {
        nodes[i]->shutdown();   // 通过基类指针调用 shutdown，由各子类执行各自的关闭逻辑
    }
}
