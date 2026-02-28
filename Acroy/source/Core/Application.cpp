#include "AcroyPCH.hpp"
#include "Application.hpp"
#include "Timestep.hpp"
#include "Log.hpp"
#include "Renderer/Renderer.hpp"
#include <imgui.h>

namespace Acroy
{
    Application* Application::s_instance = nullptr;

    Application::Application()
    {
        s_instance = this;
        
        m_window = std::make_unique<Window>();

        m_imGuiLayer = new ImGuiLayer;
        PushLayer(m_imGuiLayer);

        m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        m_window->SetVSync(false);

        Renderer::Init();
    }

    void Application::OnEvent(Event& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        event.handled |= event.IsInCategory(Acroy::EventCategory::EventCategoryMouseButton) & io.WantCaptureMouse;
        event.handled |= event.IsInCategory(Acroy::EventCategory::EventCategoryKeyboard) & io.WantCaptureKeyboard;

        if (event.GetEventType() == EventType::WindowClose)
            m_running = false;

		for (auto it = m_layerStack.begin(); it != m_layerStack.end(); ++it)
		{
			if (event.handled)
				break;
			(*it)->OnEvent(event);
		}

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
    }

    void Application::Run()
    {
        while (m_running)
        {
            float time = m_window->GetTime();
            Timestep ts = time - m_lastFrameTime;
            m_lastFrameTime = time;

            for (Layer* layer : m_layerStack)
            {
                layer->OnUpdate(ts);
            }

            m_imGuiLayer->Begin();
            for (Layer* layer : m_layerStack)
            {
                layer->OnImGuiRender();
            }
            m_imGuiLayer->End();

            m_window->Update();
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    bool Application::OnWindowResize(WindowResizeEvent& event)
    {
        Renderer::SetViewport(0, 0, event.GetWidth(), event.GetHeight());
        return true;
    }
}
