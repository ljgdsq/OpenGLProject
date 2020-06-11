#pragma once
#include "ExampleCommomHeader.h"

class Ex_FrameBuffer:public Renderer
{
    RENDERER_BASE_DECLARE(Ex_FrameBuffer);

private:
    class Cube* cube1;
    class Cube* cube2;
    class Plane* plane;
    Size winSize;
    unsigned int framebuffer;

    unsigned int textureColorbuffer;
    class ScreenRenderer* screen;
};

