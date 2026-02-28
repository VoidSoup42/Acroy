#include "SandboxLayer.hpp"
#include <Core/Log.hpp>
#include <Renderer/Renderer.hpp>
#include <Events/ApplicationEvent.hpp>
#include <Events/MouseEvent.hpp>
#include <Renderer/Texture.hpp>
#include <Scene/Entity.hpp>
#include <Scene/Components.hpp>
#include <Renderer/PerspectiveCamera.hpp>
#include <imgui.h>

void SandboxLayer::OnAttach()
{
    ACROY_INFO("SandboxLayer attached");

    // ----------------------------------------
    // -------------- Ground ------------------
    // ----------------------------------------

    float planeVertices[] = {
        // positions          // normals         // texcoords
        -15.0f, 0.0f, -15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
         15.0f, 0.0f, -15.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         15.0f, 0.0f,  15.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -15.0f, 0.0f,  15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    uint32_t planeIndices[] = { 0, 1, 2, 2, 3, 0 };
    
    Acroy::BufferLayout layout = {
        { "a_position", Acroy::ShaderDataType::Float3, false },
        { "a_normal", Acroy::ShaderDataType::Float3, false },
        { "a_texCoord", Acroy::ShaderDataType::Float2, false }
    };
    Acroy::Ref<Acroy::Mesh> groundMesh = Acroy::CreateRef<Acroy::Mesh>(planeVertices, sizeof(planeVertices), planeIndices, sizeof(planeIndices) / sizeof(uint32_t), layout);
    Acroy::Ref<Acroy::Texture2D> groundTexture = Acroy::CreateRef<Acroy::Texture2D>("/home/sam/Downloads/Grass008_2K-JPG/Grass008_2K-JPG_Color.jpg");

    // ----------------------------------------
    // -------------- Cube --------------------
    // ----------------------------------------

    float cubeVertices[] = {
    //  Positions           Normals       TextureCoords
        // Front
       -0.5, -0.5,  0.5,    0,  0,  1,    0, 0,
        0.5, -0.5,  0.5,    0,  0,  1,    1, 0,
        0.5,  0.5,  0.5,    0,  0,  1,    1, 1,
       -0.5,  0.5,  0.5,    0,  0,  1,    0, 1,
        // Back
       -0.5, -0.5, -0.5,    0,  0, -1,    1, 0,
        0.5, -0.5, -0.5,    0,  0, -1,    0, 0,
        0.5,  0.5, -0.5,    0,  0, -1,    0, 1,
       -0.5,  0.5, -0.5,    0,  0, -1,    1, 1,
        // Left
       -0.5, -0.5, -0.5,   -1,  0,  0,    0, 0,
       -0.5, -0.5,  0.5,   -1,  0,  0,    1, 0,
       -0.5,  0.5,  0.5,   -1,  0,  0,    1, 1,
       -0.5,  0.5, -0.5,   -1,  0,  0,    0, 1,
        // Right
        0.5, -0.5, -0.5,    1,  0,  0,    1, 0,
        0.5, -0.5,  0.5,    1,  0,  0,    0, 0,
        0.5,  0.5,  0.5,    1,  0,  0,    0, 1,
        0.5,  0.5, -0.5,    1,  0,  0,    1, 1,
        // Top
       -0.5,  0.5, -0.5,    0,  1,  0,    0, 1,
       -0.5,  0.5,  0.5,    0,  1,  0,    0, 0,
        0.5,  0.5,  0.5,    0,  1,  0,    1, 0,
        0.5,  0.5, -0.5,    0,  1,  0,    1, 1,
        // Bottom
       -0.5, -0.5, -0.5,    0, -1,  0,    1, 1,
       -0.5, -0.5,  0.5,    0, -1,  0,    1, 0,
        0.5, -0.5,  0.5,    0, -1,  0,    0, 0,
        0.5, -0.5, -0.5,    0, -1,  0,    0, 1
    };

    uint32_t cubeIndices[] = {
        0,1,2,2,3,0,    4,5,6,6,7,4,
        8,9,10,10,11,8, 12,13,14,14,15,12,
        16,17,18,18,19,16, 20,21,22,22,23,20
    };

    Acroy::Ref<Acroy::Mesh> cubeMesh = Acroy::CreateRef<Acroy::Mesh>(cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t), layout);
 
    Acroy::Ref<Acroy::Texture2D> cubeTexture = Acroy::CreateRef<Acroy::Texture2D>("/home/sam/Documents/dev/OpenGL-Sandbox-main/resources/textures/Planks/planks.png");

    // ----------------------------------------
    // -------------- Shader ------------------
    // ----------------------------------------

    std::string vertexSrc = R"(
        #version 460 core
        layout(location = 0) in vec3 a_position;
        layout(location = 1) in vec3 a_normal;
        layout(location = 2) in vec2 a_texCoord;

        uniform mat4 u_model;
        uniform mat4 u_view;
        uniform mat4 u_proj;
        out vec2 v_texCoord;

        void main()
        {
            gl_Position = u_proj * u_view * u_model * vec4(a_position, 1.0);
            v_texCoord = a_texCoord;
        }
    )";

    std::string fragSrc = R"(
        #version 460 core

        out vec4 FragColor;
        in vec2 v_texCoord;

        uniform sampler2D u_texture;
        uniform float u_textureScale;

        void main()
        {
            FragColor = texture(u_texture, v_texCoord * u_textureScale);
        }
    )";

    Acroy::Ref<Acroy::Shader> shader = Acroy::CreateRef<Acroy::Shader>(vertexSrc, fragSrc);


    // ----------------------------------------
    // -------------- Setup Scene -------------
    // ----------------------------------------


    auto cam = Acroy::CreateRef<Acroy::PerspectiveCamera>(90.f, 16.0f/9.0f, 0.1f, 100.0f);


    m_scene = Acroy::CreateRef<Acroy::Scene>(cam);

    Acroy::Entity cameraEntity = m_scene->Create("Camera");
    cameraEntity.AddComponent<Acroy::CameraComponent>(cam);
    Acroy::TransformComponent& camTransform = cameraEntity.GetComponent<Acroy::TransformComponent>();
    camTransform.transform = glm::translate(camTransform.transform, glm::vec3(0.0, 1.0, 0.0));

    m_cameraController = Acroy::CreateScope<CameraController>(cameraEntity);

    // camTransform.transform = glm::translate(camTransform.transform, glm::vec3(0.0, 1.0, 5.0));

    Acroy::Entity groundEntity = m_scene->Create("Ground");
    groundEntity.AddComponent<Acroy::MeshComponent>(groundMesh);
    groundEntity.AddComponent<Acroy::ShaderComponent>(shader);

    Acroy::TextureComponent& groundTextureComponent = groundEntity.AddComponent<Acroy::TextureComponent>(groundTexture);
    groundTextureComponent.textureScale = 15.0f;

    Acroy::Entity cubeEntity = m_scene->Create("Cube");
    cubeEntity.AddComponent<Acroy::MeshComponent>(cubeMesh);
    cubeEntity.AddComponent<Acroy::ShaderComponent>(shader);
    Acroy::TextureComponent& cubeTextureComponent = cubeEntity.AddComponent<Acroy::TextureComponent>(cubeTexture);
    cubeTextureComponent.textureScale = 2.0f;

    glm::mat4& cubeTransform = cubeEntity.GetComponent<Acroy::TransformComponent>().transform;

    cubeTransform = glm::translate(cubeTransform, glm::vec3(0.0, 1.0, 0.0));
    cubeTransform = glm::scale(cubeTransform, glm::vec3(2.0f));
}

