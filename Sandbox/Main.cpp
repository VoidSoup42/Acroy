#include <Acroy.hpp>
#include <iostream>
#include <vector>

using namespace Acroy;

class GameLayer : public Acroy::Layer
{
public:
    virtual void OnAttach() override
    {
        std::cout << "Game Layer Attatched" << std::endl;

        {
            std::vector<Vertex> vertices = {
                {{ -0.5f, -0.5f, 0.0f}, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
                {{  0.5f, -0.5f, 0.0f}, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
                {{  0.5f,  0.5f, 0.0f}, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
                {{ -0.5f,  0.5f, 0.0f}, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } }
            };

            std::vector<uint32_t> indices = {
                0, 1, 2,
                2, 3, 0
            };

            // Create render object
            _object = std::make_unique<RenderObject>();

            // Mesh
            _object->mesh = std::make_unique<Mesh>(vertices, indices);

            // Material
            _object->material = std::make_unique<Material>();
            _object->material->shader = std::make_unique<Shader>(
                "/home/sam/Documents/dev/Acroy/Resources/Shaders/SimpleShader.vert",
                "/home/sam/Documents/dev/Acroy/Resources/Shaders/SimpleShader.frag");

            _object->material->diffuseTexture =
                std::make_unique<Texture>(
                    "/home/sam/Pictures/Wallpapers/Wallpapers/a_beach_with_waves_and_rocks.jpg");

            _object->material->diffuseColor = {1.0f, 1.0f, 1.0f};

            _renderer.SubmitObject(std::move(_object));
        }
    }

    virtual void OnDetach() override
    {
        std::cout << "Game Layer Detached" << std::endl;
    }

    virtual void OnUpdate(float deltaTime) override
    {
        _renderer.Draw();
    }

private:
    Renderer _renderer;
    std::unique_ptr<RenderObject> _object;
};

int main()
{
    Acroy::ApplicationProps appProps;
    appProps.title = "Application";
    appProps.windowWidth = 1600;
    appProps.windowHeight = 900;
    appProps.fullscreen = false;
    appProps.vSync = true;

    Acroy::Application app(appProps);
    app.PushLayer<GameLayer>();
    app.Run();

    return 0;
}