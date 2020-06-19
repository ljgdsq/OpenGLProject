#pragma once
#include "../CommonHeader.h"
class FileUtil:public Singleton<FileUtil>
{
public:
    std::string Resource = "Resources";
    std::string LoadStringFromFile(std::string path);
    std::string LoadStringFromProjectResource(std::string name);
    std::string GetResourceFullPath(std::string name);
    std::string GetResourceImageFullPath(std::string name);
    std::string GetResourceFontFullPath(std::string name);
   
};

