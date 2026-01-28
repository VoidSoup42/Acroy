#pragma  once

#include "Core/Window.hpp"
#include "GLFW/glfw3.h"

namespace Acroy {
    class LinuxWindow final : public Window
    {
    public:
        LinuxWindow(const WindowProps& props);
        virtual ~LinuxWindow();

        void Update() override;

        inline uint32_t GetWidth() const override { return m_windowData.width; }
        inline uint32_t GetHeight() const override { return  m_windowData.height; }

        void SetEventCallback(const EventCallbackFn& callback) override { m_windowData.eventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline void* GetNativeWindow() const override { return m_window; }

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
    };
}
