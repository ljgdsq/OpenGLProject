#pragma once
#include "../Render/Renderer.h"
#include "../Base/BaseStruct.hpp"
class Ex_Lighting_Tex:public Renderer
{
public:
    void Draw();
    void InitData();
    Ex_Lighting_Tex();
    Size winSize;
    Shader* lightShader;
    class Image* image;
    class Image* image2;
};

