#include "Ex_DepthTest.h"
#include "../Macro.h"
#include "../CommonData.h"
#include "../Base/ResourceLoader.h"
#include "../Utils/ScreenViewUtil.h"
#include "../Base/Camera.hpp"

RENDERER_BASE_CONSTRUCTOR_IMPL(Ex_DepthTest);
void Ex_DepthTest::Draw()
{

    RENDERER_BASE_SUPER_DRAW();
    shader->Use();

    ScreenViewUtil::GetInstance()->SetUpShaderVPMatrix(shader);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    shader->SetModelMat4f(model);

    shader->SetInt("texture1", 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    shader->SetModelMat4f(model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    shader->SetInt("texture1", 1);
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);


}

void Ex_DepthTest::InitData()
{
    RENDERER_BASE_SUPER_INITDATA();
  
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


    auto image1=ResourceLoader::GetInstance()->LoadImage("marble.jpg");
    auto image2=ResourceLoader::GetInstance()->LoadImage("wood.png");

    tex1 = image1->GetTexture();
    tex2 = image2->GetTexture();
    shader->Use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, tex2);

    glEnable(GL_DEPTH_TEST);
   // glDepthFunc(GL_ALWAYS);
}

