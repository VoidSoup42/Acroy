#include "AcroyPCH.hpp"
#include "Core/Application.hpp"
#include "Core/Input.hpp"
#include "Core/Log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
            glm::vec2 mousepos = Input::GetMousePosition();

            ACROY_CORE_TRACE("{}, {}", mousepos.x, mousepos.y);

            glClearColor(.75f, 0.1f, 0.35f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for (Layer* layer : m_layerStack)
                layer->OnUpdate();

            m_window->Update();
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_layerStack.PushOverlay(layer);
    }
}
