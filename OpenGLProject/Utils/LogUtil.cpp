#include "LogUtil.h"
#include <iostream>


LogUtil::LogUtil()
{
    _logLevel = VERBOSE;
}

void LogUtil::Verbose(std::string msg)
{
    FormatPrint(VERBOSE, msg);
}

void LogUtil::Info(std::string msg)
{
    FormatPrint(INFO, msg);
}

void LogUtil::Warn(std::string msg)
{
    FormatPrint(WARN, msg);
}

void LogUtil::Error(std::string msg)
{
    FormatPrint(ERROR, msg);
}

void LogUtil::SetLogLevel(LogLevel level)
{
    _logLevel = level;
}

void LogUtil::FormatPrint(LogLevel level, std::string msg)
{
    if (_logLevel <=level)
    {

        std::cout <<"["<<GetLevelSring(level)<<"] :"<< msg << std::endl;
    }
}

std::string LogUtil::GetLevelSring(LogLevel level)
{
    return Names[level];
}

