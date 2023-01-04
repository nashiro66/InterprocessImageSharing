#pragma once
#include <GL/glew.h>

class Offscreen
{
public:
    Offscreen(int width, int height);
    void Resize(int width, int height);
    GLuint GetColorBuffer();
    GLuint GetFrameBuffer();

private:
    GLuint colorBuffer;
    GLuint frameBuffer;
};