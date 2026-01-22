#pragma once
#include <GLFW/glfw3.h>
#include <cstdint>

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

    private:
        static bool _keys[MAX_KEYS];
        static bool _mouseButtons[MAX_BUTTONS];
        static double _mouseX;
        static double _mouseY;
        static GLFWwindow* _window;
    };
}