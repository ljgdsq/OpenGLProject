#define STB_IMAGE_IMPLEMENTATION
#include "ResourceLoader.h"
#include "../Utils/FileUtil.h"
#include "stb_image.h"

Image* ResourceLoader::LoadImage(const char* name, bool flipY)
{
    
    auto fullPath=FileUtil::GetInstance()->GetResourceImageFullPath(name);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(!flipY);
    unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);
    if (data==nullptr)
    {
        LogUtil::GetInstance()->Error("LoadImage failed! :" + fullPath);
        return nullptr;
    }
    Image* image = new Image(width, height, nrChannels, data,true, flipY);
    return image;
}

