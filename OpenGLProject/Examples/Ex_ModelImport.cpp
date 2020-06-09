#include "Ex_ModelImport.h"
#include "../Base/Model.h"
#include "../Utils/FileUtil.h"
#include "../Base/Camera.hpp"
#include "../Base/ProjetConfig.hpp"
Ex_ModelImport::Ex_ModelImport()
{
    InitData();
}

void Ex_ModelImport::InitData()
{
    winSize = ProjectConfig::GetInstance()->GetWindowSize();
    Renderer::InitData();
    auto fullPath = FileUtil::GetInstance()->GetResourceFullPath("models/nanosuit/nanosuit.obj");
    model = new GL3D::Model(fullPath.c_str());


    const char* vShader = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aNormal;
        layout (location = 2) in vec2 aTexCoords;
        out vec2 TexCoords;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main()
        {
            TexCoords = aTexCoords;    
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
    )";

    const char* fShader = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoords;
        uniform sampler2D texture_diffuse1;
        void main()
        {    
            FragColor = texture(texture_diffuse1, TexCoords);
        }
    )";

    shader->CreateShaderProgram(vShader, fShader);
}


void Ex_ModelImport::Draw()
{
    Renderer::Draw();
    glBindVertexArray(VAO);
    shader->Use();

    glm::mat4 modelMatrix(1.0f);
    shader->SetModelMat4f(modelMatrix);
    shader->SetViewMat4f(Camera::MainCamera->GetViewMatrix());
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(Camera::MainCamera->zoom), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);
    shader->SetProjectionMat4f(projection);

    model->Draw(*shader);

}