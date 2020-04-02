#include "LogUtil.h"
#include <iostream>


LogUtil::LogUtil()
{
    _logLevel = VERBOSE;
}

void LogUtil::Verbose(std::string msg)
{
    if (_logLevel>= VERBOSE)
    {
        std::cout << "" << std::endl;
    }
}

void LogUtil::Info(std::string msg)
{
    if (_logLevel >= INFO)
    {
        std::cout << "" << std::endl;
    }
}

void LogUtil::Warn(std::string msg)
{
    if (_logLevel >= WARN)
    {
        std::cout << "" << std::endl;
    }
}

void LogUtil::Error(std::string msg)
{
    if (_logLevel >= ERROR)
    {
        std::cout << "" << std::endl;
    }
}

void LogUtil::SetLogLevel(LogLevel level)
{
    _logLevel = level;
}
