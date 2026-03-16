#pragma once

#include "../defext.h"

#ifdef __linux__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

class GlfwWindow
{
        GLFWwindow* window;
public:
        ENGINE_API GlfwWindow(const std::string title, const int width, const int height);
        ENGINE_API ~GlfwWindow();

        ENGINE_API bool isOpen();
        ENGINE_API void swapBuffers();

        ENGINE_API void createOpenGLContext();

        ENGINE_API void clear();
        ENGINE_API void clear(RGB8 rgb);
};

#endif