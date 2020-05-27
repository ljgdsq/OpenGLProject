#include "FileUtil.h"
#include <sstream>
#include <fstream>
#include "../Base/ProjetConfig.hpp"
using namespace std;

std::string FileUtil::LoadStringFromFile(std::string path)
{
    std::string str;
    std::ifstream ifs;
    ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        ifs.open(path);
        std::stringstream ss;
        ss << ifs.rdbuf();
        ifs.close();
        str = ss.str();
    }
    catch (std::ifstream::failure* e)
    {
        LogUtil::GetInstance()->Error("FileUtil::LoadFromFile Failed!:" + path +" reason:"+e->what());
    }

    return str;
}

std::string FileUtil::LoadStringFromProjectResource(std::string name)
{
    return LoadStringFromFile(GetResourceFullPath(name));
}

std::string FileUtil::GetResourceFullPath(std::string name)
{
    auto fullPath = ProjectConfig::GetInstance()->GetExecutePath();
    return fullPath+"/"+Resource+"/"+name;
}
