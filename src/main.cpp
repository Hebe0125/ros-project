// main.cpp —— M7 阶段：异常处理演示
// 验证点：面对空节点名、重复节点注册、空消息发布、不存在话题转发
// 四种非法操作，程序能捕获异常并输出语义清晰的错误信息，禁止崩溃
#include <iostream>
#include "Publisher.h"
#include "Subscriber.h"
#include "RosCore.h"
#include "Exceptions.h"

using namespace std;

int main() {
    // 第一部分：正常流程，节点创建、初始化、发布一条消息
    Publisher pub("pub1", "/chatter");
    Subscriber sub1("sub1", "/chatter");
    Subscriber sub2("sub2", "/chatter");

    pub.init();
    sub1.init();
    sub2.init();

    cout << "--------- 正常消息发布 ---------" << endl;
    pub.publish("hello 1");

    cout << "\n--------- 异常场景 1：空节点名 ---------" << endl;
    try {
        Publisher badPub("", "/chatter");   // 名字为空，构造函数抛出 NodeException
        badPub.init();                      // throw 发生后，这一行不会被执行
    } catch (const NodeException& e) {
        cout << "[ERROR] 节点异常: " << e.what() << endl;
    }

    cout << "\n--------- 异常场景 2：重复节点注册 ---------" << endl;
    try {
        // pub1 在 init() 时已经注册过一次，再注册同名节点属于非法操作
        RosCore::getInstance()->registerNode(&pub);
    } catch (const NodeException& e) {
        cout << "[ERROR] 节点异常: " << e.what() << endl;
    }

    cout << "\n--------- 异常场景 3：发布空消息 ---------" << endl;
    try {
        pub.publish("");   // 内容为空，sendMessage 抛出 MessageException
    } catch (const MessageException& e) {
        cout << "[ERROR] 消息异常: " << e.what() << endl;
    }

    cout << "\n--------- 异常场景 4：向不存在的话题转发 ---------" << endl;
    try {
        RosCore::getInstance()->sendMessage("/no_such_topic", "test");
    } catch (const TopicException& e) {
        cout << "[ERROR] 话题异常: " << e.what() << endl;
    }

    cout << "\n--------- 四种异常均已捕获，程序继续正常运行 ---------" << endl;
    RosCore::getInstance()->shutdownAll();

    return 0;
}
