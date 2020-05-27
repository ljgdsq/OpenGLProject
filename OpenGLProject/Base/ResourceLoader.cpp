#define STB_IMAGE_IMPLEMENTATION
#include "ResourceLoader.h"
#include "../Utils/FileUtil.h"
#include "stb_image.h"

Image* ResourceLoader::LoadImage(const char* name, bool flipY)
{
    auto fullPath=FileUtil::GetInstance()->GetResourceFullPath(name);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(!flipY);
    unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);
    Image* image = new Image(width, height, nrChannels, data,true, flipY);
    return image;
}

