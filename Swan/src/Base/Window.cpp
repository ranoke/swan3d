#include "pch.h"
#include "Window.h"
// #include "Events.h"

#include <GLFW/glfw3.h>

#include <glad/glad.h>

namespace Swan
{
    Window::Window(const char *name, uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height)
    {
        {
            bool status;
            status = glfwInit();
            assert(status && "Failed to init glfw!");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, name, 0, 0);

        //
        assert(m_Window && "Failed to create window!\n FIX: export MESA_GLSL_VERSION_OVERRIDE=410; export MESA_GL_VERSION_OVERRIDE=4.1COMPAT");
        glfwMakeContextCurrent((GLFWwindow *)m_Window);
        {
            bool status;
            status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            assert(status && "Failed to init glad!");
        }

        SetVsync(0);

        // Set GLFW callbacks TODO
        // glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
        //     auto data = Window::GetData();
        //     data->Width = width;
        //     data->Height = height;

        //     WindowResizeEvent event(width, height);
        //     data->EventCallback(event);
        // });

        // glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
        //     auto data = Window::GetData();
        //     WindowCloseEvent event;
        //     data->EventCallback(event);
        // });

        // glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        //     auto data = Window::GetData();

        //     switch (action)
        //     {
        //     case GLFW_PRESS:
        //     {
        //         KeyPressedEvent event(key, 0);
        //         data->EventCallback(event);
        //         break;
        //     }
        //     case GLFW_RELEASE:
        //     {
        //         KeyReleasedEvent event(key);
        //         data->EventCallback(event);
        //         break;
        //     }
        //     case GLFW_REPEAT:
        //     {
        //         KeyPressedEvent event(key, 1);
        //         data->EventCallback(event);
        //         break;
        //     }
        //     }
        // });

        // glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        //     auto data = Window::GetData();

        //     switch (action)
        //     {
        //     case GLFW_PRESS:
        //     {
        //         MouseButtonPressedEvent event(button);
        //         data->EventCallback(event);
        //         break;
        //     }
        //     case GLFW_RELEASE:
        //     {
        //         MouseButtonReleasedEvent event(button);
        //         data->EventCallback(event);
        //         break;
        //     }
        //     }
        // });

        // glfwSetScrollCallback((GLFWwindow*)m_Window, [&](GLFWwindow *window, double xOffset, double yOffset) {

        //     MouseScrolledEvent event((float)xOffset, (float)yOffset);
        //     EventCallback(event);
        // });

        // glfwSetCursorPosCallback(m_Window, [&](GLFWwindow *window, double xPos, double yPos) {
        //     auto data = Window::GetData();

        //     MouseMovedEvent event((float)xPos, (float)yPos);
        //     data->EventCallback(event);
        // });
    }

    Window::~Window()
    {
        glfwDestroyWindow((GLFWwindow *)m_Window);
        glfwTerminate();
    }

    void Window::Update()
    {
        glfwSwapBuffers((GLFWwindow *)m_Window);
        glfwPollEvents();
    }

    void Window::SetVsync(bool vsync)
    {
        m_Vsync = vsync;
        glfwSwapInterval(m_Vsync);
    }

} // namespace Swan
