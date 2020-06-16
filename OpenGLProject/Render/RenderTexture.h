#pragma once
#include "Renderer.h"
class RenderTexture:public Renderer
{

public:
    void Draw(); 
    void InitData(); 
    RenderTexture(int width, int height);

    int width;
    int height;
    unsigned int framebuffer;
    unsigned int texture;
    void Init();

    glm::vec4 clearColor;
};

