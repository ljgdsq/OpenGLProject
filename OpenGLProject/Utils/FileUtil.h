#pragma once
#include "../CommonHeader.h"
class FileUtil:public Singleton<FileUtil>
{
public:
    std::string Resource = "Resources";
    std::string LoadFromFile(std::string path);
    std::string LoadFromProjectResource(std::string name);
    std::string GetResourceFullPath(std::string name);
};

