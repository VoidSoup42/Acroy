#include "AcroyPCH.hpp"
#include "Application.hpp"
#include "Core/Log.hpp"

namespace Acroy
{
    #define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
    Application::Application()
    {
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

        ACROY_CORE_TRACE("{}", e.ToString());
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_running = false;
        return true;
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_running)
        {
            m_window->Update();
        }
    }
}
