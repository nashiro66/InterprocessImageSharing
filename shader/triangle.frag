#version 330 core
#extension GL_ARB_explicit_attrib_location:enable

in vec3 color;
in vec2 texCoord;
uniform sampler2D texture;

out vec4 fragColor;

void main()
{
    fragColor = texture2D(texture, texCoord);
}