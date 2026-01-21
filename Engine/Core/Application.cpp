#include "Application.hpp"

#include "../Graphics/Renderer.hpp"
#include "../Graphics/Texture.hpp"

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

        Texture tex("/home/sam/Pictures/Wallpapers/mountain-scenery-digital-art-4k-wallpaper-uhdpaper.com-180@1@n.jpg");



        while (!_window->ShouldClose())
        {
            _window->SetClearColor({0.8, 0.05, 0.3, 1.0});
            _window->Clear();

            glActiveTexture(GL_TEXTURE0 + 0);
            glBindTexture(GL_TEXTURE_2D, tex.GetTexture());

            shader.SetUniformInt("u_texture", 0);

            renderer.Draw(shader);
            
            _window->Update();
        }
    }
}