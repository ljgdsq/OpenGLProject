#include "Plane.h"
#include "../CommonData.h"
#include "../Base/Image.h"
#include "../Utils/ScreenViewUtil.h"
#include "../Base/ResourceLoader.h"
RENDERER_BASE_CONSTRUCTOR_IMPL(Plane)

void Plane::InitData()
{
    float planeVertices[] = {
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    shader->CreateShaderProgram(vertex_base_tex_mvp, fragment_base_tex);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    if (imagePath != "")
    {
        image = ResourceLoader::GetInstance()->LoadImage(imagePath.c_str());
    }
    else
    {
        image = Image::GetWhiteImage();
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image->GetTexture());

}


void Plane::Draw()
{
    if (image != nullptr)
    {
        shader->Use();
        shader->SetInt("ourTexture", 0);
        ScreenViewUtil::GetInstance()->SetUpShaderMVPMatrix(shader);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, image->GetTexture());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

}

Plane::Plane(std::string imagePath)
{

    this->imagePath = imagePath;
    InitData();
}
