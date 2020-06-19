#include "Ex_ShadowMapping.h"
#include "../Base/ResourceLoader.h"
#include "../Base/ProjetConfig.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "../Render/RenderTexture.h"
#include "../Render/ScreenRenderer.h"
RENDERER_BASE_CONSTRUCTOR_IMPL(Ex_ShadowMapping)

void Ex_ShadowMapping::InitData()
{

    auto winSize = ProjectConfig::GetInstance()->GetWindowSize();
    width = winSize.x;
    height = winSize.y;
    const char* debugDrawVShader=R"(
               #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoords;

            out vec2 TexCoords;

            void main()
            {
                TexCoords = aTexCoords;
                gl_Position = vec4(aPos, 1.0);
            }
)";
    const char* debugDrawFShader=R"(
            #version 330 core
        out vec4 FragColor;

        in vec2 TexCoords;

        uniform sampler2D depthMap;
        uniform float near_plane;
        uniform float far_plane;

        // required when using a perspective projection matrix
        float LinearizeDepth(float depth)
        {
            float z = depth * 2.0 - 1.0; // Back to NDC 
            return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	
        }

        void main()
        {             
            float depthValue = texture(depthMap, TexCoords).r;
            // FragColor = vec4(vec3(LinearizeDepth(depthValue) / far_plane), 1.0); // perspective
            FragColor = vec4(vec3(depthValue), 1.0); // orthographic
        }
)";

    const char* lightFShader2 = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {            
               FragColor=vec4(1,0.5,0.5,1.0); 
            // gl_FragDepth = gl_FragCoord.z;
        }
)";


    const char* sceneVShader = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aNormal;
        layout (location = 2) in vec2 aTexCoords;
        out vec2 TexCoords;
        out VS_OUT {
            vec3 FragPos;
            vec3 Normal;
            vec2 TexCoords;
            vec4 FragPosLightSpace;
        } vs_out;

        uniform mat4 projection;
        uniform mat4 view;
        uniform mat4 model;
        uniform mat4 lightSpaceMatrix;

        void main()
        {
            vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
            vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
            vs_out.TexCoords = aTexCoords;
            vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
)";

    const char* sceneFShader = R"(
        #version 330 core
        out vec4 FragColor;

        in VS_OUT {
            vec3 FragPos;
            vec3 Normal;
            vec2 TexCoords;
            vec4 FragPosLightSpace;
        } fs_in;

        uniform sampler2D diffuseTexture;
        uniform sampler2D shadowMap;

        uniform vec3 lightPos;
        uniform vec3 viewPos;
        float bias;
        float ShadowCalculation(vec4 fragPosLightSpace)
        {
            // perform perspective divide
            vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
            // transform to [0,1] range
            projCoords = projCoords * 0.5 + 0.5;
            // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
            float closestDepth = texture(shadowMap, projCoords.xy).r; 
            // get depth of current fragment from light's perspective
            float currentDepth = projCoords.z;
            // check whether current frag pos is in shadow
            float shadow = currentDepth-bias > closestDepth  ? 1.0 : 0.0;

            return shadow;
        }

        void main()
        {           
            vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
            vec3 normal = normalize(fs_in.Normal);
            vec3 lightColor = vec3(0.3);
            // ambient
            vec3 ambient = 0.3 * color;
            // diffuse
            vec3 lightDir = normalize(lightPos - fs_in.FragPos);
            float diff = max(dot(lightDir, normal), 0.0);
            vec3 diffuse = diff * lightColor;
            // specular
            vec3 viewDir = normalize(viewPos - fs_in.FragPos);
            vec3 reflectDir = reflect(-lightDir, normal);
            float spec = 0.0;
            vec3 halfwayDir = normalize(lightDir + viewDir);  
            spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
            vec3 specular = spec * lightColor;    
           
            bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
           // calculate shadow
            float shadow = ShadowCalculation(fs_in.FragPosLightSpace);                      
            vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
            FragColor = vec4(lighting, 1.0);
        }

)";

    shader->CreateShaderProgram(sceneVShader, sceneFShader);

    const char* simpleDepthVShaderSource=R"(
          #version 330 core
        layout (location = 0) in vec3 aPos;

        uniform mat4 lightSpaceMatrix;
        uniform mat4 model;

        void main()
        {
            gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
        }
)";

    const char* simpleDepthFShaderSource = R"(
         #version 330 core
        void main()
        {             
            // gl_FragDepth = gl_FragCoord.z;
        }
)";

    simpleDepthShader = new Shader(simpleDepthVShaderSource, simpleDepthFShaderSource);
    glGenFramebuffers(1, &depthMapFBO);
    glGenTextures(1, &depthMapTexture);
    glBindTexture(GL_TEXTURE_2D, depthMapTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LogUtil::GetInstance()->Error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    float planeVertices[] = {
         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
         25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 10.0f
    };
    unsigned int planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    woodTexture = ResourceLoader::GetInstance()->LoadImage("wood.png")->GetTexture();

    simpleDepthShader->Use();
    simpleDepthShader->SetInt("depthMap", 0);
    lightPos=glm::vec3(-2.0f, 4.0f, -1.0f);
    
    cubeVAO = 0;
    quadVAO = 0;
    glEnable(GL_DEPTH_TEST);


    shader->Use();
    shader->SetInt("diffuseTexture", 0);
    shader->SetInt("shadowMap", 1);

     debugDepthQuad = new Shader(debugDrawVShader,debugDrawFShader);
    debugDepthQuad->Use();
    debugDepthQuad->SetInt("depthMap", 0);
}

void Ex_ShadowMapping::Draw()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 7.5f;
    int osize = 20;
    lightProjection = glm::ortho(-1.0f*osize, 1.0f * osize, -1.0f * osize, 1.0f * osize, near_plane, far_plane);
    lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    simpleDepthShader->Use();
    simpleDepthShader->SetMat4f("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, shadowWidth, shadowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

    glClear(GL_DEPTH_BUFFER_BIT);
    RenderScene(simpleDepthShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Use();
    ScreenViewUtil::GetInstance()->SetUpShaderVPMatrix(shader);

    shader->SetVec3f("viewPos", Camera::MainCamera->position);
    shader->SetVec3f("lightPos", lightPos);
    shader->SetMat4f("lightSpaceMatrix", lightSpaceMatrix);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMapTexture);
    RenderScene(shader);


    debugDepthQuad->Use();
    debugDepthQuad->SetFloat("near_plane", near_plane);
    debugDepthQuad->SetFloat("far_plane", far_plane);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMapTexture);
    DrawQuad();
}

void Ex_ShadowMapping::RenderScene(Shader* shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    shader->SetMat4f("model", model);
    
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // cubes
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->SetMat4f("model", model);
    DrawCube();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->SetMat4f("model", model);
    DrawCube();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(0.25));
    shader->SetMat4f("model", model);
    DrawCube();
}

void Ex_ShadowMapping::DrawCube()
{
    // initialize (if necessary)
    if (cubeVAO == 0)
    {
        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            // right face
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

}

void Ex_ShadowMapping::DrawQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
