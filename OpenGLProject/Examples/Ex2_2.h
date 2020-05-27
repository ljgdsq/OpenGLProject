#pragma once
#include "../Render/Renderer.h"
class Ex2_2:public Renderer
{
public:
    Ex2_2();
    void Draw() override;
    void InitData() override;
};

