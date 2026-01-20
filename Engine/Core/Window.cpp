#include "Window.hpp"
#include <print>

namespace Acroy {
    Window::Window(const uint32_t width, const uint32_t height, const char* title, const bool fullscreen, const bool vSync)
    {
        if (!glfwInit())
        {
            std::println("Failed to initialize glfw");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        _window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

        if (!_window)
        {
            glfwTerminate();
            return;
        }

        glfwSwapInterval(vSync ? 1 : 0);
        glfwMakeContextCurrent(_window);
        glewInit();

        // glViewport(0, 0, width, height);
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    void Window::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void Window::Update()
    {
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    bool Window::ShouldClose()
    {
        return static_cast<bool>(glfwWindowShouldClose(_window));
    }

    void Window::SetClearColor(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
}
