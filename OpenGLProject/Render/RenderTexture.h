#pragma once
#include "Renderer.h"
class RenderTexture:public Renderer
{
    RENDERER_BASE_DECLARE(RenderTexture)
public:
    int winWidth;
    int winHeight;
    unsigned int framebuffer;
};

