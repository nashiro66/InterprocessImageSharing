#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(char const* fileName, bool mipmap)
{
    // load texture
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int channels;
    unsigned char* data = stbi_load(fileName, &texWidth, &texHeight, &channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        if(mipmap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else
    {
        std::cerr << "can't load image" << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, texId);
}

void Texture::Resize(int width, int height)
{
    texWidth = width;
    texHeight = height;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
}


int Texture::GetTexWidth()
{
    return texWidth;
}

int Texture::GetTexHeight()
{
    return texHeight;
}

unsigned Texture::GetTexId()
{
    return texId;
}
