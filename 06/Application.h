#pragma once

#include <GLFW/glfw3.h>
#include "Skybox.h"
#include "ObjModel.h"
#include "Camera.h"
#include "TextureLoader.h"

class Application
{
public:
    Application();

    ~Application();

    int Run();

private:
    GLFWwindow *m_window;
    Camera m_camera;
    Skybox m_skybox;
    ObjModel m_model;

    void UpdateCamera();

    static void InitLight();
};