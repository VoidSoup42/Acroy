#include "Application.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Core/Log.hpp"

namespace Acroy
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);
        ACROY_CORE_INFO(e.ToString());
        while (true);
    }
}
