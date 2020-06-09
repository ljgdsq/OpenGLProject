#pragma once
#include "../Render/Renderer.h"
class WorldIndicator:public Renderer
{
    RENDERER_BASE_DECLARE(WorldIndicator);
public:

    float indicator_data[18] = {
        //x
        -0.5f,0,0,  0.5f,0,0,
        //y
        0,-0.5f,0,  0,0.5f,0,
        //z
        0,0,-0.5,   0,0,0.5f,
    };
};

