#include "Image.h"
#include "../Utils/LogUtil.h"
#include <cstdlib>
void Image::GenTexture()
{
    if (texture!= GL_INVALID_VALUE)
    {
        LogUtil::GetInstance()->Error("Image already generated texture!");
        return;
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeatMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeatMode);



    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

    int filter = filterMode;
    if (genMipmap)
    {
        if (filter == GL_LINEAR)
        {
            filter = GL_LINEAR_MIPMAP_NEAREST; //TODO just 2 mode
        }
        else 
        {
            filter = GL_NEAREST_MIPMAP_LINEAR;
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    }
    if (data)
    {
        int ch = channel == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, ch, width, height, 0, ch, GL_UNSIGNED_BYTE, data);
        if (genMipmap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        if (releaseData)
        {
            free(this->data);
        }
    }
}

void Image::ReleaseGLTexture()
{
    glDeleteTextures(1, &texture);
}

Image::Image(int width, int height, int channel, unsigned char* data,bool releaseData, bool flipY)
{
    this->width = width;
    this->height = height;
    this->channel = channel;
    this->data = data;
    this->genMipmap = false;
    this->texture = GL_INVALID_VALUE;
    this->releaseData = releaseData;
    this->flipY = flipY;
    repeatMode = RepeatMode::REPEAT;
    filterMode = FilterMode::LINEAR;
}

void Image::SetFilterMode(FilterMode filterMode)
{
    this->filterMode = filterMode;
}

void Image::SetRepeatMode(RepeatMode repeatMode)
{
    this->repeatMode = repeatMode;
}

void Image::SetGenMipmap(bool gen)
{
    this->genMipmap = gen;
}

void Image::Use()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}