void SandboxLayer::OnUpdate(Acroy::Timestep timestep)
{
    Acroy::Renderer::SetClearColor({0.73f,0.81f,0.92f,1.0f});
    Acroy::Renderer::Clear();

    m_scene->OnUpdate(timestep);
    m_cameraController->OnUpdate(timestep);
}

void SandboxLayer::OnImGuiRender()
{
    ImGui::ShowDemoWindow();
}

void SandboxLayer::OnEvent(Acroy::Event& event)
{
    ACROY_TRACE("{0}", event.ToString());

    if (event.GetEventType() == Acroy::EventType::WindowResize)
    {
        auto e = dynamic_cast<Acroy::WindowResizeEvent*>(&event);
        m_scene->OnWindowResize(e->GetWidth(), e->GetHeight());
    }

    if (event.GetEventType() == Acroy::EventType::MouseButtonPressed)
    {
        auto e = dynamic_cast<Acroy::MouseButtonPressedEvent*>(&event);
        if (e->GetButton() == 1)
            m_cameraController->Activate();
    }

    if (event.GetEventType() == Acroy::EventType::MouseButtonReleased)
    {
        auto e = dynamic_cast<Acroy::MouseButtonReleasedEvent*>(&event);
        if (e->GetButton() == 1)
            m_cameraController->Deactivate();
    }
}
