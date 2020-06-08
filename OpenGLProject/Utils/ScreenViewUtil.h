#pragma once
#include "../Base/Singleton.h"
class ScreenViewUtil:public Singleton<ScreenViewUtil>
{
public:
    void SetUpShaderViewMatrix(class Camera* camera, class Shader* shader);
};

