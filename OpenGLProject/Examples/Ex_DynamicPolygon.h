#pragma once
#include <glm/glm.hpp>
#include "../Render/Renderer.h"
#include "../Base/BaseStruct.hpp"
class Ex_DynamicPolygon :public Renderer
{
public:
    Ex_DynamicPolygon();
    void Draw() override;
    virtual void InitData() override;
    Size winSize;
    int vertexCount;
    float height;
    unsigned int sideVAO;
    unsigned int sideVBO;
    unsigned int sideEBO;

    void ChangeData();
    int curSide;
    int maxSide;
    int minSide;
    float changeSpeed;
    float time;
    bool isDirty;
};

