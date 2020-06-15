#include <iostream>
#include <string>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utils/LogUtil.h"
#include "Utils/GLEnvInfo.hpp"
#include "Utils/StringUtil.h"
#include "Base/World.h"
#include "Base/Camera.hpp"
#include "Base/CompGlfwImpl/GLFWTimer.h"
#include "Base/ProjetConfig.hpp"

#include "Examples/ExampleInit.h"
#include "Shape/WorldIndicator.h"


#define LOG_FPS
const float show_fps_per_second = 1;
float show_time = 0;
using namespace std;

World* world = World::GetInstance();
Camera* camera = new Camera(glm::vec3(0, 0, 3));

Camera* Camera::MainCamera = camera;

ITimer* timer = GLFWTimer::GetInstance();

float deltaTime = 0;
float lastTime = 0;
double lastX = 0;
double lastY = 0;
bool isFirst = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
bool isKeyDown = false;
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
        camera->ProcessKeyboard(Camera_Movement::DOWN, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::UP, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        isKeyDown = true;
        // LogUtil::GetInstance()->Info(toString(timer->IsPaused()));
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE && isKeyDown)
    {
        isKeyDown = false;
        timer->SetPause(!timer->IsPaused());
        // LogUtil::GetInstance()->Info(toString(timer->IsPaused()));
    }

    // LogUtil::GetInstance()->Info(toString(camera->position));
}

void mouse_callback(GLFWwindow* window, double x, double y)
{
    if (isFirst)
    {
        isFirst = false;
        lastX = x;
        lastY = y;
    }

    double xOffset = x - lastX;
    double yOffset = y - lastY;

    lastX = x;
    lastY = y;
    // LogUtil::GetInstance()->Info(toString(xOffset));
    camera->ProcessMouseMove((float)xOffset, (float)yOffset);
}

void mouse_scroll(GLFWwindow* window, double x, double y)
{
    camera->ProcessMouseScroll((float)y);
    //   LogUtil::GetInstance()->Info(toString(y));
}



int main(int argc, char** argv)
{
    world->InitWorld(timer, nullptr, ResourceLoader::GetInstance(), camera);
    timer->Init();

    const char* title = "OpenGL";
    const int width = 800;
    const int height = 600;
    ProjectConfig::GetInstance()->SetExecutePath(argv[0]);
    Size size;
    size.x = width;
    size.y = height;
    ProjectConfig::GetInstance()->SetWindowSize(size);
    LogUtil::GetInstance()->Verbose("Dir:" + ProjectConfig::GetInstance()->GetExecutePath());



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
    
    InitExamples();
    Renderer* render =ExampleFactory::GetLastExample();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    LogUtil::GetInstance()->Info(toString(GLEnvInfo::GetMaxVertexUniformComponent()));



    auto indicator = new WorldIndicator();
    while (!glfwWindowShouldClose(window))
    {
        timer->Tick();
        deltaTime = timer->GetDeltaTime();

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
        indicator->Draw();
        if (render)
        {
            render->Draw();
        }
    
      
        //glDisable(GL_DEPTH_TEST);

        glfwSwapBuffers(window);
        glfwPollEvents();


#ifdef LOG_FPS
        show_time += deltaTime;
        if (show_time>=show_fps_per_second)
        {
            show_time = 0;
            LogUtil::GetInstance()->Info(toString(1.0f / deltaTime));
        }
#endif // LOG_FPS


    }

    glfwTerminate();
    return 0;
}