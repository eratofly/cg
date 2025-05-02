#include "Application.h"
#include <GL/gl.h>
#include <GL/glu.h>

//убрать мельтешение - фильтрация
//повороты починить
//найти лучше текстуру для неба

Application::Application()
{
    if (!glfwInit())
    {
        m_window = nullptr;
    } else
    {
        m_window = glfwCreateWindow(800, 600, "Home", nullptr, nullptr);
        if (m_window)
        {
            glfwMakeContextCurrent(m_window);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_TEXTURE_2D);
            m_skybox.Load("home/sky.jpg");
            m_model.Load("home/home.obj", "home/");
        } else
        {
            glfwTerminate();
        }
    }
}

Application::~Application()
{
    glfwTerminate();
}

int Application::Run()
{
    if (!m_window)
    {
        return -1;
    }

    while (!glfwWindowShouldClose(m_window))
    {
        UpdateCamera();
        InitLight();

        GLfloat lightPos[] = { 0.0f, 10.0f, 10.0f, 0.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

        glm::vec3 camPos = m_camera.GetPosition();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, 800.f / 600.f, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(camPos.x, camPos.y, camPos.z, 0, 0, 0, 0, 1, 0);

        m_skybox.Draw();
        m_model.Draw();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    return 0;
}

void Application::UpdateCamera()
{
    m_camera.Update(m_window);
}

void Application::InitLight()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = { 0.0f, 10.0f, 10.0f, 0.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}