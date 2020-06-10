#pragma once
#include "ExampleCommomHeader.h"
class Ex_StencilTest:public Renderer
{
public:
    RENDERER_BASE_DECLARE(Ex_StencilTest);
    unsigned int tex1;
    unsigned int tex2;
    unsigned int planeVAO, planeVBO;

    Shader* borderShader;
};

