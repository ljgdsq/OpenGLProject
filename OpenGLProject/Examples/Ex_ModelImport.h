#include "../Render/Renderer.h"
#include "../Base/BaseStruct.hpp"
#include "../Base/Model.h"
class Ex_ModelImport :public Renderer
{
 
public:
    void Draw();
    void InitData();
    Ex_ModelImport();
    Size winSize;
    class  GL3D::Model* model;
};
