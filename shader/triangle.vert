#version 330 core
#extension GL_ARB_explicit_attrib_location:enable

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec3 color;
out vec2 texCoord;

void main()
{
    gl_Position = vec4(aPosition, 1.0);
    color = aColor;
    texCoord = aTexCoord;
}