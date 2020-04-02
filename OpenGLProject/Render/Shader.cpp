#include "Shader.h"
#include <iostream>
#include <glad/glad.h>


int Shader::INVALID_SHADER = -1;

Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource, bool needDeleteAfterCompile)
{
    shaderProgram = INVALID_SHADER;
    CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

    this->needDeleteAfterCompile = needDeleteAfterCompile;
}

void Shader::CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{

    int success;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }



}
