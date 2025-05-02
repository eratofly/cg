#include "Skybox.h"
#include "TextureLoader.h"
#include <GL/gl.h>
#include <cmath>

void Skybox::Load(const std::string &path)
{
    m_textureID = LoadTexture(path);
}

void Skybox::Draw() const
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    const float radius = 50.0f;
    const int verticalLines = 40;
    const int horizontLines = 40;

    for (auto i = 0; i < horizontLines; ++i)
    {
        float lat0 = M_PI * (-0.5f + (float)i / horizontLines);
        float lat1 = M_PI * (-0.5f + (float)(i + 1) / horizontLines);
        float z0 = sin(lat0);
        float zr0 = cos(lat0);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (auto j = 0; j <= verticalLines; ++j)
        {
            float longitude = 2 * M_PI * j / verticalLines;
            float x = cos(longitude);
            float y = sin(longitude);

            glTexCoord2f((float)j / verticalLines, (float)i / horizontLines);
            glVertex3f(radius * x * zr0, radius * y * zr0, radius * z0);

            glTexCoord2f((float)j / verticalLines, (float)(i + 1) / horizontLines);
            glVertex3f(radius * x * zr1, radius * y * zr1, radius * z1);
        }
        glEnd();
    }

    glEnable(GL_DEPTH_TEST);
}
