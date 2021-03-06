#include "Ex_Lighting.h"
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
void Ex_Lighting::Draw()
{
    float time = World::GetInstance()->GetTimer()->GetGameTime();
    float realTime = World::GetInstance()->GetTimer()->GetElapsedTime();
    glm::vec3 lightPos(1.2f*sin(time), 1.0f , 2.0f * cos(time));
    shader->Use();

    //shader->SetFloat("ambientStrength", 1.0f);
    //shader->SetFloat("specularStrength", 1.0f);
    //shader->SetVec3f("lightingColor", 1.0f, 1.0f, 1.0f);
    //shader->SetVec3f("objectColor", 1.0f, 0.5f, 0.31f);


    shader->SetVec3f("lightPos", lightPos);
    shader->SetVec3f("viewPos", Camera::MainCamera->position);
    //shader->SetInt("specularPower",32);

   //shader->SetVec3f("material.ambient", 0.0f, 0.1f, 0.06f); //cyan plastic
   //shader->SetVec3f("material.diffuse", 0.0f, 0.50980392f, 0.50980392f);
   //shader->SetVec3f("material.specular", 0.50196078f, 0.50196078f, 0.50196078f);
   //shader->SetFloat("material.shininess", 32.0f);
 

     /*  shader->SetVec3f("material.ambient", 0.02f, 0.02f, 0.02f);
       shader->SetVec3f("material.diffuse", 0.01f, 0.01f, 0.01f);
       shader->SetVec3f("material.specular", 0.4f, 0.4f, 0.4f);
       shader->SetFloat("material.shininess", 10.f);*/

    shader->SetVec3f("material.ambient", 1.0f, 0.5f, 0.31f);
    shader->SetVec3f("material.diffuse", 1.0f, 0.5f, 0.31f);
    shader->SetVec3f("material.specular", 0.5f, 0.5f, 0.5f);
    shader->SetFloat("material.shininess", 32.0f);

    glm::vec3 lightColor(1,1,1);
    //lightColor.x = sin(realTime * 2.0f);
    //lightColor.y = sin(realTime * 0.7f);
    //lightColor.z = sin(realTime * 1.3f);
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 

    shader->SetVec3f("light.ambient", ambientColor);
    shader->SetVec3f("light.diffuse", diffuseColor);

    /* shader->SetVec3f("light.ambient", 0.2f, 0.2f, 0.2f);
     shader->SetVec3f("light.diffuse", 0.5f, 0.5f, 0.5f); */
    shader->SetVec3f("light.specular", 1.0f, 1.0f, 1.0f);


    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(Camera::MainCamera->zoom), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);
    shader->SetMat4f("projection", projection);
    shader->SetViewMat4f(Camera::MainCamera->GetViewMatrix());
    glm::mat4 model(1.0f);
    //model = glm::translate(model, glm::vec3(-0.5f,-0.5f,-1.5));
    shader->SetModelMat4f(model);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    lightShader->Use();
    lightShader->SetVec3f("objectColor", 1.0f, 1.f, 1.f);
    lightShader->SetVec3f("lightingColor", 1.0f,1.0f,1.0f);
    lightShader->SetFloat("ambientStrength", 1.0f);
    lightShader->SetMat4f("projection", projection);
    lightShader->SetViewMat4f(Camera::MainCamera->GetViewMatrix());
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    lightShader->SetMat4f("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Ex_Lighting::InitData()
{

    lightShader = new Shader();
    winSize = ProjectConfig::GetInstance()->GetWindowSize();
    const char* vertexShader=R"(
    
	#version 330 core
	layout(location=0) in vec3 aPos;
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
	void main()
	{
		gl_Position=projection*view*model*vec4(aPos.x,aPos.y,aPos.z,1.0);
	}
)";

    const char*fragmentShader=R"(
	#version 330 core
    uniform vec3 lightingColor;
    uniform vec3 objectColor;
    uniform float ambientStrength;
	out vec4 FragColor;
	void main()
	{
        
		FragColor=vec4(lightingColor*ambientStrength*objectColor,1.0f);
	}
)";


    const char* cubeVertexShader = R"(
    
	#version 330 core
	layout(location=0) in vec3 aPos;
	layout(location=1) in vec3 aNormal;
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
    out vec3 Normal;
    out vec3 FragPos;
	void main()
	{
        FragPos=vec3(model*vec4(aPos.x,aPos.y,aPos.z,1.0));
        Normal = mat3(transpose(inverse(model))) * aNormal;
		gl_Position=projection*view*model*vec4(aPos.x,aPos.y,aPos.z,1.0);
	}
)";


    const char* cubeFragmentShader = R"(
	#version 330 core
    in vec3 Normal;
    in vec3 FragPos;
    uniform vec3 lightPos;
    uniform vec3 viewPos;
	out vec4 FragColor;

    struct Material
    {
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        float shininess;
    };

    uniform  Material material;

    struct Light {
        vec3 position;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };

    uniform Light light;

	void main()
	{
        vec3 ambient=light.ambient*material.ambient;

        vec3 nor=normalize(Normal);
        vec3 lightDir=normalize(lightPos-FragPos);
        float diff=max(dot(lightDir,nor),0.0f);
        vec3 diffuse=diff*light.diffuse*material.diffuse;

        vec3 viewDir=normalize(viewPos-FragPos);
        vec3 reflectDir=reflect(-lightDir,nor);
        float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);    
        vec3 specular=spec*light.specular*material.specular;

        vec3 col=(ambient+diffuse+specular);
		FragColor=vec4(col,1.0f);
	}
)";
    const char* cubeVertexShader2 = R"(
    
	#version 330 core
	layout(location=0) in vec3 aPos;
	layout(location=1) in vec3 aNormal;
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

    uniform float ambientStrength;
    uniform vec3 lightPos;
    uniform vec3 lightingColor;
    uniform vec3 objectColor;
    uniform vec3 viewPos;
    uniform float specularStrength;
    uniform int specularPower;

    out vec3 Color;
	void main()
	{
        vec3 FragPos=vec3(model*vec4(aPos.x,aPos.y,aPos.z,1.0));
        vec3 Normal = mat3(transpose(inverse(model))) * aNormal;

        vec3 ambient=ambientStrength*lightingColor;
        vec3 nor=normalize(Normal);
        vec3 lightDir=normalize(lightPos-FragPos);
        float diff=max(dot(lightDir,nor),0.0f);
        vec3 diffuse=diff*lightingColor;

        vec3 viewDir=normalize(viewPos-FragPos);
        vec3 reflectDir=reflect(-lightDir,nor);
        float spec=pow(max(dot(viewDir,reflectDir),0.0f),specularPower);    
        vec3 specular=spec*specularStrength*lightingColor;

        Color=(ambient+diffuse+specular)*objectColor;

		gl_Position=projection*view*model*vec4(aPos.x,aPos.y,aPos.z,1.0);
	}
)";

    const char* cubeFragmentShader2 = R"(
	#version 330 core
    in vec3 Color;
	out vec4 FragColor;
    
	void main()
	{
		FragColor=vec4(Color,1.0f);
	}
)";

    lightShader->CreateShaderProgram(vertexShader, fragmentShader);
    shader->CreateShaderProgram(cubeVertexShader, cubeFragmentShader);
   // shader->CreateShaderProgram(cubeVertexShader2, cubeFragmentShader2);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vert_normal), cube_vert_normal, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

}

Ex_Lighting::Ex_Lighting()
{
    InitData();
}
