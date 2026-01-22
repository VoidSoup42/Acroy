#include "Input.hpp"
#include <iostream>

namespace Acroy
{
    bool Input::_keys[MAX_KEYS] = { false };
    bool Input::_mouseButtons[MAX_BUTTONS] = { false };
    double Input::_mouseX = 0.0;
    double Input::_mouseY = 0.0;
    GLFWwindow* Input::_window = nullptr;

    void Input::Init(GLFWwindow* window)
    {
        _window = window;
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCursorPosCallback(window, CursorPositionCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
    }

    bool Input::IsKeyPressed(uint32_t keycode)
    {
        if (keycode >= MAX_KEYS)
            return false;
        return _keys[keycode];
    }

    bool Input::IsMouseButtonPressed(uint32_t button)
    {
        if (button >= MAX_BUTTONS)
            return false;
        return _mouseButtons[button];
    }

    void Input::GetMousePosition(double& x, double& y)
    {
        x = _mouseX;
        y = _mouseY;
    }

    void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key >= 0 && key < MAX_KEYS)
            _keys[key] = (action != GLFW_RELEASE);
    }

    void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
    {
        _mouseX = xpos;
        _mouseY = ypos;
    }

    void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        (void)window;
        (void)mods;
        if (button >= 0 && button < MAX_BUTTONS)
            _mouseButtons[button] = (action != GLFW_RELEASE);
    }

    void Input::SetCursorMode(bool enabled)
    {
        if (!_window) return;
        
        if (enabled)
        {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    glm::vec2 Input::GetWindowSize()
    {
        int width, height;
        glfwGetWindowSize(_window, &width, &height);
        return glm::vec2(static_cast<float>(width), static_cast<float>(height));
    }
}
