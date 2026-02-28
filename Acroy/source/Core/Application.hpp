#pragma once

#include <memory>

#include "Core/Layer.hpp"
#include "Core/Window.hpp"
#include "Core/LayerStack.hpp"
#include "Events/ApplicationEvent.hpp"
#include "ImGui/ImGuiLayer.hpp"

namespace Acroy {
    class Application
    {
    public:
        Application();
        virtual ~Application() {};

        void Run();
        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application& GetApplicationInstance() { return *s_instance; }
        inline Window& GetWindow() const { return *m_window; }

        bool OnWindowResize(WindowResizeEvent& event);
        bool OnWindowClose(WindowCloseEvent& event);

    private:
        LayerStack m_layerStack;
        std::unique_ptr<Window> m_window;
        bool m_running = true;
        float m_lastFrameTime = 0.0f;
        ImGuiLayer* m_imGuiLayer;
        static Application* s_instance;
    };

    Application* CreateApplication(); // Defined in Client
}
