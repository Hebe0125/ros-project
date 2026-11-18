// Message.cpp —— Message 类的实现
#include "Message.h"
#include <ctime>

using namespace std;  // 之后可以直接写 string，不用敲 std::

// 构造函数：初始化列表把传入的内容存起来，再自动生成时间戳
Message::Message(const string& msgData) : content(msgData) {
    time_t now = time(nullptr);       // 拿到当前时刻（一个时间数字）
    tm* t = localtime(&now);          // 换算成年月日时分秒
    char buf[20] = {0};
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);  // 按格式拼成字符串
    timestamp = buf;
}

string Message::getContent() const { return content; }
string Message::getTimeStamp() const { return timestamp; }