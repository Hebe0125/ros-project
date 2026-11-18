// RosCore.h —— ROS 核心管理模块（单例）
// 职责：维护话题与订阅者的映射关系，负责消息转发和所有节点的统一关闭
#ifndef ROSCORE_H
#define ROSCORE_H

#include <string>
#include <map>
#include <vector>

class Subscriber;
class Node;      // 前向声明：本类只使用这两个类的指针，无需包含其完整定义
class Message;   // 前向声明：sendMessage 重载使用其引用

class RosCore {
private:
    // 话题到该话题订阅者列表的映射，一个话题可对应多个订阅者
    std::map<std::string, std::vector<Subscriber*>> topic_subs;

    // 所有已注册节点的指针，用于统一关闭
    std::vector<Node*> nodes;

    RosCore();   // 构造函数私有化，禁止外部直接创建实例

    static RosCore* instance;   // 指向全局唯一实例的静态指针

public:
    // 获取全局唯一实例；首次调用时创建
    static RosCore* getInstance();

    // 登记节点，纳入统一管理（供 shutdownAll 使用）
    void registerNode(Node* n);

    // 为指定话题添加一个订阅者
    void registerSubscriber(const std::string& topic, Subscriber* s);

    // 运行中途移除一个已注册节点（动态增删节点）
    void removeNode(Node* n);

    // 将一个订阅者从指定话题的订阅列表中移除（动态增删节点）
    void unregisterSubscriber(const std::string& topic, Subscriber* s);

    // 将消息转发给指定话题下的所有订阅者
    void sendMessage(const std::string& topic, const std::string& content);

    // 转发一个已构造好的消息对象（支持 Message 及其子类，如自定义消息类型）
    void sendMessage(const std::string& topic, const Message& msg);

    // 遍历并统一关闭所有已注册节点
    void shutdownAll();
};

#endif
