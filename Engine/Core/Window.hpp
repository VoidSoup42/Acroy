#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Acroy {
    class Window
    {
    public:
        Window(uint32_t width, uint32_t height, const char* title, bool fullscreen);
        ~Window();

        void SetClearColor(glm::vec4 color);
        bool ShouldClose();
        void Update();
    
    private:
        GLFWwindow* _window;
    };
}
