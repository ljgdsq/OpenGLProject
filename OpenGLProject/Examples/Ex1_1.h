#pragma once
#include "../Render/Renderer.h"
class Ex1_1:public Renderer
{
public:
    Ex1_1();
    virtual  void InitData() override;
    virtual void Draw() override;
};

