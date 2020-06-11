#pragma once
#include "../Render/Renderer.h"
#include <string>
class Cube:public Renderer
{
    RENDERER_BASE_DECLARE(Cube);
public:
    Cube(std::string imagePath);
private:
    class Image* image;
    std::string imagePath;


};

