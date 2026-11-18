// RosCore.cpp —— ROS 核心管理模块的实现
#include "RosCore.h"
#include "Node.h"
#include "Subscriber.h"
#include "Message.h"
#include "Exceptions.h"
#include "Logger.h"
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

void RosCore::removeNode(Node* n) {
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i] == n) {
            nodes.erase(nodes.begin() + i);   // 从统一管理的名单中移除
            Logger::log(LOG_INFO, "RosCore", "节点 " + n->getName() + " 已从核心移除");
            return;
        }
    }
    Logger::log(LOG_WARN, "RosCore", "尝试移除的节点 " + n->getName() + " 不在注册列表中");
}

void RosCore::unregisterSubscriber(const string& topic, Subscriber* s) {
    auto it = topic_subs.find(topic);   // 查找该话题的订阅者列表
    if (it == topic_subs.end()) {
        Logger::log(LOG_WARN, "RosCore", "话题 " + topic + " 不存在，无法移除订阅者");
        return;
    }
    vector<Subscriber*>& list = it->second;
    for (size_t i = 0; i < list.size(); i++) {
        if (list[i] == s) {
            list.erase(list.begin() + i);   // 从映射表中移除，之后该话题的消息不再转发给它
            return;
        }
    }
    Logger::log(LOG_WARN, "RosCore", "该订阅者未订阅话题 " + topic + "，无法移除");
}

void RosCore::sendMessage(const string& topic, const string& content) {
    // 校验空消息：内容为空则抛出消息异常
    if (content.empty()) {
        throw MessageException("消息发布失败：消息内容不能为空");
    }
    sendMessage(topic, Message(content));   // 包装成消息对象后走统一转发
}

void RosCore::sendMessage(const string& topic, const Message& msg) {
    // 校验话题是否存在：不存在则抛出话题异常
    // 用 find 而不是 topic_subs[topic]，后者会给不存在的话题凭空创建一条空记录
    if (topic_subs.find(topic) == topic_subs.end()) {
        throw TopicException("消息转发失败：话题 \"" + topic + "\" 不存在");
    }

    Logger::log(LOG_INFO, "RosCore", "话题 " + topic + " 收到消息，开始转发...");

    auto& subs = topic_subs[topic];   // 取出该话题的订阅者列表
    for (size_t i = 0; i < subs.size(); i++) {
        subs[i]->onMessage(msg);      // msg 可能是 Message 或其子类，getContent 按实际类型执行（多态）
    }
}

void RosCore::shutdownAll() {
    if (nodes.empty()) {
        Logger::log(LOG_WARN, "RosCore", "当前没有任何已注册节点，无需关闭");
        return;
    }
    Logger::log(LOG_INFO, "RosCore", "统一关闭所有节点，共 "
                + to_string(nodes.size()) + " 个");
    for (size_t i = 0; i < nodes.size(); i++) {
        nodes[i]->shutdown();   // 通过基类指针调用 shutdown，由各子类执行各自的关闭逻辑
    }
}
