#include "ColorTriangle.h"
#include <GLFW/glfw3.h>

void ColorTriangle::Draw()
{
    glUseProgram(shader->GetShaderProgram());
    glBindVertexArray(VAO);

    float timeValue = (float)glfwGetTime();
    float greenValue =(float) sin(timeValue) / 2.0f + 0.5f;
    shader->SetVec4f("ourColor", 0.3f, greenValue, 0.6f, 0.8f);
    glDrawArrays(GL_TRIANGLES, 0,3);
}

ColorTriangle::ColorTriangle(Shader*shader):Renderer(shader)
{
    InitData();
}

void ColorTriangle::InitData()
{
    float vertices[] = {
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

ColorTriangle::ColorTriangle():Renderer(new Shader())
{
    InitData();
    auto fragSource = FileUtil::GetInstance()->LoadStringFromProjectResource("fragment_00.frag");
    auto vertSource = FileUtil::GetInstance()->LoadStringFromProjectResource("vertex_00.vert");
    shader->CreateShaderProgram(vertSource.c_str(), fragSource.c_str());
}
