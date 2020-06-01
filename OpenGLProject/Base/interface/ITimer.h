#pragma once
class ITimer
{
protected:
    float deltaTime;
    float lastTime;
    bool isPaused;
    float gameTime;
 
public:
    virtual void Tick() = 0;
    inline float GetDeltaTime() {
        return deltaTime;
    };
    virtual float GetElapsedTime() = 0;

    virtual float GetGameTime() = 0;

    void SetPause(bool pause) 
    {
        isPaused = pause;
    }

    bool IsPaused()
    {
        return isPaused;
    }

    void Init() {
        deltaTime = 0;
        lastTime = 0;
        isPaused = false;
        gameTime = 0;
    }
};