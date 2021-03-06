#pragma once
#include "ExampleCommomHeader.h"
#include <map>
class Ex_Text:public Renderer
{
    RENDERER_BASE_DECLARE(Ex_Text)

public:
        struct Character {
        GLuint     TextureID;  // 字形纹理的ID
        glm::ivec2 Size;       // 字形大小
        glm::ivec2 Bearing;    // 从基准线到字形左部/顶部的偏移值
        GLuint     Advance;    // 原点距下一个字形原点的距离
    };

    std::map<GLchar, Character> Characters;

    void  RenderText(Shader& s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};

