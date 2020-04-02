#pragma once
#include "../CommonHeader.h"

#include <map>

class IniReader:public Singleton<IniReader>
{
public:
    std::map<std::string, std::string> LoadProjectConfig();
};

