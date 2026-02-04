#include "Platform/Linux/LinuxInput.hpp"
#include "Core/Application.hpp"
#include <GLFW/glfw3.h>

namespace Acroy {
    
    Input* Input::s_instance = new LinuxInput();
    
    bool LinuxInput::IsKeyPressedImpl(int keycode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplicationInstance().GetWindow().GetNativeWindow());
        int state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::IsMouseButtonPressedImpl(int button)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplicationInstance().GetWindow().GetNativeWindow());
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    glm::vec2 LinuxInput::GetMousePositionImpl()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplicationInstance().GetWindow().GetNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return { static_cast<float>(x), static_cast<float>(y) };
    }

    void LinuxInput::SetMouseModeImpl(MouseMode mode)
    {
        if (mode == m_mouseMode)
            return;

        int glfwMode = GLFW_CURSOR_NORMAL;

        switch (mode)
        {
            case MouseMode::Normal:    glfwMode = GLFW_CURSOR_NORMAL;   break;
            case MouseMode::Hidden:    glfwMode = GLFW_CURSOR_HIDDEN;   break;
            case MouseMode::Disabled:  glfwMode = GLFW_CURSOR_DISABLED; break;
        }

        GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplicationInstance().GetWindow().GetNativeWindow());
        glfwSetInputMode(window, GLFW_CURSOR, glfwMode);
        m_mouseMode = mode;
    }
}
