#include "glfw.hpp"

#ifdef __linux__

ENGINE_API GlfwWindow::GlfwWindow(const std::string title, const int width, const int height)
{
        if (!glfwInit())
        {
                std::cerr << "glfwInit failed\n";
                window = nullptr;
                return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

        glfwMakeContextCurrent(window);
}

ENGINE_API GlfwWindow::~GlfwWindow()
{
        glfwTerminate();
}

ENGINE_API bool GlfwWindow::isOpen()
{
        if(!glfwWindowShouldClose(window))
        {
                glfwPollEvents();
                return true;
        }
        
        return false;
}

ENGINE_API void GlfwWindow::swapBuffers()
{
        glfwSwapBuffers(window);
}

ENGINE_API void GlfwWindow::createOpenGLContext()
{
        glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK)
        {
                std::cerr << "fuck" << std::endl;
                return;
        }

        const GLubyte *version = glGetString(GL_VERSION);

	std::cout << "Created new OpenGL Context with version: " << version << "\n";

	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::cout << "Enabled:\nGL_DEPTH_TEST\nGL_BLEND\nglBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)" << std::endl;

	GLint samples;
	glGetIntegerv(GL_SAMPLES, &samples);

	std::cout << "Samples: " << samples << std::endl;

	glEnable(GL_MULTISAMPLE);
}

ENGINE_API void GlfwWindow::clear()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

ENGINE_API void GlfwWindow::clear(RGB8 rgb)
{
        glClearColor(rgb.r / 255.f, rgb.g / 255.f, rgb.b / 255.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

#endif