#pragma once
#include <GL/glew.h>

class Shader
{
public:
    void CheckError(unsigned int shader);
    void Use();
    void SetVec4(const std::string& name, glm::vec4 value);
    Shader(const char* vertFile, const char* fragFile);
    ~Shader();
    GLint GetProgram();

private:
    unsigned int shaderProgram;
    int isSuccess;
    char infoLog[512];
    unsigned int vertexShader;
    unsigned int fragmentShader;
};