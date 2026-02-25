#pragma once

#include <functional>
#include <cstdint>
#include <string>
#include "Events/Event.hpp"
#include "Core/Timestep.hpp"
#include <GLFW/glfw3.h>

namespace Acroy
{
    struct WindowProps
    {
        std::string title;
        uint32_t width;
        uint32_t height;

        WindowProps(const std::string& title = "Acroy Application", uint32_t width = 1280, uint32_t height = 720)
        : title(title), width(width), height(height) {}
    };
    
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        Window(const WindowProps& props = WindowProps());
        ~Window();

        void Update();

        inline uint32_t GetWidth() const { return m_windowData.width; }
        inline uint32_t GetHeight() const { return m_windowData.height; }

        inline Timestep GetTime() const { return glfwGetTime(); }

        void SetEventCallback(const EventCallbackFn& callback) { m_windowData.eventCallback = callback; }
        void SetVSync(bool enabled);
        inline bool IsVSync() const { return m_windowData.vSync; }

        GLFWwindow* GetGlfwWindow() const { return m_window; }

    private:
        GLFWwindow* m_window;

        struct WindowData
        {
            std::string title;
            uint32_t width, height;
            bool vSync;

            EventCallbackFn eventCallback;
        };

        WindowData m_windowData;

        static bool s_glfwInitialized;
    };
}
