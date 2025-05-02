#define STB_IMAGE_IMPLEMENTATION

#include "TextureLoader.h"
#include "lib/stb_image.h"
#include <GL/gl.h>
#include <iostream>

unsigned int LoadTexture(const std::string &path)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (data)
    {
        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else
    {
        std::cerr << "Failed to load texture: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}