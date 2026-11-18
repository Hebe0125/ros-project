// Message.h —— 消息类：内容 + 自动生成的时间戳
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message {
private:
    std::string content;    // 消息内容，创建后不再修改
    std::string timestamp;  // 发送时间 YYYY-MM-DD HH:MM:SS

public:
    explicit Message(const std::string& msgData);  // 构造函数：传入消息内容
    std::string getContent() const;    // 只读接口：取内容
    std::string getTimeStamp() const;  // 只读接口：取时间戳
};

#endif