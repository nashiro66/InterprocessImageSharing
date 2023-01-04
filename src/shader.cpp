#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include "shader.hpp"

void Shader::CheckError(unsigned int shader)
{
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isSuccess);
    if (!isSuccess)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "vertex shader compile failed" << infoLog << std::endl;
    }
}

void Shader::Use()
{
    glUseProgram(shaderProgram);
}

void Shader::SetVec4(const std::string& name, glm::vec4 value)
{
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), value.x, value.y, value.z, value.w);
}

Shader::Shader(const char* vertFile, const char* fragFile)
{
    std::ifstream vertShaderFile;
    std::ifstream fragShaderFile;
    std::string vertCode;
    std::string fragCode;

    vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertShaderFile.open(vertFile);
        fragShaderFile.open(fragFile);

        // read files
        std::stringstream vertShaderStream, fragShaderStream;
        vertShaderStream << vertShaderFile.rdbuf();
        fragShaderStream << fragShaderFile.rdbuf();

        vertShaderFile.close();
        fragShaderFile.close();

        vertCode = vertShaderStream.str();
        fragCode = fragShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "can't read shader file" << std::endl;
    }

    const char* vertexShaderCode = vertCode.c_str();
    const char* fragmentShaderCode = fragCode.c_str();

    // generate shader module
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    CheckError(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    CheckError(fragmentShader);

    // create program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isSuccess);
    if (!isSuccess)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "can't create shader program" << infoLog << std::endl;
    }
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLint Shader::GetProgram()
{
    return shaderProgram;
}