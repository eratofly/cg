cmake_minimum_required(VERSION 3.22)
project(house)

set(CMAKE_CXX_STANDARD 20)

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLUT REQUIRED)

add_executable(house
        main.cpp
        Application.h
        Application.cpp
        Camera.h
        Camera.cpp
        ObjModel.h
        ObjModel.cpp
        Skybox.h
        Skybox.cpp
        TextureLoader.h
        TextureLoader.cpp
        external/glad.c
)

target_include_directories(house PRIVATE
        external/include
)

target_link_libraries(house
        OpenGL::GL
        OpenGL::GLU
        glfw
        glm::glm
        GLUT::GLUT
)
