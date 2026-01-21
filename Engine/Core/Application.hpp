#pragma once

#include <vector>
#include <memory>

#include "Window.hpp"
#include "../Graphics/Layer.hpp"

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

        template<typename TLayer>
        void PushLayer()
        {
            _layerStack.emplace_back(std::make_unique<TLayer>());
        }

        void Run();

    private:
        std::shared_ptr<Window> _window;
        std::vector<std::unique_ptr<Layer>> _layerStack;
    };
}
