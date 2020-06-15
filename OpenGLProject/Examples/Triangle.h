#pragma once
#include "../Render/Renderer.h"



class Triangle:public Renderer
{
public:
    Triangle();

    void Draw() override;


    // Inherited via Renderer
    virtual void InitData() override;

};

