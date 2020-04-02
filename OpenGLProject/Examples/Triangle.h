#pragma once
#include "../Render/Renderer.h"

class Triangle:public Renderer
{
public:
    void InitDrawData();
    Triangle();

    void Draw() override;
};

