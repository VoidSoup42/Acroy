#include "Application.hpp"

#include "../Graphics/Renderer.hpp"

namespace Acroy
{
    Application::Application(const ApplicationProps &props)
    {
        _window = std::make_shared<Window>(props.windowWidth, props.windowHeight, props.title, props.fullscreen, props.vSync);
    }

    void Application::Run()
    {
        std::vector<Vertex> vertices = {
            {{-0.5f, -0.5f, 0.0f}, {0, 0, 1}, {0, 0}},
            {{0.5f, -0.5f, 0.0f}, {0, 0, 1}, {1, 0}},
            {{0.5f, 0.5f, 0.0f}, {0, 0, 1}, {1, 1}},
            {{-0.5f, 0.5f, 0.0f}, {0, 0, 1}, {0, 1}}};

        std::vector<uint32_t> indices = {
            0, 1, 2,
            2, 3, 0};

        Renderer renderer;

        // Create render object
        auto object = std::make_unique<RenderObject>();

        // Mesh
        object->mesh = std::make_unique<Mesh>(vertices, indices);

        // Material
        object->material = std::make_unique<Material>();
        object->material->shader = std::make_unique<Shader>(
            "/home/sam/Documents/dev/Acroy/Resources/Shaders/SimpleShader.vert",
            "/home/sam/Documents/dev/Acroy/Resources/Shaders/SimpleShader.frag");

        object->material->diffuseTexture =
            std::make_unique<Texture>(
                "/home/sam/Pictures/Wallpapers/Wallpapers/a_beach_with_waves_and_rocks.jpg");

        object->material->diffuseColor = {1.0f, 1.0f, 1.0f};

        renderer.SubmitObject(std::move(object));

        while (!_window->ShouldClose())
        {
            _window->SetClearColor({0.8f, 0.05f, 0.3f, 1.0f});
            _window->Clear();

            renderer.Draw();

            _window->Update();
        }
    }
}