#pragma once
#include "../Render/Renderer.h"
class Ex2_1:public Renderer
{
public:
    Ex2_1();

    virtual void Draw() override;
    virtual void InitData() override;
};

