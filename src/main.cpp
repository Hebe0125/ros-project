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

/*
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

// main.cpp —— M5 阶段：完整链路测试（发布 -> RosCore 转发 -> 订阅者收到）
#include <iostream>
#include "Publisher.h"
#include "Subscriber.h"
#include "RosCore.h"

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

    cout << "--------- 统一关闭 ---------" << endl;
    RosCore::getInstance()->shutdownAll();   // 一句话关掉所有节点，不再挨个 shutdown

    return 0;
}
    */
   // main.cpp —— M6 阶段：多话题演示
// 验证点：消息只转发给订阅了对应话题的节点，不同话题之间互不干扰
#include <iostream>
#include "Publisher.h"
#include "Subscriber.h"
#include "RosCore.h"

using namespace std;

int main() {
    // 话题 1：/chatter —— 一个发布者，两个订阅者
    Publisher chatPub("chat_pub", "/chatter");
    Subscriber chatSub1("chat_sub1", "/chatter");
    Subscriber chatSub2("chat_sub2", "/chatter");

    // 话题 2：/battery —— 一个发布者，一个订阅者
    Publisher battPub("batt_pub", "/battery");
    Subscriber battSub("batt_sub", "/battery");

    chatPub.init();
    chatSub1.init();
    chatSub2.init();
    battPub.init();
    battSub.init();

    cout << "--------- 话题 1：/chatter ---------" << endl;
    chatPub.publish("hello 1");
    chatPub.publish("hello 2");

    cout << "--------- 话题 2：/battery ---------" << endl;
    battPub.publish("电量 85%");

    cout << "--------- 统一关闭 ---------" << endl;
    RosCore::getInstance()->shutdownAll();

    return 0;
}
