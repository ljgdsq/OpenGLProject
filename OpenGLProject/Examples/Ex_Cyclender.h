#pragma once
#include <glm/glm.hpp>
#include "../Render/Renderer.h"
#include "../Base/BaseStruct.hpp"
class Ex_Cyclender:public Renderer
{
public:
    Ex_Cyclender();
    void Draw() override;
    virtual void InitData() override;
    Size winSize;
    int vertexCount;
    float height;
    unsigned int sideVAO;
    unsigned int sideVBO;
    unsigned int sideEBO;
};

