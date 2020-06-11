#pragma once
#include "../Render/Renderer.h"
#include <string>
class Plane :public Renderer
{
    RENDERER_BASE_DECLARE(Plane);
public:
    Plane(std::string imagePath);
private:
    class Image* image;
    std::string imagePath;
};
