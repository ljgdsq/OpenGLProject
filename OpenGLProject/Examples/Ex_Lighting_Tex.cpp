#include "Ex_Lighting_Tex.h"
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
void Ex_Lighting_Tex::Draw()
{

    float time = World::GetInstance()->GetTimer()->GetGameTime();
    float realTime = World::GetInstance()->GetTimer()->GetElapsedTime();
    glm::vec3 lightPos(1.2f * sin(time), 1.0f, 2.0f * cos(time));
    shader->Use();

    shader->SetVec3f("lightPos", lightPos);
    shader->SetVec3f("viewPos", Camera::MainCamera->position);

 
    shader->SetVec3f("material.specular", 0.5f, 0.5f, 0.5f);
    shader->SetFloat("material.shininess", 32.0f);

    glm::vec3 lightColor(1, 1, 1);
    //lightColor.x = sin(realTime * 2.0f);
    //lightColor.y = sin(realTime * 0.7f);
    //lightColor.z = sin(realTime * 1.3f);
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

    shader->SetVec3f("light.ambient", ambientColor);
    shader->SetVec3f("light.diffuse", diffuseColor);
    shader->SetVec3f("light.specular", 1.0f, 1.0f, 1.0f);


    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(Camera::MainCamera->zoom), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);
    shader->SetMat4f("projection", projection);
    shader->SetViewMat4f(Camera::MainCamera->GetViewMatrix());
    glm::mat4 model(1.0f);
    shader->SetModelMat4f(model);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    lightShader->Use();
    lightShader->SetVec3f("objectColor", 1.0f, 1.f, 1.f);
    lightShader->SetVec3f("lightingColor", 1.0f, 1.0f, 1.0f);
    lightShader->SetFloat("ambientStrength", 1.0f);
    lightShader->SetMat4f("projection", projection);
    lightShader->SetViewMat4f(Camera::MainCamera->GetViewMatrix());
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    lightShader->SetMat4f("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Ex_Lighting_Tex::InitData()
{

    lightShader = new Shader();
    winSize = ProjectConfig::GetInstance()->GetWindowSize();
    const char* vertexShader = R"(
    
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

    const char* fragmentShader = R"(
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
	layout(location=2) in vec2 aTexCoord;
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection; 
    out vec3 Normal;
    out vec3 FragPos;
    out vec2 TexCoord;
	void main()
	{
        TexCoord=aTexCoord;
        FragPos=vec3(model*vec4(aPos.x,aPos.y,aPos.z,1.0));
        Normal = mat3(transpose(inverse(model))) * aNormal;
		gl_Position=projection*view*model*vec4(aPos.x,aPos.y,aPos.z,1.0);
	}
)";


    const char* cubeFragmentShader = R"(
	#version 330 core
    in vec3 Normal;
    in vec3 FragPos;
    in vec2 TexCoord;
    uniform vec3 lightPos;
    uniform vec3 viewPos;
	out vec4 FragColor;

    struct Material
    {
        sampler2D diffuse;
        sampler2D specular;
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
        vec3 ambient=light.ambient*texture(material.diffuse,TexCoord).xyz;

        vec3 nor=normalize(Normal);
        vec3 lightDir=normalize(lightPos-FragPos);
        float diff=max(dot(lightDir,nor),0.0f);
        vec3 diffuse=diff*light.diffuse*texture(material.diffuse,TexCoord).xyz;

        vec3 viewDir=normalize(viewPos-FragPos);
        vec3 reflectDir=reflect(-lightDir,nor);
        float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);    
        vec3 specular=spec*light.specular*texture(material.specular,TexCoord).xyz;

        vec3 col=(ambient+diffuse+specular);
		FragColor=vec4(col,1.0f);
	}
)";

    image = ResourceLoader::GetInstance()->LoadImage("images/container2.png");
    image->GenTexture();

    image2 = ResourceLoader::GetInstance()->LoadImage("images/container2_specular.png");
    image2->GenTexture();

    lightShader->CreateShaderProgram(vertexShader, fragmentShader);
    shader->CreateShaderProgram(cubeVertexShader, cubeFragmentShader);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vert_normal_texel), cube_vert_normal_texel, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    shader->Use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image->GetTexture());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, image2->GetTexture());

    shader->SetInt("material.diffuse", 0);
    shader->SetInt("material.specular", 1);


}

Ex_Lighting_Tex::Ex_Lighting_Tex()
{
    InitData();
}
