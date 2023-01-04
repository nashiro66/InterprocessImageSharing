#pragma once
#include <GL/glew.h>
#include <iostream>

class Texture
{
public:
    Texture(char const* fileName, bool mipmap);
    void Bind();
    void Resize(int width, int height);
    int GetTexWidth();
    int GetTexHeight();
    unsigned int GetTexId();

private:
    unsigned int texId;
    int texWidth;
    int texHeight;
};