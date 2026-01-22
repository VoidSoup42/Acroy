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
}