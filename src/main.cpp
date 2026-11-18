/*
// main.cpp —— M2 阶段：测试 Message 类
#include <iostream>
#include "Message.h"

using namespace std;

int main() {
    Message m("hello 1");

    cout << "消息内容: " << m.getContent() << endl;
    cout << "发送时间: " << m.getTimeStamp() << endl;

    return 0;
}
*/


// main.cpp —— M4 阶段：测试 Publisher / Subscriber
#include <iostream>
#include "Publisher.h"
#include "Subscriber.h"

using namespace std;

int main() {
    Publisher pub("pub1", "/chatter");
    Subscriber sub1("sub1", "/chatter");
    Subscriber sub2("sub2", "/chatter");

    pub.init();
    sub1.init();
    sub2.init();

    cout << "--------- 发布消息 ---------" << endl;
    pub.publish("hello 1");
    pub.publish("hello 2");

    cout << "--------- 关闭节点 ---------" << endl;
    pub.shutdown();
    sub1.shutdown();
    sub2.shutdown();

    return 0;
}
