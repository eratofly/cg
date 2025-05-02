#pragma once
#include "lib/tiny_obj_loader.h"
#include <string>
#include <vector>
#include <GL/gl.h>

class ObjModel
{
public:
    void Load(const std::string &path, const std::string &baseDir);
    void Draw();

private:
    tinyobj::attrib_t m_attrib;
    std::vector<tinyobj::shape_t> m_shapes;
    std::vector<tinyobj::material_t> m_materials;
    std::vector<GLuint> m_materialTextures;
};