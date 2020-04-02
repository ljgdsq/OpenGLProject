#include "Triangle.h"

void Triangle::InitDrawData()
{
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  
        0.5f, -0.5f, 0.0f,  
       -0.5f, -0.5f, 0.0f,  
       -0.5f,  0.5f, 0.0f   
    };
    unsigned int indices[] = { 
        0, 1, 3,  
        1, 2, 3  
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

Triangle::Triangle():Renderer(new Shader(vertex_shader_0,fragment_shader_0))
{
    InitDrawData();
}

void Triangle::Draw()
{
    glUseProgram(shader->GetShaderProgram());
    glBindVertexArray(VAO); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
