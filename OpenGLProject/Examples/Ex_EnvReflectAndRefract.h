#pragma once
#include "ExampleCommomHeader.h"
class Ex_EnvReflectAndRefract:public Renderer
{
    RENDERER_BASE_DECLARE(Ex_EnvReflectAndRefract)
public:
    class Skybox* skybox;
    class Cube* cube;

};

