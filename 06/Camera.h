#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    Camera();
    void Update(GLFWwindow* window);
    glm::vec3 GetPosition() const;

private:
    float m_angleX, m_angleY;
};
