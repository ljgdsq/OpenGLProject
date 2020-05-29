#pragma once
#include "../Singleton.h"
#include "../interface/ITimer.h"
class GLFWTimer:public Singleton<GLFWTimer>,public ITimer
{

public:
    void Tick() override;
    float GetElapsedTime();

};

