#include "Ex_PlanetInstancing.h"
#include "../Base/ResourceLoader.h"

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
}


void Ex_PlanetInstancing::Draw()
{
    shader->Use();
    ScreenViewUtil::GetInstance()->SetUpShaderMVPMatrix(shader);
   // planet->Draw(*shader);

    rockShader->Use();
    ScreenViewUtil::GetInstance()->SetUpShaderMVPMatrix(rockShader);
    rock->Draw(*rockShader);
}
