#pragma once
#include "ExampleCommomHeader.h"
class Ex_ShadowMapping:public Renderer
{
    RENDERER_BASE_DECLARE(Ex_ShadowMapping)
private:
    class Shader* simpleDepthShader;
    class Shader* debugDepthQuad;

    unsigned int planeVAO,planeVBO;
    unsigned int quadVAO;
    unsigned int quadVBO;
    unsigned int cubeVAO;
    unsigned int cubeVBO;

    void RenderScene(class Shader* shader);
    void DrawCube();
    void DrawQuad();
    glm::vec3 lightPos;
    const unsigned int shadowWidth = 1024;
    const unsigned int shadowHeight = 1024;

    unsigned int depthMapTexture;
    unsigned int woodTexture;
    unsigned int depthMapFBO;

    int width;
    int height;

};

