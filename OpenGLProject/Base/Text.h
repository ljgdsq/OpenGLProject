#pragma once
#include <string>
#include <vector>
#include "../Render/Renderer.h"
class Text:public Renderer
{
private:
    void  RenderText(GLfloat x, GLfloat y, GLfloat scale);
public:
    void Draw(); 
    void InitData(); 
    Text(std::string text, GLfloat x, GLfloat y, GLfloat scale);
    glm::vec3 color;
    std::string text;
    GLfloat x; GLfloat y; GLfloat scale;
    //TODO Ĭ��ʹ��һ������

private:
    int winWidth;
    int winHeight;
    int maxCachedFontCount = 8;
/*
    class _TextFontInit
    {
    public:
        struct Character {
            GLuint     TextureID;  // ���������ID
            glm::ivec2 Size;       // ���δ�С
            glm::ivec2 Bearing;    // �ӻ�׼�ߵ�������/������ƫ��ֵ
            GLuint     Advance;    // ԭ�����һ������ԭ��ľ���
        };
        std::vector<std::string, Character> FontCharacter;
        std::map<GLchar, Character> Characters;
        _TextFontInit(Shader*shader,unsigned int VAO,unsigned int VBO);
        void InitFont(Shader* shader, unsigned int VAO, unsigned int VBO);
        void Draw(Shader* shader, unsigned int VAO, unsigned int VBO);
    };
    */
};

