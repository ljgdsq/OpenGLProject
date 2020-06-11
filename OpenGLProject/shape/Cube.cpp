#include "Cube.h"
#include "../CommonData.h"
#include "../Base/Image.h"
#include "../Utils/ScreenViewUtil.h"
#include "../Base/ResourceLoader.h"
RENDERER_BASE_CONSTRUCTOR_IMPL(Cube)

void Cube::InitData()
{
    shader->CreateShaderProgram(vertex_base_tex_mvp, fragment_base_tex);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vert_texel), cube_vert_texel, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    if (imagePath!="")
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


void Cube::Draw()
{
    if (image!=nullptr)
    {
        shader->Use();
        shader->SetInt("ourTexture", 0);
        ScreenViewUtil::GetInstance()->SetUpShaderMVPMatrix(shader);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, image->GetTexture());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

}

Cube::Cube(std::string imagePath)
{

    this->imagePath = imagePath;
    InitData();
}
