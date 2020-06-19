#include "Text.h"
#include <ft2build.h>
#include FT_FREETYPE_H  
#include "../Utils/LogUtil.h"
#include "../Utils/FileUtil.h"
#include "../Base/ProjetConfig.hpp"
#include <glm/ext/matrix_clip_space.hpp>
/*
void Text::RenderText(GLfloat x, GLfloat y, GLfloat scale)
{
   
}

void Text::Draw()
{

}

void Text::InitData()
{
    auto size=ProjectConfig::GetInstance()->GetWindowSize();
    winHeight = size.y;
    winWidth = size.x;


}

Text::Text(std::string text, GLfloat x, GLfloat y, GLfloat scale)
{
    static _TextFontInit fontIniter(shader, VAO, VBO);
    this->text = text;
    this->x = x;
    this->y = y;
    this->scale = scale;
    InitData();
}

Text::_TextFontInit::_TextFontInit(Shader* shader, unsigned int VAO, unsigned int VBO)
{
    InitFont(shader,VAO,VBO);
}

void Text::_TextFontInit::InitFont(Shader* shader, unsigned int VAO, unsigned int VBO)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        LogUtil::GetInstance()->Error("ERROR::FREETYPE: Could not init FreeType Library");
    }

    auto fontPath = FileUtil::GetInstance()->GetResourceFontFullPath("arial.ttf");
    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
    {
        LogUtil::GetInstance()->Error("ERROR::FREETYPE: Failed to load font");

    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制

    for (GLubyte c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            LOGE("ERROR::FREETYTPE: Failed to load Glyph");
            continue;
        }
        // 生成纹理
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x
        };
        Characters.insert({ c, character });
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    const char* vShaderSource = R"(
         #version 330 core
        layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
        out vec2 TexCoords;

        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
            TexCoords = vertex.zw;
        }

)";
    const char* fShaderSource = R"(
          #version 330 core
        in vec2 TexCoords;
        out vec4 color;

        uniform sampler2D text;
        uniform vec3 textColor;

        void main()
        {    
            vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
            color = vec4(textColor, 1.0) * sampled;
        }

)";

    shader->CreateShaderProgram(vShaderSource, fShaderSource);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Text::_TextFontInit::Draw(Shader* shader, unsigned int VAO, unsigned int VBO)
{
    shader->Use();
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

}
*/