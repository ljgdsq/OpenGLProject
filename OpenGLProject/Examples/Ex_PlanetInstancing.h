#pragma once
#include "ExampleCommomHeader.h"
#include "../Base/Model.h"
using namespace GL3D;

#define MAX_ROCK 10000
class Ex_PlanetInstancing :public Renderer
{
    RENDERER_BASE_DECLARE(Ex_PlanetInstancing)
private:
     GL3D::Model* rock;
    GL3D::Model* planet;

    Shader* rockShader;
    int amount ;
    glm::mat4 *modelMatrices;
};

