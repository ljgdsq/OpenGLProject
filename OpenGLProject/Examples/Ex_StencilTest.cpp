#include "Ex_StencilTest.h"
#include "../CommonData.h"
#include "../Base/ResourceLoader.h"
#include "../Utils/ScreenViewUtil.h"
#include "../Base/Camera.hpp"
RENDERER_BASE_CONSTRUCTOR_IMPL(Ex_StencilTest)

void Ex_StencilTest::InitData()
{
    const char* vShader = R"(

        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoords;

        out vec2 TexCoords;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            TexCoords = aTexCoords;    
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
   )";


    const char* fShader = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoords;
        uniform sampler2D texture1;
        void main()
        {    
            FragColor = texture(texture1, TexCoords);
            //FragColor = vec4(vec3(gl_FragCoord.z),1.0);
        }
    )";

    const char* borderVertex = R"(

        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoords;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
   )";

    const char* borderFragment = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {    
            FragColor = vec4(0.4,0.5,0.6,1.0);
        }
    )";

    borderShader = new Shader(borderVertex, borderFragment);
    shader->CreateShaderProgram(vShader, fShader);
    float planeVertices[] = {
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vert_texel), &cube_vert_texel, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);


    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);


    auto image1 = ResourceLoader::GetInstance()->LoadImage("marble.jpg");
    auto image2 = ResourceLoader::GetInstance()->LoadImage("wood.png");

    tex1 = image1->GetTexture();
    tex2 = image2->GetTexture();
    shader->Use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, tex2);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
}


void Ex_StencilTest::Draw()
{
    glEnable(GL_DEPTH_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    shader->Use();

    ScreenViewUtil::GetInstance()->SetUpShaderVPMatrix(shader);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    shader->SetModelMat4f(model);

    glStencilMask(0x00);
    shader->SetInt("texture1", 1);
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xff);
    shader->SetInt("texture1", 0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    shader->SetModelMat4f(model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

  
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    borderShader->Use();
    ScreenViewUtil::GetInstance()->SetUpShaderVPMatrix(borderShader);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    model = glm::scale(model, glm::vec3(1.1f,1.1f,1.1f));
    shader->SetModelMat4f(model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, -1.0f));
    model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
    borderShader->SetModelMat4f(model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST);
}


