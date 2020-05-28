#pragma once
#include "ShaderSources/ShaderSources.h"
#include <glad/glad.h>
#include <string>

#include <glm/glm.hpp>
class Shader
{
public:
    static int INVALID_SHADER;
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource, bool needDeleteAfterCompile = true);
    Shader();

    int GetShaderProgram();
    void CreateShaderProgramFromFile(const char* vPath, const char* fPath);
    void CreateShaderProgramFromResource(const char* vertexShaderName,const char* fragmentShaderName);
    void CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
private:
    int shaderProgram;
    bool needDeleteAfterCompile;
    int vertexShader;
    int fragmentShader;
public:
    void Use();
    void SetBool(const std::string name, bool value) ;
    void SetInt(const std::string name, int value) ;
    void SetFloat(const std::string name, float value) ;

    void SetVec3f(const std::string name, float x, float y, float z);
    void SetVec4f(const std::string name, float x, float y, float z, float w);

    void SetMat4f(const std::string name, glm::mat4x4 mat);
};

