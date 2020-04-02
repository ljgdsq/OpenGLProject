#pragma once
#include "Shader.h"


class Renderer
{

public:
    Renderer(Shader* shader);
    virtual void Draw();
    virtual ~Renderer();
protected:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    Shader* shader;

};

