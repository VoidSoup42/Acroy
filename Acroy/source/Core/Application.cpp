#include "Application.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Core/Log.hpp"

namespace Acroy
{
    Application::Application()
    {
        m_window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_running)
        {
            // glClearColor(0.75f, 0.1f, 0.35f, 1.0f);
            // glClear(GL_COLOR_BUFFER_BIT);
            m_window->Update();
        }
    }
}
