#pragma once
#include "ShaderSources/ShaderSources.h"


class Shader
{
public:
    int shaderProgram;
    int vertexShader;
    int fragmentShader;

    static int INVALID_SHADER;

    Shader(const char* vertexShaderSource, const char* fragmentShaderSource, bool needDeleteAfterCompile = false);
private:
    bool needDeleteAfterCompile;
    
    void CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
};

