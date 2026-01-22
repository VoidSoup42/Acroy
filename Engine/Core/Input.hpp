#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>
#include <glm/vec2.hpp>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace Acroy
{
    class Input
    {
    public:
        static void Init(GLFWwindow* window);

        static bool IsKeyPressed(uint32_t keycode);
        static bool IsMouseButtonPressed(uint32_t button);
        static void GetMousePosition(double& x, double& y);
        static void SetCursorMode(bool enabled);

        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

        static glm::vec2 GetWindowSize();

    private:
        static bool _keys[MAX_KEYS];
        static bool _mouseButtons[MAX_BUTTONS];
        static double _mouseX;
        static double _mouseY;
        static GLFWwindow* _window;
    };
}
