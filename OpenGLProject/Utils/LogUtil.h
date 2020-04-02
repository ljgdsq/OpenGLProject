#pragma once
#include <string>

#include "../Base/Singleton.h"

class LogUtil:public Singleton<LogUtil>
{
public:
    enum  LogLevel
    {
        NONE=0,
        VERBOSE=1,
        INFO=2,
        WARN=3,
        ERROR=4
    };
    LogUtil();
public:
    void Verbose(std::string msg);
    void Info(std::string msg);
    void Warn(std::string msg);
    void Error(std::string msg);

    void SetLogLevel(LogLevel level);

private:
    LogLevel _logLevel;
};

