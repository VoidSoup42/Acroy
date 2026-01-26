#include "LinuxWindow.hpp"
#include "Core/Log.hpp"
#include "Core/Core.hpp"

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
        }

        ACROY_CORE_INFO("Creating {} window: {} ({}, {})", glfwGetPlatform() == GLFW_PLATFORM_X11 ? "X11" : glfwGetPlatform() == GLFW_PLATFORM_WAYLAND ? "Wayland" : "Linux", props.title, props.width, props.height);

        m_window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_windowData);
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
