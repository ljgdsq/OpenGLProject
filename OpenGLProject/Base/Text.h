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
    //TODO 默认使用一种字体

private:
    int winWidth;
    int winHeight;
    int maxCachedFontCount = 8;
/*
    class _TextFontInit
    {
    public:
        struct Character {
            GLuint     TextureID;  // 字形纹理的ID
            glm::ivec2 Size;       // 字形大小
            glm::ivec2 Bearing;    // 从基准线到字形左部/顶部的偏移值
            GLuint     Advance;    // 原点距下一个字形原点的距离
        };
        std::vector<std::string, Character> FontCharacter;
        std::map<GLchar, Character> Characters;
        _TextFontInit(Shader*shader,unsigned int VAO,unsigned int VBO);
        void InitFont(Shader* shader, unsigned int VAO, unsigned int VBO);
        void Draw(Shader* shader, unsigned int VAO, unsigned int VBO);
    };
    */
};

