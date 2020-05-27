#pragma once
#include "../Render/Renderer.h"
class Ex3_1:public Renderer
{
public:
    void Draw();
    void InitData();
    Ex3_1();
private:
    class Image* image;
};

