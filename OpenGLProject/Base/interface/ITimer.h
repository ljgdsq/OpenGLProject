#pragma once
class ITimer
{
protected:
    float deltaTime;
    float lastTime;
public:
    virtual void Tick() = 0;
    inline float GetDeltaTime() {
        return deltaTime;
    };
    virtual float GetElapsedTime() = 0;

};