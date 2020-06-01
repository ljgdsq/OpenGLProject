#pragma once
#include "../Render/Renderer.h"
#include "../Base/BaseStruct.hpp"
class Ex_Lighting :public Renderer
{
public:
    void Draw();
    void InitData();
    Ex_Lighting();
    Size winSize;
    Shader* lightShader;
};


