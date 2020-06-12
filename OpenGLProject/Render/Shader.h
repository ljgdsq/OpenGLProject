#pragma once
#include "ShaderSources/ShaderSources.h"
#include <glad/glad.h>
#include <string>
#include <map>
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
    static const char* modelStr;
    static const char* viewStr;
    static const char* projectionStr;
public:
    void Use();
    void SetBool(const std::string name, bool value) ;
    void SetInt(const std::string name, int value) ;
    void SetFloat(const std::string name, float value) ;

    void SetVec2f(const std::string name, float x, float y);
    void SetVec2f(const std::string name, glm::vec2 value);

    void SetVec3f(const std::string name, float x, float y, float z);
    void SetVec3f(const std::string name,glm::vec3 value);

    void SetVec4f(const std::string name, float x, float y, float z, float w);
    void SetVec4f(const std::string name, glm::vec4 value);

    void SetMat4f(const std::string name, glm::mat4x4 mat);
    void SetModelMat4f(glm::mat4x4 mat);
    void SetViewMat4f(glm::mat4x4 mat);
    void SetProjectionMat4f(glm::mat4x4 mat);

    static Shader* FindShader(const std::string name);
    static bool AddShader(const std::string name,Shader*shader);
    static bool RemoveShader(const std::string name);
private:
    static std::map<std::string, Shader*> _cachedShader;
};

