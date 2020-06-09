#pragma once
#include "ExampleCommomHeader.h"
class Ex_DepthTest:public Renderer
{
public:
    void Draw();
    void InitData();
    Ex_DepthTest();

    unsigned int tex1;
    unsigned int tex2;
    unsigned int planeVAO, planeVBO;
};
