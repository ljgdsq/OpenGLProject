#pragma once
#include "../Render/Renderer.h"
class Ex3_2:public Renderer
{
public:
    void Draw();
    void InitData();
    Ex3_2();
private:
    class Image* image1;
    class Image* image2;
};

