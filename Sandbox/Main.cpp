#include <Acroy.hpp>
#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class GameLayer : public Acroy::Layer
{
private:
    Acroy::Renderer renderer;
    Acroy::RenderObject object;
    Acroy::Camera camera;

public:
    void OnAttach() override
    {
        std::cout << "Game Layer Attatched" << std::endl;

        object.mesh = Acroy::MeshFactory::CreateCube(glm::vec3(1.0));
        object.material = std::make_shared<Acroy::Material>();

        object.material->shader = std::make_shared<Acroy::Shader>(
            "/home/sam/Documents/dev/Acroy/Resources/Shaders/SimpleShader.vert",
            "/home/sam/Documents/dev/Acroy/Resources/Shaders/SimpleShader.frag");

        object.material->diffuseTexture =
            std::make_shared<Acroy::Texture>(
                "/home/sam/Pictures/Wallpapers/Wallpapers/a_beach_with_waves_and_rocks.jpg");

        object.material->diffuseColor = {1.0f, 1.0f, 1.0f};

        camera.SetPosition({0.0f, 0.0f, 2.0f}); // Move back 2 units
        camera.SetFOV(90.0);
    }

    void OnUpdate(float deltaTime) override
    {
        glm::vec2 windowSize = Acroy::Input::GetWindowSize();
        camera.SetAspectRatio(windowSize.x / windowSize.y);
        
        object.Rotate({0.0, deltaTime / 3, 0.0});
        
        renderer.Clear();
        renderer.SubmitObject(object);
        renderer.Draw(camera);
    }
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
