#pragma once

#include <memory>
#include "Core/Window.hpp"

namespace Acroy {
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<Window> m_window;
        bool m_running = true;
    };

    Application* CreateApplication(); // Defined in Client
}
