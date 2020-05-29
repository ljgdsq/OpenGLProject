#pragma once
#include <glm/glm.hpp>
#include "../Render/Renderer.h"
#include "../Base/BaseStruct.hpp"
class FaceBox:public Renderer
{
public:
    FaceBox();
            
    void Draw() override;
    void InitData() override;
    void Draw2(glm::mat4 view,float zoom);
private:
    class Image* image1;
    class Image* image2;
    Size winSize;

};

