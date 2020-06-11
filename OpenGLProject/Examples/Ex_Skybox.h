#pragma once
#include "ExampleCommomHeader.h"
#include <vector>
#include <string>
class Ex_Skybox:public Renderer
{
    RENDERER_BASE_DECLARE(Ex_Skybox)

private:
    class Skybox* skybox;
    class Cube* cube;
};

