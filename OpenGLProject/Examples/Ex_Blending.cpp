#include "Ex_Blending.h"
#include "../CommonData.h"
#include "../Base/ResourceLoader.h"
#include "../Utils/ScreenViewUtil.h"
#include "../Base/Camera.hpp"
#include "../Shape/Cube.h"
#include "../Shape/Plane.h"
#include <vector>
RENDERER_BASE_CONSTRUCTOR_IMPL(Ex_Blending)

void Ex_Blending::InitData()
{

    vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
    vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
    vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
    vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
    vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

 
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
        out vec2 TexCoord;
        void main()
        {
            TexCoord=aTexCoords;
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
   )";

    const char* grassFragment= R"(
	    #version 330 core
	    in vec2 TexCoord;
	    out vec4 FragColor;

        uniform sampler2D ourTexture;
	    void main()
	    {
               vec4 color=texture(ourTexture, TexCoord);
               /* if(color.a<0.1)
                    discard;*/
		      FragColor = color;
		  // FragColor=vec4(0.7,0.5,1,1);
	    }
    )";


    shader->CreateShaderProgram(vShader, fShader);
    grassShader = new Shader(borderVertex, grassFragment);
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


    glGenVertexArrays(1, &grassVAO);
    glGenBuffers(1, &grassVBO);
    glGenBuffers(1, &grassEBO);
    glBindVertexArray(grassVAO);
    glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vert_texl), &plane_vert_texl, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grassEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(plane_indices), &plane_indices, GL_STATIC_DRAW);

    glBindVertexArray(0);


    auto image1 = ResourceLoader::GetInstance()->LoadImage("marble.jpg");
    auto image2 = ResourceLoader::GetInstance()->LoadImage("wood.png");
    auto image3 = ResourceLoader::GetInstance()->LoadImage("grass.png");

    image3->SetRepeatMode(Image::CLAMP_TO_EDGE);
    tex1 = image1->GetTexture();
    tex2 = image2->GetTexture();
    tex3 = image3->GetTexture();


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, tex3);
    

    cube = new Cube("wood.png");
    plane = new Plane("wall.jpg");
    glDisable(GL_CULL_FACE);
}
void Ex_Blending::Draw()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    plane->Draw();
    cube->Draw();
    shader->Use();
    ScreenViewUtil::GetInstance()->SetUpShaderVPMatrix(shader);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    shader->SetModelMat4f(model);
    glBindVertexArray(planeVAO);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, tex2);
    shader->SetInt("texture1", 1);

  //  glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    shader->SetInt("texture1", 0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    shader->SetModelMat4f(model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

  
    //glBlendFunc(GL_ONE, GL_ZERO);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, tex3);
    glBindVertexArray(grassVAO);
    grassShader->Use();
    ScreenViewUtil::GetInstance()->SetUpShaderVPMatrix(grassShader);
    grassShader->SetInt("ourTexture", 2);

    vegetationMap.clear();
    for (size_t i = 0; i < vegetation.size(); i++)
    {
        auto distance = glm::length(Camera::MainCamera->position - vegetation[i]);
        vegetationMap[distance] = vegetation[i];
    }
    

    for (auto it=vegetationMap.rbegin();it!=vegetationMap.rend();it++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, it->second);
        grassShader->SetModelMat4f(model);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    
}