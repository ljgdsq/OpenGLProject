#pragma once
#include "../Base/Singleton.h"
class ScreenViewUtil:public Singleton<ScreenViewUtil>
{
public:
    void SetUpShaderMVPMatrix(class Camera* camera, class Shader* shader);
    void SetUpShaderVPMatrix(class Camera* camera, class Shader* shader);
};

