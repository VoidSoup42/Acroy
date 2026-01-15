#pragma once

#include <memory>
#include "Window.hpp"

namespace Acroy {

    struct ApplicationProps
    {
        const char* title;
        uint32_t windowWidth;
        uint32_t windowHeight;
        bool fullscreen;
        bool vSync;
    };

    class Application
    {
    public:
        Application(const ApplicationProps& props);
        ~Application() = default;

        void Run();

    private:
        std::shared_ptr<Window> _window;
    };
}
