#include "WorldIndicator.h"
#include "../Utils/ScreenViewUtil.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
RENDERER_BASE_CONSTRUCTOR_IMPL(WorldIndicator)

void WorldIndicator::InitData()
{
#if _DEBUG
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    shader = new Shader();
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

    shader->CreateShaderProgram(vertexShader, fragmentShader);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(indicator_data), indicator_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#endif


}


void WorldIndicator::Draw()
{
#if _DEBUG
    shader->Use();
    glm::mat4 model(1.0f);
    model = glm::scale(model, glm::vec3(9999, 9999, 9999));
    shader->SetModelMat4f(model);
    ScreenViewUtil::GetInstance()->SetUpShaderVPMatrix(shader);
    glBindVertexArray(VAO);
    shader->SetVec3f("objectColor", glm::vec3(1.0, 0, 0));
    glDrawArrays(GL_LINES, 0, 2);
    shader->SetVec3f("objectColor", glm::vec3(0, 1.0, 0));
    glDrawArrays(GL_LINES, 2, 2);
    shader->SetVec3f("objectColor", glm::vec3(0, 0, 1.0));
    glDrawArrays(GL_LINES, 4, 2);

#endif
}

