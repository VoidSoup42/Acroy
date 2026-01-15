#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Acroy {
    class Window
    {
    public:
        Window(const uint32_t width, const uint32_t height, const char* title, const bool fullscreen, const bool vSync);
        ~Window();

        void SetClearColor(glm::vec4 color);
        bool ShouldClose();
        void Clear();
        void Update();
    
    private:
        GLFWwindow* _window;
    };
}
