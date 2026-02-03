#include "AcroyPCH.hpp"
#include "Core/Application.hpp"
#include "Core/Log.hpp"
#include <glad/glad.h>

namespace Acroy
{
    Application* Application::s_instance = nullptr;

    #define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

    Application::Application()
    {
        s_instance = this;
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
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
            for (Layer* layer : m_layerStack)
                layer->OnUpdate();

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
