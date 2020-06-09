#pragma once
#include "../Base/Singleton.h"
class ScreenViewUtil:public Singleton<ScreenViewUtil>
{
public:
    void SetUpShaderMVPMatrix(class Shader* shader,class Camera* camera=nullptr);
    void SetUpShaderVPMatrix(class Shader* shader,class Camera* camera=nullptr);
};

