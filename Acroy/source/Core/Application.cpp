#include "AcroyPCH.hpp"
#include "Core/Application.hpp"
#include "Core/Timestep.hpp"
#include "Core/Log.hpp"
#include "Renderer/Renderer.hpp"

namespace Acroy
{
    Application* Application::s_instance = nullptr;

    #define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

    Application::Application()
    {
        s_instance = this;
        
        m_window = std::make_unique<Window>();

        m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        m_window->SetVSync(false);

        Renderer::Init();
    }

    void Application::OnEvent(Event& event)
    {
        if (event.GetEventType() == EventType::WindowClose)
            m_running = false;

		for (auto it = m_layerStack.begin(); it != m_layerStack.end(); ++it)
		{
			if (event.handled)
				break;
			(*it)->OnEvent(event);
		}
    }

    void Application::Run()
    {
        while (m_running)
        {
            float time = m_window->GetTime();
            Timestep ts = time - m_lastFrameTime;
            m_lastFrameTime = time;

            for (Layer* layer : m_layerStack)
                layer->OnUpdate(ts);

            m_window->Update();
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_layerStack.PushOverlay(layer);
        layer->OnAttach();
    }
}
