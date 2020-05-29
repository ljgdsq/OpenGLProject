#include "GLFWTimer.h"
#include "GLFW/glfw3.h"

void GLFWTimer::Tick()
{
    float curTime=GetElapsedTime();
    deltaTime = curTime - lastTime;
    lastTime = curTime;
}


float GLFWTimer::GetElapsedTime()
{
    return (float)glfwGetTime();
}
