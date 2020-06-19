#pragma once
#include "ExampleCommomHeader.h"
#include <map>
class Ex_Text:public Renderer
{
    RENDERER_BASE_DECLARE(Ex_Text)

public:
        struct Character {
        GLuint     TextureID;  // ���������ID
        glm::ivec2 Size;       // ���δ�С
        glm::ivec2 Bearing;    // �ӻ�׼�ߵ�������/������ƫ��ֵ
        GLuint     Advance;    // ԭ�����һ������ԭ��ľ���
    };

    std::map<GLchar, Character> Characters;

    void  RenderText(Shader& s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};

