#pragma once
#include "../GLEnvHeader.h"
class Image
{
public:
    enum  RepeatMode
    {
        REPEAT=GL_REPEAT,
        MIRROR_REPEAT=GL_MIRRORED_REPEAT,
        CLAMP_TO_EDGE=GL_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER=GL_CLAMP_TO_BORDER
    };

    enum  FilterMode {
        NEAREST= GL_NEAREST,
        LINEAR= GL_LINEAR
    };
private:
    int width;
    int height;
    int channel;
    unsigned char* data;
    unsigned int texture;
    bool genMipmap;
    bool releaseData;
    bool flipY;
    RepeatMode repeatMode;
    FilterMode filterMode;

    void ReleaseGLTexture();
public:

    Image(int width, int height, int channel, unsigned char* data,bool releaseData=false,bool flipY=false);

    inline int GetWidth() const {
        return width;
    }

    inline int GetHeight() const {
        return height;
    }

    inline int GetChannel() const {
        return channel;
    }

    inline int GetTexture() const {
        return texture;
    }

    void SetFilterMode(FilterMode filterMode);
    void SetRepeatMode(RepeatMode repeatMode);
    void SetGenMipmap(bool gen);
    void GenTexture();
    void Use();
};

