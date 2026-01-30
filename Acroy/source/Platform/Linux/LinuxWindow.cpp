#include "LinuxWindow.hpp"
#include "Core/Log.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Platform/OpenGL/OpenGLContext.hpp"
#include <glad/glad.h>

namespace Acroy {

    static bool s_glfwInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new LinuxWindow(props);
    }

    LinuxWindow::LinuxWindow(const WindowProps& props)
    {
        m_windowData.title = props.title;
        m_windowData.width = props.width;
        m_windowData.height = props.height;

        if (!s_glfwInitialized)
        {
            int success = glfwInit();
            ACROY_CORE_ASSERT(success, "Could not initialize GLFW!");
            s_glfwInitialized = true;
            
            glfwSetErrorCallback([](int error, const char* description)
            {
                ACROY_CORE_ERROR("GLFW Error ({}): {}", error, description);
            });
        }

        ACROY_CORE_INFO("Creating {} window: {} ({}, {})", glfwGetPlatform() == GLFW_PLATFORM_X11 ? "X11" : glfwGetPlatform() == GLFW_PLATFORM_WAYLAND ? "Wayland" : "Linux", props.title, props.width, props.height);

        m_window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
        m_context = new OpenGLContext(m_window);
        m_context->Init();

        glfwSetWindowUserPointer(m_window, &m_windowData);

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;

            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xpos, (float)ypos);
            data.eventCallback(event);
        });
    }

    void LinuxWindow::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    LinuxWindow::~LinuxWindow()
    {
        glfwDestroyWindow(m_window);
    }

    void LinuxWindow::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled ? 1 : 0);
        m_windowData.vSync = enabled;
    }

    bool LinuxWindow::IsVSync() const
    {
        return m_windowData.vSync;
    }
}
