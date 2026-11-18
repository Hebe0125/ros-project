// Logger.h —— 分级日志工具（加分项：INFO/WARN/ERROR 分级 + 日志持久化）
// 统一日志出口：控制台输出与文件写入使用同一格式，便于调试与留存
#ifndef LOGGER_H
#define LOGGER_H

#include <string>

// 日志级别：信息 / 警告 / 错误
enum LogLevel { LOG_INFO, LOG_WARN, LOG_ERROR };

class Logger {
public:
    // 设置日志文件路径；设置后所有日志追加写入该文件（持久化）
    static void setFile(const std::string& path);

    // 记录一条日志：级别 + 模块名 + 内容，同时输出到控制台和日志文件
    static void log(LogLevel level, const std::string& module, const std::string& message);

private:
    static std::string logFile;   // 日志文件路径，为空表示只输出到控制台
};

#endif
