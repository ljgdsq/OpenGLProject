#include "Ex2_2.h"

Ex2_2::Ex2_2():Renderer(new Shader())
{

    shader->CreateShaderProgramFromResource("ex2_2.vert", "ex2_2.frag");
    InitData();
}

void Ex2_2::Draw()
{
    shader->Use();
    shader->SetVec3f("offset",0.5f,0,0 );
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Ex2_2::InitData()
{


    float datas[] = {
        0,0.5f,0,     1.0,0,0,
        0.5f,-0.5,0,  0,1.0,0,
        -0.5,-0.5,0,  0,0,1.0
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(datas), datas, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}
