#pragma once

#include <memory>
#include <vector>

#include "Core/Layer.hpp"
#include "Core/Window.hpp"
#include "Core/LayerStack.hpp"
#include "Events/ApplicationEvent.hpp"

namespace Acroy {
    class Application
    {
    public:
        Application();
        virtual ~Application() {};

        void Run();
        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

    private:
        LayerStack m_layerStack;
        std::unique_ptr<Window> m_window;
        bool m_running = true;
    };

    Application* CreateApplication(); // Defined in Client
}
