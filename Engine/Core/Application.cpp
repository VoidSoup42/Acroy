#include "Application.hpp"

#include "../Graphics/Renderer.hpp"

namespace Acroy {
    Application::Application(const ApplicationProps& props)
    {
        _window = std::make_shared<Window>(props.windowWidth, props.windowHeight, props.title, props.fullscreen, props.vSync);
    }

    void Application::Run()
    {
        // Vertices
        std::vector<Vertex> vertices = {
            // Bottom-left
            {
                glm::vec3(-0.5f, -0.5f, 0.0f),
                glm::vec3(0.0f, 0.0f, 1.0f),
                glm::vec2(0.0f, 0.0f)
            },
            // Bottom-right
            {
                glm::vec3( 0.5f, -0.5f, 0.0f),
                glm::vec3(0.0f, 0.0f, 1.0f),
                glm::vec2(1.0f, 0.0f)
            },
            // Top-right
            {
                glm::vec3( 0.5f,  0.5f, 0.0f),
                glm::vec3(0.0f, 0.0f, 1.0f),
                glm::vec2(1.0f, 1.0f)
            },
            // Top-left
            {
                glm::vec3(-0.5f,  0.5f, 0.0f),
                glm::vec3(0.0f, 0.0f, 1.0f),
                glm::vec2(0.0f, 1.0f)
            }
        };

        // Indices (two triangles)
        std::vector<uint32_t> indices =
        {
            0, 1, 2,
            2, 3, 0
        };

        Shader shader("/home/sam/Documents/dev/Acroy/Resources/Shaders/SimpleShader.vert", "/home/sam/Documents/dev/Acroy/Resources/Shaders/SimpleShader.frag");
        
        Mesh mesh(vertices, indices);

        Renderer renderer;

        renderer.SubmitMesh(mesh);

        while (!_window->ShouldClose())
        {
            _window->SetClearColor({0.8, 0.05, 0.3, 1.0});
            _window->Clear();

            renderer.Draw(shader);


            _window->Update();
        }
    }
}