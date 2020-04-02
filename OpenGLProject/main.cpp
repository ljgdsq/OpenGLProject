#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utils/LogUtil.h"
#include "Examples/Triangle.h"
#include "Examples/ColorTriangle.h"
#include "Base/ProjetConfig.hpp"

using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc,char**argv)
{
    const char* title = "OpenGL";

    const int width = 800;
    const int height = 600;
    ProjectConfig::GetInstance()->SetExecutePath(argv[0]);
    LogUtil::GetInstance()->Verbose("Dir:"+ ProjectConfig::GetInstance()->GetExecutePath());

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //auto logUtil=LogUtil::GetInstance();
    //logUtil->Error("some error");
    //logUtil->Warn("some warn");
    //logUtil->Info("some info");
    //logUtil->SetLogLevel(LogUtil::WARN);
    //logUtil->Error("some error");
    //logUtil->Warn("some warn");
    //logUtil->Info("some info");
    //Renderer* triangle = new Triangle();
    Shader* shader = new Shader();

    auto fragSource=FileUtil::GetInstance()->LoadFromProjectResource("fragment_00.frag");
    auto vertSource=FileUtil::GetInstance()->LoadFromProjectResource("vertex_00.vert");

    shader->CreateShaderProgram(vertSource.c_str(), fragSource.c_str());
    Renderer* triangle = new ColorTriangle(shader);
    


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = (float)glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;

        triangle->Draw();
        shader->SetVec4f("ourColor", 0.3f,greenValue,0.6f,0.8f);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}