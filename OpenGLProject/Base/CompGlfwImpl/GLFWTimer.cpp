#include "GLFWTimer.h"
#include "GLFW/glfw3.h"

void GLFWTimer::Tick()
{
    float curTime=GetElapsedTime();
    deltaTime = curTime - lastTime;
    lastTime = curTime;
    if (!isPaused)
    {
        gameTime += deltaTime;
    }
}


float GLFWTimer::GetElapsedTime()
{
    return (float)glfwGetTime();
}

float GLFWTimer::GetGameTime()
{
    return gameTime;
}
