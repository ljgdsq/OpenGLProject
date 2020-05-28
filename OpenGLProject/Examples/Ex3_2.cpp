#include "Ex3_2.h"
#include "../Base/ResourceLoader.h"
#include "../Base/ProjetConfig.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
void Ex3_2::Draw()
{

    float time = (float)glfwGetTime();
    //glm::mat4 trans(1.0f);

    //trans = glm::translate(trans, glm::vec3(0.5f,-0.5,0));
    //trans = glm::rotate(trans, glm::radians(time)*60, glm::vec3(1,0,0));
    //shader->SetMat4f("tranform", trans);
    glm::mat4 model(1.0f);


    model = glm::rotate(model, glm::radians(time) * 30, glm::vec3(0, 1.0f, 0));
    shader->SetMat4f("model", model);

    glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);



    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.2f, 0, 0));
    model = glm::scale(model, glm::vec3(0.8f, 0.8f, 1.0f));
    model = glm::rotate(model, glm::radians(time)*30, glm::vec3(1.0f, 0, 0));
    shader->SetMat4f("model", model);

    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);


}

void Ex3_2::InitData()
{
    winSize = ProjectConfig::GetInstance()->GetWindowSize();
    shader->CreateShaderProgram(vertex_shader_pcolor_tex_mvp, fragment_shader_pcolor_tex);
   // shader->CreateShaderProgramFromResource("vertex_pcolor_tex_m.vert", "fragment_pcolor_tex.frag");
    //shader->CreateShaderProgramFromResource("vertex_pcolor_tex.vert", "fragment_pcolor_tex.frag");
    float texScale = 1.0f;
    //float vertices[] = {
    //    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
    //         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f*texScale, 1.0f * texScale,   // 右上
    //         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f * texScale, 0.0f * texScale,   // 右下
    //        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f * texScale, 0.0f * texScale,   // 左下
    //        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f * texScale, 1.0f * texScale    // 左上
    //};
    float vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
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

    glm::mat4 trans(1.0f);

    trans = glm::translate(trans, glm::vec3(0.5f,0,0));
    trans = glm::scale(trans, glm::vec3(0.5,0.5f,1));
    trans = glm::rotate(trans, glm::radians(90.0f),glm::vec3(0,0,1));
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(60.0f), winSize.x * 1.0f / winSize.y, 1.0f, 100.0f);

   // glm::mat4 projection = glm::mat4(1.0f);
    //projection = glm::perspective(glm::radians(45.0f), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);
   
    shader->SetMat4f("projection", projection);

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0, 0, -3.0f));
    shader->SetMat4f("view", view);
}

Ex3_2::Ex3_2():Renderer()
{
    InitData();
}
