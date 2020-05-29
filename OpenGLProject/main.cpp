#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utils/LogUtil.h"
#include "Utils/StringUtil.hpp"
#include "Base/Camera.hpp"

#include "Examples/Triangle.h"
#include "Examples/ColorTriangle.h"
#include "Base/ProjetConfig.hpp"
#include "Examples/Ex1_1.h"
#include "Examples/Ex2_1.h"
#include "Examples/Ex2_2.h"
#include "Examples/Ex3_1.h"
#include "Examples/Ex3_2.h"
#include "Examples/FaceBox.h"

using namespace std;

float deltaTime = 0;
float lastTime = 0;
float lastX = 0;
float lastY = 0;
bool isFirst = true;
Camera* camera = new Camera(glm::vec3(0,0,3));

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::UP, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
}

void mouse_callback(GLFWwindow* window, double x, double y)
{
    if (isFirst)
    {
        isFirst = false;
        lastX = x;
        lastY = y;
    }

    float xOffset = x - lastX;
    float yOffset = y - lastY;

    lastX = x;
    lastY = y;
    LogUtil::GetInstance()->Info(toString(xOffset));
    camera->ProcessMouseMove(xOffset, yOffset);
}

void mouse_scroll(GLFWwindow* window, double x, double y)
{
    camera->ProcessMouseScroll(y);
    LogUtil::GetInstance()->Info(toString(y));
}

int main(int argc,char**argv)
{
    const char* title = "OpenGL";

    const int width = 800;
    const int height = 600;
    ProjectConfig::GetInstance()->SetExecutePath(argv[0]);
    Size size;
    size.x = 800;
    size.y = 600;
    ProjectConfig::GetInstance()->SetWindowSize(size);
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, mouse_scroll);
    //auto logUtil=LogUtil::GetInstance();
    //logUtil->Error("some error");
    //logUtil->Warn("some warn");
    //logUtil->Info("some info");
    //logUtil->SetLogLevel(LogUtil::WARN);
    //logUtil->Error("some error");
    //logUtil->Warn("some warn");
    //logUtil->Info("some info");
    //Renderer* triangle = new Triangle();

  
    //Renderer* triangle = new ColorTriangle();

   // Renderer* render = new Ex1_1();
    //Renderer* render = new Ex2_1();
    //Renderer* render = new Ex2_2();
   // Renderer* render = new Ex3_1();
    //Renderer* render = new Ex3_2();
    FaceBox* render = new FaceBox();
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        float time =(float) glfwGetTime();
        deltaTime = time - lastTime;
        lastTime = time;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       //glClear(GL_COLOR_BUFFER_BIT);
    
        //render->Draw();
        render->Draw2(camera->GetViewMatrix(),camera->zoom);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}