#include "Ex3_2.h"
#include "../Base/ResourceLoader.h"

void Ex3_2::Draw()
{

   


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Ex3_2::InitData()
{

    shader->CreateShaderProgramFromResource("vertex_pcolor_tex.vert", "fragment_pcolor_tex.frag");
    float texScale = 0.2f;
    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
             0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f*texScale, 1.0f * texScale,   // 右上
             0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f * texScale, 0.0f * texScale,   // 右下
            -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f * texScale, 0.0f * texScale,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f * texScale, 1.0f * texScale    // 左上
    };

    unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    image1 = ResourceLoader::GetInstance()->LoadImage("images/wall.jpg");
    image1->GenTexture();

    image2 = ResourceLoader::GetInstance()->LoadImage("images/face.png");
    image2->SetRepeatMode(Image::RepeatMode::MIRROR_REPEAT);
    image2->SetFilterMode(Image::FilterMode::NEAREST);
    image2->SetFilterMode(Image::FilterMode::LINEAR);
    image2->GenTexture();

    shader->Use();
    glActiveTexture(GL_TEXTURE0);
    image1->Use();
    glActiveTexture(GL_TEXTURE1);
    image2->Use();

    shader->SetInt("ourTexture1", 0);
    shader->SetInt("ourTexture2", 1);
    shader->SetFloat("mixPercent", 0.2f);
}

Ex3_2::Ex3_2():Renderer()
{
    InitData();
}
