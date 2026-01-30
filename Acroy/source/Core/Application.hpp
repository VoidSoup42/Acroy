#pragma once

#include <memory>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/ext/scalar_uint_sized.hpp>

#include "Core/Layer.hpp"
#include "Core/Window.hpp"
#include "Core/LayerStack.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Renderer/Shader.hpp"

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

        inline static Application& GetApplicationInstance() {return *s_instance;}
        inline Window& GetWindow() const {return *m_window;}

    private:
        LayerStack m_layerStack;
        std::unique_ptr<Window> m_window;
        bool m_running = true;
        static Application* s_instance;

    // Temp
    private:
        uint32_t m_vertexArray, m_vertexBuffer, m_indexBuffer;
        std::unique_ptr<Shader> m_shader;
    };

    Application* CreateApplication(); // Defined in Client
}
