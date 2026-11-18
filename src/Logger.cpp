// Logger.cpp —— Logger 类的实现
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

string Logger::logFile = "";   // 静态成员初始化：默认不写文件

void Logger::setFile(const string& path) {
    logFile = path;
}

// 生成当前时间字符串 YYYY-MM-DD HH:MM:SS（与 Message 的时间戳格式一致）
static string nowString() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    char buf[20] = {0};
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
    return buf;
}

// 级别名称转文字
static const char* levelName(LogLevel level) {
    switch (level) {
        case LOG_INFO:  return "INFO";
        case LOG_WARN:  return "WARN";
        case LOG_ERROR: return "ERROR";
    }
    return "INFO";
}

void Logger::log(LogLevel level, const string& module, const string& message) {
    string line = string("[") + levelName(level) + "] ["
                + nowString() + "] ["
                + module + "] " + message;

    cout << line << endl;   // 输出到控制台

    if (!logFile.empty()) {             // 若开启了持久化，追加写入文件
        ofstream file(logFile.c_str(), ios::app);
        if (file) {
            file << line << "\n";
        }
    }
}
