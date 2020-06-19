#pragma once
#include <string>

#include "../Base/Singleton.h"
#include "../Utils/StringUtil.h"
class LogUtil:public Singleton<LogUtil>
{
private:
    std::string Names[5] = {
        "none   ",
        "verbose",
        "info   ",
        "warn   ",
        "error  "
    };
public:
    enum  LogLevel
    {
        NONE=99,
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
    void FormatPrint(LogLevel level,std::string msg);

     std::string GetLevelSring(LogLevel level);
};

#define LOGE(msg)  LogUtil::GetInstance()->Error( toString(__FILE__)+toString(" : "+toString(__LINE__)+toString(" \n"))+toString(msg));
#define LOGW(msg)  LogUtil::GetInstance()->Warn( toString(__FILE__)+toString(" : "+toString(__LINE__)+toString(" \n"))+toString(msg));
#define LOGI(msg)  LogUtil::GetInstance()->Info( toString(__FILE__)+toString(" : "+toString(__LINE__)+toString(" \n"))+toString(msg));