#pragma once
#include "ShaderSources/ShaderSources.h"
#include <glad/glad.h>
#include <string>


class Shader
{
public:
    static int INVALID_SHADER;
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource, bool needDeleteAfterCompile = false);
    Shader();

    int GetShaderProgram();
    void CreateShaderProgramFromFile(const char* vPath, const char* fPath);
    void CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

private:
    int shaderProgram;
    bool needDeleteAfterCompile;
    int vertexShader;
    int fragmentShader;
public:
    void SetBool(const std::string name, bool value) ;
    void SetInt(const std::string name, int value) ;
    void SetFloat(const std::string name, float value) ;

    void SetVec4f(const std::string name, float x, float y, float z, float w);
};

