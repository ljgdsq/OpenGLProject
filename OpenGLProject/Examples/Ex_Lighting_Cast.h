#pragma once
#include "../Render/Renderer.h"
#include "../Base/BaseStruct.hpp"
class Ex_Lighting_Cast:public Renderer
{
public:
    void Draw();
    void InitData();
    Ex_Lighting_Cast();
    Size winSize;
    Shader* lightShader;
    class Image* image;
    class Image* image2;

    Shader* lineShader;
    unsigned int lineVAO;
    unsigned int lineVBO;
};

