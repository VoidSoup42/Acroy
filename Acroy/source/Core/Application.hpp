#pragma once

#include <memory>
#include "Core/Window.hpp"
#include "Events/ApplicationEvent.hpp"

namespace Acroy {
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e);

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> m_window;
        bool m_running = true;
    };

    Application* CreateApplication(); // Defined in Client
}
