#include "Ex_Cyclender.h"
#include "../Base/ResourceLoader.h"
#include "../Base/ProjetConfig.hpp"
#include "../Base/Camera.hpp"
#include "../CommonData.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "../Base/World.h"
#include "../Base/interface/ITimer.h"
Ex_Cyclender::Ex_Cyclender()
{
    InitData();
}

void Ex_Cyclender::Draw()
{
    glBindVertexArray(VAO);
    shader->Use();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(Camera::MainCamera->zoom), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);
    shader->SetMat4f("projection", projection);
    shader->SetViewMat4f(Camera::MainCamera->GetViewMatrix());
    shader->SetVec3f("objectColor", glm::vec3(1, 0.5, 0));
    glm::mat4 model(1.0f);
    shader->SetModelMat4f(model);


    glBindVertexArray(sideVAO);
    shader->SetVec3f("objectColor", glm::vec3(0.2, 0.5, 0));
    glDrawElements(GL_TRIANGLES, 6*4, GL_UNSIGNED_INT, 0);
    glBindVertexArray(VAO);

    shader->SetVec3f("objectColor", glm::vec3(1, 0.5, 0));
    //  glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount+1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount + 2);
    model = glm::translate(model, glm::vec3(0.f, 0.0f, height));
    shader->SetModelMat4f(model);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount + 2);
}



void Ex_Cyclender::InitData()
{
    winSize = ProjectConfig::GetInstance()->GetWindowSize();

    const char* vertexShader = R"(
    
	#version 330 core
	layout(location=0) in vec3 aPos;
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
    out vec4 Pos;
    out vec4 Center;
	void main()
	{
        Pos=model*vec4(aPos.x,aPos.y,aPos.z,1.0);
        Center=model*vec4(0,0,0,1.0);
		gl_Position=projection*view*model*vec4(aPos.x,aPos.y,aPos.z,1.0);
	}
)";

    const char* fragmentShader = R"(
	#version 330 core
    uniform vec3 objectColor;
	in  vec4 Pos;
	in  vec4 Center;
    out vec4 FragColor;
	void main()
	{
        float x=Pos.x-Center.x;
        float y=Pos.y-Center.y;
        float len=sqrt(x*x+y*y);
    /*    if(len>0.5)
        {
            FragColor=vec4(1,1,1,0);
            //discard;
        }else
            {
             FragColor=vec4(objectColor,1.0f);
            }*/
           FragColor=vec4(objectColor,1.0f);
	}
)";

    vertexCount = 4;
    height = 0.9;
    Vec3* vertices = new Vec3[vertexCount + 2];

    float step = 360.0f / vertexCount;
    for (int i = 1; i <= vertexCount; i++)
    {
        auto xValue = sin(glm::radians(i * step));
        auto yValue = cos(glm::radians(i * step));
        vertices[i] = Vec3(xValue, yValue, 0);
    }
    vertices[0] = Vec3(0, 0, 0);
    vertices[vertexCount + 1] = vertices[1];

    shader->CreateShaderProgram(vertexShader, fragmentShader);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * (vertexCount + 2), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_BLEND);

    Vec3* vertices2 =new Vec3[vertexCount + 2];


    for (int i = 0; i < vertexCount + 2; i++)
    {
        vertices2[i] = vertices[i] - Vec3(0, 0, height);
    }

   Vec3* sides = new Vec3[vertexCount * 2];

    for (int i = 0; i < vertexCount - 1; i++)
    {
        sides[i*2] =vertices[i+1];
        sides[i*2 + 1] = vertices2[i+1];
    }

    int* indices = new int[vertexCount * 6];
    for (int i = 0; i < vertexCount; i++)
    {
        indices[i * 6 + 0] = 2 * i + 0;
        indices[i * 6 + 1] = 2 * i + 1;
        indices[i * 6 + 2] = 2 * i + 2;
        indices[i * 6 + 3] = 2 * i + 2;
        indices[i * 6 + 4] = 2 * i + 1;
        indices[i * 6 + 5] = 2 * i + 3;
    }


    glGenVertexArrays(1, &sideVAO);
    glBindVertexArray(sideVAO);

    glGenBuffers(1, &sideVBO);
    glGenBuffers(1, &sideEBO);


    glBindBuffer(GL_ARRAY_BUFFER, sideVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * (vertexCount * 2), sides, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sideEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)* vertexCount * 6, indices, GL_STATIC_DRAW);



    glDisable(GL_CULL_FACE);
}
