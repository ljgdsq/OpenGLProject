#pragma once
#include "Shader.h"
#include "../Render/Renderer.h"


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

};

#define RENDERER_BASE_CONSTRUCTOR_IMPL(TypeName) \
    TypeName::TypeName()                    \
    {                                        \
    InitData();                              \
    };                                       

#define RENDERER_BASE_SUPER_DRAW()  \
  Renderer::Draw();

#define RENDERER_BASE_SUPER_INITDATA()  \
  Renderer::InitData();

#define RENDERER_BASE_DECLARE(TypeName) \
public:\
void Draw();\
void InitData();\
TypeName();