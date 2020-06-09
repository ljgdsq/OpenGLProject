#include "Renderer.h"
#include "../Base/World.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
Renderer::Renderer()
{
    VAO = 0;
    VBO = 0;
    EBO = 0;
    this->shader = new Shader();
}

Renderer::Renderer(Shader* shader)
{
    VAO = 0;
    VBO = 0;
    EBO = 0;
    this->shader = shader;

}

void Renderer::Draw()
{
}

void Renderer::InitData()
{

}

Renderer::~Renderer()
{
    if (VAO)
    {
        glDeleteVertexArrays(1, &VAO);
    }
    if (VBO)
    {
        glDeleteBuffers(1, &VBO);
    }

    if (EBO)
    {
        glDeleteBuffers(1, &EBO);
    }
    if (this->shader)
    {
        delete shader;
    }

}

