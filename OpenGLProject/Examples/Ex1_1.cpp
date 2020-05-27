#include "Ex1_1.h"
#include "../CommonHeader.h"
Ex1_1::Ex1_1():Renderer(new Shader())
{
    InitData();
}

void Ex1_1::InitData()
{
    //shader->CreateShaderProgramFromFile("ex1_1.vert", "ex1_1.frag");
    shader->CreateShaderProgram(vertex_shader_0, fragment_shader_0);
      
    float vert[12] = {
        0.5f,0.5f,0,
        0.5f,-0.5f,0,
        -0.5f,-0.5f,0,
        -0.5f,0.5f,0
    };

   unsigned int indices[] = {
        0,1,2,
        0,2,3
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Ex1_1::Draw()
{
    glUseProgram(shader->GetShaderProgram());

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
