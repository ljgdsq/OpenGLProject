#pragma once
#include <vector>
#include <map>
#include "ExampleCommomHeader.h"

class Ex_Blending: public Renderer
{
    RENDERER_BASE_DECLARE(Ex_Blending);
public:
    unsigned int tex1;
    unsigned int tex2;
    unsigned int tex3;
    unsigned int planeVAO, planeVBO;
    unsigned int grassVAO, grassVBO,grassEBO;
    Shader* grassShader;
    std::vector<glm::vec3> vegetation;

    std::map<float, glm::vec3> vegetationMap;

    class Cube* cube;
    class Plane* plane;
};

