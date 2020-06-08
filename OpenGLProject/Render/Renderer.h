#pragma once
#include "Shader.h"


class Renderer
{

public:
    Renderer();
    Renderer(Shader* shader);
    virtual void Draw();
    virtual void InitData();
    virtual ~Renderer();
protected:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    Shader* shader;


#if _DEBUG
    unsigned int indicatorVAO;
    unsigned int indicatorVBO;
    float indicator_data[18] = {
        //x
        -0.5f,0,0,  0.5f,0,0,
        //y
        0,-0.5f,0,  0,0.5f,0,
        //z
        0,0,-0.5,   0,0,0.5f,
    };
    Shader* indicatorShader;
#endif
};

