// TempHumidityMessage.h —— 自定义温湿度消息类型（加分项）
// 继承 Message 并重写 getContent：消息内容按温湿度格式输出，
// 体现消息类型可扩展（自定义消息类型）与多态的又一次应用
#ifndef TEMPHUMIDITYMESSAGE_H
#define TEMPHUMIDITYMESSAGE_H

#include "Message.h"
#include <string>
#include <sstream>

class TempHumidityMessage : public Message {
private:
    double temperature;   // 温度（摄氏度）
    double humidity;      // 湿度（百分比）

public:
    // 构造：传入温湿度数值，基类部分存储消息类型标识并自动生成时间戳
    TempHumidityMessage(double temp, double hum)
        : Message("[温湿度数据]"), temperature(temp), humidity(hum) {}

    // 重写基类 getContent：把温湿度数值拼成可读字符串
    virtual std::string getContent() const {
        std::ostringstream oss;
        oss << "温度 " << temperature << "°C / 湿度 " << humidity << "%";
        return oss.str();
    }
};

#endif
