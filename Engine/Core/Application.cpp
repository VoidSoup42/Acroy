#include "Application.hpp"
#include "../Graphics/Renderer.hpp"

namespace Acroy
{
    Application::Application(const ApplicationProps &props)
    {
        _window = std::make_shared<Window>(props.windowWidth, props.windowHeight, props.title, props.fullscreen, props.vSync);
    }

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    void Application::Run()
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        for (const auto& layer : _layerStack)
        {
            layer->OnAttach();
        }

        while (!_window->ShouldClose())
        {
            _window->Clear();

            for (const auto& layer : _layerStack)
            {
                layer->OnUpdate(deltaTime);
            }

            _window->Update();
        }

        for (const auto& layer : _layerStack)
        {
            layer->OnDetach();
        }
    }
}