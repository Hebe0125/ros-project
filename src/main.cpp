// main.cpp —— 程序入口
// 演示内容：发布/订阅通信、多话题隔离、动态增删节点、异常处理、分级日志
#include <iostream>
#include "Publisher.h"
#include "Subscriber.h"
#include "RosCore.h"
#include "Exceptions.h"
#include "Logger.h"

using namespace std;

int main() {
    Logger::setFile("ros_log.txt");   // 开启日志持久化：所有日志同时追加写入文件

    // 第一部分：创建节点并初始化（话题 1：/chatter，话题 2：/battery）
    Publisher pub("pub1", "/chatter");
    Subscriber sub1("sub1", "/chatter");
    Subscriber sub2("sub2", "/chatter");
    Publisher battPub("batt_pub", "/battery");
    Subscriber battSub("batt_sub", "/battery");

    pub.init();
    sub1.init();
    sub2.init();
    battPub.init();
    battSub.init();

    cout << "\n--------- 正常消息发布 ---------" << endl;
    pub.publish("hello 1");

    cout << "\n--------- 话题 2：/battery（验证按话题隔离转发） ---------" << endl;
    battPub.publish("电量 85%");

    cout << "\n--------- 动态增加节点 ---------" << endl;
    Subscriber lateSub("late_sub", "/chatter");
    lateSub.init();                            // 运行中途加入新订阅者
    pub.publish("新成员加入后的第一条消息");     // late_sub 也会收到这条消息

    cout << "\n--------- 动态移除节点 ---------" << endl;
    RosCore::getInstance()->removeNode(&lateSub);                          // 从节点名单中移除
    RosCore::getInstance()->unregisterSubscriber("/chatter", &lateSub);    // 从话题映射中移除
    lateSub.shutdown();                        // 被移除的节点自行关闭
    pub.publish("成员退出后的消息");            // 输出中不再出现 late_sub

    cout << "\n--------- 异常场景验证 ---------" << endl;
    try {
        Publisher badPub("", "/chatter");   // 名字为空，构造函数抛出 NodeException
        badPub.init();
    } catch (const NodeException& e) {
        Logger::log(LOG_ERROR, "系统", string("捕获节点异常: ") + e.what());
    }

    try {
        RosCore::getInstance()->registerNode(&pub);   // pub1 已注册过，重复注册非法
    } catch (const NodeException& e) {
        Logger::log(LOG_ERROR, "系统", string("捕获节点异常: ") + e.what());
    }

    try {
        pub.publish("");   // 空消息
    } catch (const MessageException& e) {
        Logger::log(LOG_ERROR, "系统", string("捕获消息异常: ") + e.what());
    }

    try {
        RosCore::getInstance()->sendMessage("/no_such_topic", "test");   // 不存在的话题
    } catch (const TopicException& e) {
        Logger::log(LOG_ERROR, "系统", string("捕获话题异常: ") + e.what());
    }

    cout << "\n--------- 统一关闭 ---------" << endl;
    RosCore::getInstance()->shutdownAll();

    return 0;
}
