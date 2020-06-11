#include "ScreenRenderer.h"
RENDERER_BASE_CONSTRUCTOR_IMPL(ScreenRenderer)

void ScreenRenderer::InitData()
{
    float quadVertices[] = {

        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    texture = -1;
}


void ScreenRenderer::Draw()
{
    if (texture!=-1)
    {
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->Use();
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void ScreenRenderer::SetTexture(int texture)
{
    this->texture = texture;
}

void ScreenRenderer::InitShader()
{
    const char* screenVShader = R"(
       #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTexCoords;
        out vec2 TexCoords;
        void main()
        {
            TexCoords = aTexCoords;
            gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
        }  
)";

    const char* screenFShader = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoords;
        uniform sampler2D screenTexture;
        void main()
        {
            vec3 col = texture(screenTexture, TexCoords).rgb;
            FragColor = vec4(col, 1.0);
        } 
)";

    const char* screenFShaderBlur = R"(
     #version 330 core
        out vec4 FragColor;
        in vec2 TexCoords;
        uniform sampler2D screenTexture;

        const float offset = 1.0 / 300.0;  
        void main()
        {   
            vec2 offsets[9] = vec2[](
                vec2(-offset,  offset), // 左上
                vec2( 0.0f,    offset), // 正上
                vec2( offset,  offset), // 右上
                vec2(-offset,  0.0f),   // 左
                vec2( 0.0f,    0.0f),   // 中
                vec2( offset,  0.0f),   // 右
                vec2(-offset, -offset), // 左下
                vec2( 0.0f,   -offset), // 正下
                vec2( offset, -offset)  // 右下
                );

             float kernel[9] = float[](
                1.0 / 16, 2.0 / 16, 1.0 / 16,
                2.0 / 16, 4.0 / 16, 2.0 / 16,
                1.0 / 16, 2.0 / 16, 1.0 / 16  
            );

            vec3 sampleTex[9];
            for(int i = 0; i < 9; i++)
            {
                sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
            }
            vec3 col = vec3(0.0);
            for(int i = 0; i < 9; i++)
                col += sampleTex[i] * kernel[i];
            
            FragColor = vec4(col, 1.0);
        }

)";
    const char* screenGrayShader = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoords;
        uniform sampler2D screenTexture;
        void main()
        {
            FragColor.rgb = texture(screenTexture, TexCoords).rgb;
            float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
            FragColor = vec4(average, average, average, 1.0);
        } 
)";

    shader = new Shader(screenVShader, screenGrayShader);
    shader->Use();
    shader->SetInt("screenTexture", 0);
}
