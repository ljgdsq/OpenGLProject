#include "Ex_Instancing.h"
#include <string>
#include <sstream>

using namespace std;
RENDERER_BASE_CONSTRUCTOR_IMPL(Ex_Instancing)

void Ex_Instancing::InitData()
{
    int maxCount = 100000;
    xMaxCount = sqrt(maxCount);
    yMaxCount = sqrt(maxCount);

    float quadVertices[] = {
        -0.05f / (xMaxCount / 10),  0.05f / (yMaxCount / 10),  1.0f, 0.0f, 0.0f,
         0.05f / (xMaxCount / 10), -0.05f / (yMaxCount / 10),  0.0f, 1.0f, 0.0f,
        -0.05f / (xMaxCount / 10), -0.05f / (yMaxCount / 10),  0.0f, 0.0f, 1.0f,
        -0.05f / (xMaxCount / 10),  0.05f / (yMaxCount / 10),  1.0f, 0.0f, 0.0f,
         0.05f / (xMaxCount / 10), -0.05f / (yMaxCount / 10),  0.0f, 1.0f, 0.0f,
         0.05f / (xMaxCount / 10),  0.05f / (yMaxCount / 10),  0.0f, 1.0f, 1.0f
    };



    const char* vShader = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec3 aColor;

        out vec3 fColor;
        uniform vec2 offsets[1024];
        void main()
        {
            vec2 offset = offsets[gl_InstanceID];
            gl_Position = vec4(aPos + offset, 0.0, 1.0);
            fColor = aColor;
        }
    )";
    const char* vShaderInstancing = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec3 aColor;
        layout (location = 2) in vec2 aOffsest;

        out vec3 fColor;
        void main()
        {
            gl_Position = vec4(aPos + aOffsest, 0.0, 1.0);
            fColor = aColor;
        }
    )";

    const char* fShader = R"(

        #version 330 core
        out vec4 FragColor;
        in vec3 fColor;
        void main()
        {
            FragColor = vec4(fColor, 1.0);
        }
    )";

    shader->CreateShaderProgram(vShaderInstancing, fShader);

    glm::vec2* translations = new glm::vec2[xMaxCount * yMaxCount];
    int index = 0;

    float offsetX = 1.0f/xMaxCount;
    float offsetY = 1.0f/yMaxCount;

    float xBase = 2.0f / xMaxCount;
    float yBase = 2.0f / yMaxCount;
    for (int i = 0; i < xMaxCount; i++)
    {
        for (int j = 0; j < yMaxCount; j++)
        {
            float x = -1+ i*xBase + offsetX;
            float y = -1 + j*yBase + offsetY;
            translations[j * xMaxCount + i] = glm::vec2(x, y);
        }
    }


    unsigned int offsetVBO;
    glGenBuffers(1, &offsetVBO);
    glBindBuffer(GL_ARRAY_BUFFER, offsetVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*maxCount, translations, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, offsetVBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);
    glBindVertexArray(0);

    shader->Use();
 /*   for (unsigned int i = 0; i < xMaxCount * yMaxCount; i++)
    {
        stringstream ss;
        string index;
        ss << i;
        index = ss.str();
        shader->SetVec2f(("offsets[" + index + "]").c_str(), translations[i]);
    }*/
}

void Ex_Instancing::Draw()
{
    shader->Use();
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, xMaxCount*yMaxCount);
}