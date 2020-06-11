#pragma once
#include "Renderer.h"
class ScreenRenderer:public Renderer
{
    RENDERER_BASE_DECLARE(ScreenRenderer);
public:
    void SetTexture(int texture);
    virtual void InitShader();
private:
    int texture;
};

