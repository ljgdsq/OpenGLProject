#pragma once

class GLFWInputController
{
public:
    void ProcessKeyBoard(class GLFWwindow* window);
    void ProcessMouseMove(class GLFWwindow* window);
    void ProcessMouseScroll(class GLFWwindow* window);
};

