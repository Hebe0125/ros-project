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