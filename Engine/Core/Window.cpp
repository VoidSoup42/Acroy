#include "Window.hpp"
#include <print>

namespace Acroy {
    Window::Window(uint32_t width, uint32_t height, const char* title, bool fullscreen)
    {
        if (!glfwInit())
        {
            std::println("Failed to initialize glfw");
            return;
        }

        _window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

        if (!_window)
        {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(_window);

        if (glewInit() != GLEW_OK)
        {
            std::println("Failed to initialize glfw");
            return;
        }

        glViewport(0, 0, width, height);
    }

    Window::~Window()
    {
        glfwTerminate();
    }
    
    void Window::Update()
    {
        glClear(GL_COLOR_BUFFER_BIT);
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
