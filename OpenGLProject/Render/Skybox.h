#pragma once
#include <vector>
#include <string>
#include "Renderer.h"
#include "../Base/BaseStruct.hpp"
class Skybox:public Renderer
{
    RENDERER_BASE_DECLARE(Skybox)
public:
    void SetImages(const std::vector<std::string>& faces);
private:
    unsigned int cubeTexture;
    unsigned int LoadCubemap(const std::vector<std::string>& faces);
    Size winSize;
};

