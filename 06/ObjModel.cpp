#define TINYOBJLOADER_IMPLEMENTATION
#include "ObjModel.h"
#include "TextureLoader.h"
#include <iostream>

void ObjModel::Load(const std::string &path, const std::string &baseDir)
{
    std::string warn, err;
    bool ret = tinyobj::LoadObj(&m_attrib, &m_shapes, &m_materials, &warn, &err, path.c_str(), baseDir.c_str(), true);
    if (!ret)
    {
        std::cerr << "Failed to Load OBJ: " << path << std::endl;
        return;
    }

    m_materialTextures.resize(m_materials.size(), 0);
    for (size_t i = 0; i < m_materials.size(); ++i)
    {
        if (!m_materials[i].diffuse_texname.empty())
        {
            m_materialTextures[i] = LoadTexture(baseDir + m_materials[i].diffuse_texname);
        }
    }
}

void ObjModel::Draw()
{
    for (const auto &shape: m_shapes)
    {
        size_t indexOffset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {
            int faceVertex = shape.mesh.num_face_vertices[f];
            int materialID = shape.mesh.material_ids[f];

            if (materialID >= 0 && materialID < m_materialTextures.size() && m_materialTextures[materialID])
            {
                glBindTexture(GL_TEXTURE_2D, m_materialTextures[materialID]);
            } else
            {
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            glBegin(GL_TRIANGLES);
            for (int v = 0; v < faceVertex; v++)
            {
                tinyobj::index_t index = shape.mesh.indices[indexOffset + v];

                if (!m_attrib.normals.empty() && index.normal_index >= 0)
                {
                    float nx = m_attrib.normals[3 * index.normal_index + 0];
                    float ny = m_attrib.normals[3 * index.normal_index + 1];
                    float nz = m_attrib.normals[3 * index.normal_index + 2];
                    glNormal3f(nx, ny, nz);
                } else
                {
                    glNormal3f(0.0f, 0.0f, 1.0f);
                }

                if (!m_attrib.texcoords.empty() && index.texcoord_index >= 0)
                {
                    float tx = m_attrib.texcoords[2 * index.texcoord_index + 0];
                    float ty = m_attrib.texcoords[2 * index.texcoord_index + 1];
                    glTexCoord2f(tx, ty);
                }

                float vx = m_attrib.vertices[3 * index.vertex_index + 0];
                float vy = m_attrib.vertices[3 * index.vertex_index + 1];
                float vz = m_attrib.vertices[3 * index.vertex_index + 2];
                glVertex3f(vx, vy, vz);
            }
            glEnd();

            indexOffset += faceVertex;
        }
    }
}
