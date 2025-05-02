#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : m_angleX(0), m_angleY(0)
{}

void Camera::Update(GLFWwindow *window)
{
    const float speed = 1.0f;
    static float lastTime = glfwGetTime();
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_angleY -= speed * deltaTime;
    }
    //камера не должна знать про окно, в окне обрабатывать, а камере пердавать, передавать структуру с нажатыми кнопками
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_angleY += speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_angleX -= speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_angleX += speed * deltaTime;
    }
}

glm::vec3 Camera::GetPosition() const
{
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation = glm::rotate(rotation, m_angleX, glm::vec3(1.0f, 0.0f, 0.0f));
    rotation = glm::rotate(rotation, m_angleY, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec4 camTarget = rotation * glm::vec4(0.0f, 0.0f, 15.0f, 1.0f);
    return glm::vec3(camTarget);
}