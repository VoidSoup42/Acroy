#include "Application.hpp"


namespace Acroy {
    Application::Application(const ApplicationProps& props)
    {
        _window = std::make_shared<Window>(
            props.windowWidth,
            props.windowHeight,
            props.title,
            props.fullscreen,
            props.vSync
        );
    }

    void Application::Run()
    {
        while (!_window->ShouldClose())
        {
            _window->SetClearColor({0.8, 0.05, 0.3, 1.0});
            _window->Clear();
            _window->Update();
        }
    }
}