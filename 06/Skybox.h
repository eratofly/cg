#pragma once
#include <string>

class Skybox {
public:
    void Load(const std::string& path);
    void Draw() const;

private:
    unsigned int m_textureID = 0;
};