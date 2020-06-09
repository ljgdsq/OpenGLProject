#include "ScreenViewUtil.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Base/Camera.hpp"
#include "../Render/Shader.h"
#include "../Base/ProjetConfig.hpp"
void ScreenViewUtil::SetUpShaderMVPMatrix(Shader* shader, Camera* camera)
{
    if (camera==nullptr)
    {
        camera = Camera::MainCamera;
    }
    glm::mat4 model(1.0f);
    shader->SetModelMat4f(model);

    glm::mat4 projection = glm::mat4(1.0f);
    auto winSize = ProjectConfig::GetInstance()->GetWindowSize();
    projection = glm::perspective(glm::radians(camera->zoom), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);
    shader->SetMat4f("projection", projection);
    shader->SetViewMat4f(camera->GetViewMatrix());

}

void ScreenViewUtil::SetUpShaderVPMatrix(Shader* shader,Camera* camera)
{
    if (camera == nullptr)
    {
        camera = Camera::MainCamera;
    }
    glm::mat4 projection = glm::mat4(1.0f);
    auto winSize = ProjectConfig::GetInstance()->GetWindowSize();
    projection = glm::perspective(glm::radians(camera->zoom), (float)winSize.x / (float)winSize.y, 0.1f, 100.0f);
    shader->SetMat4f("projection", projection);
    shader->SetViewMat4f(camera->GetViewMatrix());
}
