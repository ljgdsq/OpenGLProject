#pragma once
#include "ExampleCommomHeader.h"

//#define ANTI_ALISING 
class Ex_AntiAlising:public Renderer
{
    RENDERER_BASE_DECLARE(Ex_AntiAlising)
public:
    class Cube* cube;

    unsigned int texture;

    Size winSize;
};

