#include "Shader.h"
#include <iostream>
#include "../Utils/LogUtil.h"
#include "../Utils/FileUtil.h"

int Shader::INVALID_SHADER = -1;

Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource, bool needDeleteAfterCompile)
{
    shaderProgram = INVALID_SHADER;
    vertexShader = INVALID_SHADER;
    fragmentShader = INVALID_SHADER;
    CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

    this->needDeleteAfterCompile = needDeleteAfterCompile;
}

Shader::Shader()
{
    vertexShader = INVALID_SHADER;
    fragmentShader = INVALID_SHADER;
    shaderProgram = INVALID_SHADER;
    this->needDeleteAfterCompile = true;
}

int Shader::GetShaderProgram()
{
    if (shaderProgram == INVALID_SHADER)
    {
        LogUtil::GetInstance()->Error("INVALID_SHADER ! you must call CreateShaderProgramFromFile first!");
    }
    return shaderProgram;
}

void Shader::CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{

    if (shaderProgram != INVALID_SHADER)
    {
        LogUtil::GetInstance()->Warn("you already have a shader program do not create again!");
        return;
    }

    int success;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        LogUtil::GetInstance()->Error("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
        LogUtil::GetInstance()->Error(infoLog);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        LogUtil::GetInstance()->Error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
        LogUtil::GetInstance()->Error(infoLog);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        LogUtil::GetInstance()->Error("ERROR::SHADER::PROGRAM::LINKING_FAILED");
        LogUtil::GetInstance()->Error(infoLog);
    }
    if (needDeleteAfterCompile)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        vertexShader = INVALID_SHADER;
        fragmentShader = INVALID_SHADER;
    }

}

void Shader::CreateShaderProgramFromFile(const char* vPath, const char* fPath)
{
    if (shaderProgram!=INVALID_SHADER)
    {
        LogUtil::GetInstance()->Warn("you already have a shader program do not create again!");
        return;
    }
    auto vSource=FileUtil::GetInstance()->LoadStringFromFile(vPath);
    auto fSource=FileUtil::GetInstance()->LoadStringFromFile(fPath);
    CreateShaderProgram(vSource.c_str(), fSource.c_str());
}

void Shader::CreateShaderProgramFromResource(const char* vertexShaderName, const char* fragmentShaderName)
{
    auto vSource = FileUtil::GetInstance()->LoadStringFromProjectResource(vertexShaderName);
    auto fSource = FileUtil::GetInstance()->LoadStringFromProjectResource(fragmentShaderName);
    CreateShaderProgram(vSource.c_str(), fSource.c_str());
}

void Shader::Use()
{
    glUseProgram(GetShaderProgram());
}

void Shader::SetBool(const std::string name, bool value)
{
    glUniform1i(glGetUniformLocation(GetShaderProgram(), name.c_str()), (int)value);
}

void Shader::SetInt(const std::string name, int value) 
{
    glUniform1i(glGetUniformLocation(GetShaderProgram(), name.c_str()), value);

}

void Shader::SetFloat(const std::string name, float value) 
{
    glUniform1f(glGetUniformLocation(GetShaderProgram(), name.c_str()), value);

}

void Shader::SetVec3f(const std::string name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(GetShaderProgram(), name.c_str()), x, y, z);
}

void Shader::SetVec4f(const std::string name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(GetShaderProgram(), name.c_str()), x, y, z, w);
}
