#pragma once
#include "../Render/Renderer.h"
#include <string>
class Cube:public Renderer
{
    RENDERER_BASE_DECLARE(Cube);
public:
    Cube(std::string imagePath);
    void SetColor(glm::vec3 color);
private:
    class Image* image;
    std::string imagePath;
    glm::vec3 color;


};

