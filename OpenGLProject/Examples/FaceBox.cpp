#include "FaceBox.h"
#include "../Base/ResourceLoader.h"
#include "../Base/ProjetConfig.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
FaceBox::FaceBox()
{
    InitData();
}

void FaceBox::Draw()
{
    
}

void FaceBox::InitData()
{
    winSize = ProjectConfig::GetInstance()->GetWindowSize();
    shader->CreateShaderProgram(vertex_base_tex_mvp, fragment_base_tex2);
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f

    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    image1 = ResourceLoader::GetInstance()->LoadImage("images/container.jpg");
    image1->SetFilterMode(Image::FilterMode::LINEAR);
    image1->SetRepeatMode(Image::RepeatMode::REPEAT);
    image1->GenTexture();

    image2 = ResourceLoader::GetInstance()->LoadImage("images/face.png");
    image2->SetFilterMode(Image::FilterMode::LINEAR);
    image2->SetRepeatMode(Image::RepeatMode::REPEAT);
    image2->GenTexture();

    shader->Use();
    shader->SetInt("texture1", 0);
    shader->SetInt("texture2", 1);
    shader->SetFloat("mixPercent", 0.2f);



    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image1->GetTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, image2->GetTexture());

}

void FaceBox::Draw2(glm::mat4 view,float zoom)
{
    glBindVertexArray(VAO);

    glm::vec3  cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    shader->Use();
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(zoom), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);
    shader->SetMat4f("projection", projection);
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    float radius = 10.0f;

    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;

    shader->SetMat4f("view", view);
    float time = (float)glfwGetTime();
    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        //model = glm::rotate(model, glm::radians(angle+time*20), glm::vec3(1.0f, 0.3f, 0.5f));
        shader->SetMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
