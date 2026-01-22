#include <Acroy.hpp>
#include <iostream>
#include <vector>

class GameLayer : public Acroy::Layer
{
public:
    virtual void OnAttach() override
    {
        std::cout << "Game Layer Attatched" << std::endl;

        std::vector<Acroy::Vertex> vertices = {
            //     Position               Normal                 Color             TexCoord
            {{ -0.5f, -0.5f, 0.0f}, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
            {{  0.5f, -0.5f, 0.0f}, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
            {{  0.5f,  0.5f, 0.0f}, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },
            {{ -0.5f,  0.5f, 0.0f}, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } }
        };

        std::vector<uint32_t> indices = {
            0, 1, 2,
            2, 3, 0
        };

        object.mesh = std::make_shared<Acroy::Mesh>(vertices, indices);
        object.material = std::make_shared<Acroy::Material>();

        object.material->shader = std::make_shared<Acroy::Shader>(
            "/home/sam/Documents/dev/Acroy/Resources/Shaders/SimpleShader.vert",
            "/home/sam/Documents/dev/Acroy/Resources/Shaders/SimpleShader.frag");

        object.material->diffuseTexture =
            std::make_shared<Acroy::Texture>(
                "/home/sam/Pictures/Wallpapers/Wallpapers/a_beach_with_waves_and_rocks.jpg");

        object.material->diffuseColor = {1.0f, 1.0f, 1.0f};
    
    }

    virtual void OnDetach() override
    {
        std::cout << "Game Layer Detached" << std::endl;
    }

    virtual void OnUpdate(float deltaTime) override
    {
        if (Acroy::Input::IsKeyPressed(GLFW_KEY_A))
        {
            renderer.Draw();
            renderer.Clear();
            renderer.SubmitObject(object);
        }
    }

private:
    Acroy::Renderer renderer;
    Acroy::RenderObject object;
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
