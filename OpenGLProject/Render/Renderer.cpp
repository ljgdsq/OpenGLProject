#include "Renderer.h"
#include "../Utils/ScreenViewUtil.h"
#include "../Base/World.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
Renderer::Renderer()
{
    VAO = 0;
    VBO = 0;
    EBO = 0;
    this->shader = new Shader();

#if _DEBUG
    indicatorShader = nullptr;
    glGenVertexArrays(1, &indicatorVAO);
    glGenBuffers(1, &indicatorVBO);
#endif
}

Renderer::Renderer(Shader* shader)
{
    VAO = 0;
    VBO = 0;
    EBO = 0;
    this->shader = shader;

#if _DEBUG
    indicatorShader = nullptr;
    glGenVertexArrays(1, &indicatorVAO);
    glGenBuffers(1, &indicatorVBO);
#endif
}

void Renderer::Draw()
{
#if _DEBUG
    indicatorShader->Use();
    glm::mat4 model(1.0f);
    model = glm::scale(model, glm::vec3(9999, 9999, 9999));
    shader->SetModelMat4f(model);
    ScreenViewUtil::GetInstance()->SetUpShaderVPMatrix(World::GetInstance()->GetMainCamera(),indicatorShader);
    glBindVertexArray(indicatorVAO);
    indicatorShader->SetVec3f("objectColor", glm::vec3(1.0, 0, 0));
    glDrawArrays(GL_LINES, 0, 2);
    indicatorShader->SetVec3f("objectColor", glm::vec3(0, 1.0, 0));
    glDrawArrays(GL_LINES, 2, 2);
    indicatorShader->SetVec3f("objectColor", glm::vec3(0, 0, 1.0));
    glDrawArrays(GL_LINES, 4, 2);

#endif

}

void Renderer::InitData()
{
#if _DEBUG
    indicatorShader = new Shader();
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
    uniform vec3 objectColor;
    out vec4 FragColor;
	void main()
	{
      FragColor=vec4(objectColor,1.0f);
	}
)";

    indicatorShader->CreateShaderProgram(vertexShader, fragmentShader);
    glBindVertexArray(indicatorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, indicatorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(indicator_data), indicator_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#endif

}

Renderer::~Renderer()
{
    if (VAO)
    {
        glDeleteVertexArrays(1, &VAO);
    }
    if (VBO)
    {
        glDeleteBuffers(1, &VBO);
    }

    if (EBO)
    {
        glDeleteBuffers(1, &EBO);
    }
    if (this->shader)
    {
        delete shader;
    }

#if _DEBUG
    glDeleteVertexArrays(1, &indicatorVAO);
    glDeleteBuffers(1, &indicatorVBO);
#endif
}

