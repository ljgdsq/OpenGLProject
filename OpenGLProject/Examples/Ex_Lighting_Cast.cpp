#include "Ex_Lighting_Cast.h"
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
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
void Ex_Lighting_Cast::Draw()
{
    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    glBindVertexArray(VAO);

    glm::vec3 lightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
    float time = World::GetInstance()->GetTimer()->GetGameTime();
    float realTime = World::GetInstance()->GetTimer()->GetElapsedTime();
    //glm::vec3 lightPos(1.2f * sin(time), 1.0f, 2.0f * cos(time));

    shader->Use();
    shader->SetVec3f("viewPos", Camera::MainCamera->position);
    shader->SetVec3f("material.specular", 0.5f, 0.5f, 0.5f);
    shader->SetFloat("material.shininess", 32.0f);

    glm::vec3 lightColor(1, 1, 1);
    //lightColor.x = sin(realTime * 2.0f);
    //lightColor.y = sin(realTime * 0.7f);
    //lightColor.z = sin(realTime * 1.3f);
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

    //shader->SetVec3f("light.direction", lightDirection);
    shader->SetVec3f("light.position", lightPos);
    shader->SetVec3f("light.ambient", ambientColor);
    shader->SetVec3f("light.diffuse", diffuseColor);
    shader->SetVec3f("light.specular", 1.0f, 1.0f, 1.0f);

    shader->SetFloat("light.constant", 1.0f);
    shader->SetFloat("light.linear", 0.09f);
    shader->SetFloat("light.quadratic", 0.032f);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(Camera::MainCamera->zoom), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);
    shader->SetMat4f("projection", projection);
    shader->SetViewMat4f(Camera::MainCamera->GetViewMatrix());


    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader->SetModelMat4f(model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glm::mat4 model(1.0f);


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

    lineShader->Use();
    lineShader->SetMat4f("model", glm::mat4(1.0f));
    lineShader->SetMat4f("projection", projection);
    lineShader->SetViewMat4f(Camera::MainCamera->GetViewMatrix());
    glLineWidth(2.0f);
    glPointSize(10.0f);
    glBindVertexArray(lineVAO);
    glDrawArrays(GL_POINTS, 0, 2);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
    glLineWidth(1.0f);
    glPointSize(1.0f);
}

void Ex_Lighting_Cast::InitData()
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


        float constant;
        float linear;
        float quadratic;
    };

    uniform Light light;

	void main()
	{
        float distance=length(light.position-FragPos);
        float attenuation=1.0/(light.constant+light.linear*distance+light.quadratic*light.quadratic*distance);
        vec3 ambient=light.ambient*texture(material.diffuse,TexCoord).xyz;
        
        vec3 nor=normalize(Normal);
        vec3 lightDir=normalize(FragPos-light.position);
        float diff=max(dot(-lightDir,nor),0.0f);
        vec3 diffuse=diff*light.diffuse*texture(material.diffuse,TexCoord).xyz;

        vec3 viewDir=normalize(viewPos-FragPos);
        vec3 reflectDir=reflect(lightDir,nor);
        float spec=pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);    
        vec3 specular=spec*light.specular*texture(material.specular,TexCoord).xyz;

        vec3 col=(ambient+diffuse+specular)*attenuation;
		FragColor=vec4(col,1.0f);
	}
)";

    image = ResourceLoader::GetInstance()->LoadImage("images/container2.png");
    image->GenTexture();

    image2 = ResourceLoader::GetInstance()->LoadImage("images/container2_specular.png");
    image2->GenTexture();

    lightShader->CreateShaderProgram(vertexShader, fragmentShader);
    shader->CreateShaderProgram(cubeVertexShader, cubeFragmentShader);

    const char* lineVertShader = R"(

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
    const char* lineFragShader = R"(
    #version 330 core
	out vec4 FragColor;
	void main()
	{
        
		FragColor=vec4(1.0,0.5,0.3,1.0f);
	}

)";

    lineShader = new Shader();
    lineShader->CreateShaderProgram(lineVertShader, lineFragShader);

    float lineData[] = {
        0,0,0,
        lightPos.x,lightPos.y,lightPos.z
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);


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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &lineVAO);
    glBindVertexArray(lineVAO);
    glGenBuffers(1, &lineVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineData), lineData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

Ex_Lighting_Cast::Ex_Lighting_Cast()
{
    InitData();
}
