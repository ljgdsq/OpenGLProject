#include "Ex_PlanetInstancing.h"
#include "../Base/ResourceLoader.h"
#include "GLFW/glfw3.h"
RENDERER_BASE_CONSTRUCTOR_IMPL(Ex_PlanetInstancing)

void Ex_PlanetInstancing::InitData()
{

    planet = ResourceLoader::GetInstance()->LoadModel("models/planet/planet.obj");
    rock = ResourceLoader::GetInstance()->LoadModel("models/rock/rock.obj");
   
    const char* planetVShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 2) in vec2 aTexCoords;
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

    const char* planetFShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoords;
        uniform sampler2D texture_diffuse1;
        void main()
        {    
            FragColor = texture(texture_diffuse1, TexCoords);
        }
    )";

    shader->CreateShaderProgram(planetVShaderSource, planetFShaderSource);

    const char* rockVShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 2) in vec2 aTexCoords;
        layout (location = 3) in mat4 instanceMatrix;
        out vec2 TexCoords;
        uniform mat4 view;
        uniform mat4 projection;
        void main()
        {
            TexCoords = aTexCoords;    
            gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0);
        }
    )";

    const char* rockFShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoords;
        uniform sampler2D texture_diffuse1;
        void main()
        {    
            FragColor = texture(texture_diffuse1, TexCoords);
        }
    )";

    rockShader = new Shader(rockVShaderSource, rockFShaderSource);

    amount = MAX_ROCK;

    modelMatrices = new glm::mat4[amount];
    srand(glfwGetTime());

    float radius = 50.0f;
    float offset = 2.5f;
    for (int i=0;i<amount;i++)
    {
        glm::mat4 model(1.0f);

        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // 让行星带的高度比x和z的宽度要小
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. 缩放：在 0.05 和 0.25f 之间缩放
        float scale = (rand() % 20) / 100.0f + 0.05;
        model = glm::scale(model, glm::vec3(scale));

        // 3. 旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
        float rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
        modelMatrices[i] = model;
    }

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    auto vec4Size = sizeof(glm::vec4);

    for (int i=0;i<rock->meshes.size();i++)
    {
        unsigned int VAO = rock->meshes[i].GetVAO();
        glBindVertexArray(VAO);
        
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);

        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));

        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size*2));

        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size * 3));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
        
        glBindVertexArray(0);

    }

}


void Ex_PlanetInstancing::Draw()
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
    shader->Use();
    ScreenViewUtil::GetInstance()->SetUpShaderVPMatrix(shader);
    shader->SetModelMat4f(model);
    planet->Draw(*shader);

    rockShader->Use();
    ScreenViewUtil::GetInstance()->SetUpShaderVPMatrix(rockShader);

    rock->InstancingDraw(*rockShader, amount);
    return;
       rockShader->SetInt("texture_diffuse1", 0);
       glActiveTexture(GL_TEXTURE0);
       glBindTexture(GL_TEXTURE_2D, rock->textures_loaded[0].id);

       for (unsigned int i=0;i<rock->meshes.size();i++)
       {
           glBindVertexArray(rock->meshes[i].GetVAO());
           glDrawElementsInstanced(GL_TRIANGLES, rock->meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
           glBindVertexArray(0);
       }
}
