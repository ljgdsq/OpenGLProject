#pragma once
#include "../CommonHeader.h"
class ColorTriangle:public Renderer
{
public:
    
    virtual void Draw() override;
    ColorTriangle(Shader*shader);
    void InitData() override;

    ColorTriangle();
};

