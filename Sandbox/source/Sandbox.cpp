#include <Acroy.hpp>

class CameraController // Vibe Coded Camera Controller
{
public:
    CameraController(Acroy::Camera* camera, float moveSpeed, float sensitivity, const glm::vec3& startPos)
        : m_camera(camera), m_moveSpeed(moveSpeed), m_sensitivity(sensitivity), m_active(false),
          m_position(startPos), m_rotation(0.0f, 270.0f), m_velocity(0.0f),
          m_firstMouse(true), m_lastX(0.0), m_lastY(0.0), m_smoothTime(0.1f)
    {
        UpdateCamera();
    }

    void SetActive(bool enabled) { m_active = enabled; }
    bool IsActive() const { return m_active; }

    void OnUpdate(Acroy::Timestep ts)
    {
        float dt = ts.GetSeconds();

        if (m_active)
        {
            Acroy::Input::SetMouseMode(Acroy::MouseMode::Disabled);
        }
        else
        {
            Acroy::Input::SetMouseMode(Acroy::MouseMode::Normal);
            m_firstMouse = true;
            return;
        }

        glm::vec2 mousePos = Acroy::Input::GetMousePosition();

        if (m_firstMouse)
        {
            m_lastX = mousePos.x;
            m_lastY = mousePos.y;
            m_firstMouse = false;
            return;
        }

        glm::vec2 delta(mousePos.x - m_lastX, m_lastY - mousePos.y);
        m_lastX = mousePos.x;
        m_lastY = mousePos.y;

        m_rotation.x += delta.y * m_sensitivity;
        m_rotation.y += delta.x * m_sensitivity;
        m_rotation.x = glm::clamp(m_rotation.x, -89.0f, 89.0f);

        float pitch = glm::radians(m_rotation.x);
        float yaw   = glm::radians(m_rotation.y);

        glm::vec3 forward {
            glm::cos(yaw) * glm::cos(pitch),
            glm::sin(pitch),
            glm::sin(yaw) * glm::cos(pitch)
        };
        forward = glm::normalize(forward);

        glm::vec3 right = glm::normalize(glm::cross(forward, {0, 1, 0}));
        glm::vec3 up    = glm::normalize(glm::cross(right, forward));

        glm::vec3 dir{0.0f};

        if (Acroy::Input::IsKeyPressed(87)) dir += forward;  // W
        if (Acroy::Input::IsKeyPressed(83)) dir -= forward;  // S
        if (Acroy::Input::IsKeyPressed(68)) dir += right;    // D
        if (Acroy::Input::IsKeyPressed(65)) dir -= right;    // A
        if (Acroy::Input::IsKeyPressed(69)) dir += up;       // E
        if (Acroy::Input::IsKeyPressed(81)) dir -= up;       // Q

        float speed = m_moveSpeed;
        if (Acroy::Input::IsKeyPressed(341)) speed *= 0.3f;  // Ctrl
        if (Acroy::Input::IsKeyPressed(340)) speed *= 2.0f;  // Shift

        float lerp = 1.0f - std::exp(-dt / m_smoothTime);

        if (glm::length(dir) > 0.0f)
        {
            dir = glm::normalize(dir);
            m_velocity = glm::mix(m_velocity, dir * speed, lerp);
        }
        else
        {
            m_velocity = glm::mix(m_velocity, glm::vec3(0.0f), lerp);
        }

        m_position += m_velocity * dt;

        UpdateCamera();
    }

    void SetPosition(const glm::vec3& pos)
    {
        m_position = pos;
        UpdateCamera();
    }

private:
    void UpdateCamera()
    {
        m_camera->SetPosition(m_position);
        m_camera->SetRotation({ m_rotation.x, m_rotation.y, 0.0f });
    }

private:
    Acroy::Camera* m_camera;
    glm::vec3 m_position;
    glm::vec2 m_rotation;
    glm::vec3 m_velocity;

    float m_moveSpeed;
    float m_sensitivity;
    float m_smoothTime;

    bool   m_active;
    bool   m_firstMouse;
    double m_lastX;
    double m_lastY;
};


class GameLayer : public Acroy::Layer
{
private:
    std::unique_ptr<CameraController> m_cameraController;
    Acroy::Ref<Acroy::Camera> m_camera;
    Acroy::Ref<Acroy::Shader> m_shader;
    Acroy::Ref<Acroy::VertexArray> m_vao;

    void OnAttach() override
    {
        // -------------------------------
        // ----------- Buffers -----------
        // -------------------------------

        float vertices[] = {
            // Position          // Color
            -0.5f, -0.5f,  0.5f,  1, 0, 0, 1,   // Front-bottom-left: red
             0.5f, -0.5f,  0.5f,  0, 1, 0, 1,   // Front-bottom-right: green
             0.5f,  0.5f,  0.5f,  0, 0, 1, 1,   // Front-top-right: blue
            -0.5f,  0.5f,  0.5f,  1, 1, 0, 1,   // Front-top-left: yellow

            -0.5f, -0.5f, -0.5f,  1, 0, 1, 1,   // Back-bottom-left: magenta
             0.5f, -0.5f, -0.5f,  0, 1, 1, 1,   // Back-bottom-right: cyan
             0.5f,  0.5f, -0.5f,  1, 1, 1, 1,   // Back-top-right: white
            -0.5f,  0.5f, -0.5f,  0, 0, 0, 1    // Back-top-left: black
        };

        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0, // Front
            4, 5, 6, 6, 7, 4, // Back
            3, 2, 6, 6, 7, 3, // Top
            0, 1, 5, 5, 4, 0, // Bottom
            0, 3, 7, 7, 4, 0, // Left
            1, 2, 6, 6, 5, 1  // Right
        };

        m_vao = Acroy::VertexArray::Create();

        Acroy::Ref<Acroy::VertexBuffer> vbo = Acroy::VertexBuffer::Create(vertices, sizeof(vertices));

        Acroy::BufferLayout layout = {
            { "position", Acroy::ShaderDataType::Float3 },
            { "color",    Acroy::ShaderDataType::Float4 }
        };

        vbo->SetLayout(layout);

        Acroy::Ref<Acroy::IndexBuffer> ibo = Acroy::IndexBuffer::Create(indices, 36);

        m_vao->AddVertexBuffer(vbo);
        m_vao->SetIndexBuffer(ibo);

        // -------------------------------
        // ----------- Shader ------------
        // -------------------------------

        std::string vertexSrc = R"(
            #version 460 core
            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;

            out vec4 v_color;

            uniform mat4 u_view;
            uniform mat4 u_proj;

            void main()
            {
                gl_Position = u_proj * u_view * vec4(a_position, 1.0);
                v_color = a_color;
            }
        )";

        std::string fragmentSrc = R"(
            #version 460 core
            in vec4 v_color;
            out vec4 color;

            void main()
            {
                color = v_color;
            }
        )";

        m_shader = Acroy::Shader::Create(vertexSrc, fragmentSrc);

        // -------------------------------
        // ----------- Camera ------------
        // -------------------------------

        m_camera = Acroy::CreateRef<Acroy::Camera>(80.0f, 16.0f / 9.0f, 0.1f, 100.0f);
        m_cameraController = std::make_unique<CameraController>(m_camera.get(), 3.0f, 0.15f, glm::vec3(0.0f, 0.0f, 5.0f));
    }

    void OnEvent(Acroy::Event& event) override
    {
        if (event.GetEventType() == Acroy::EventType::MouseButtonPressed)
        {
            auto e = dynamic_cast<Acroy::MouseButtonPressedEvent*>(&event);
            if (e->GetButton() == 1)
            {
                m_cameraController->SetActive(true);
            }
        }
        if (event.GetEventType() == Acroy::EventType::MouseButtonReleased)
        {
            auto e = dynamic_cast<Acroy::MouseButtonReleasedEvent*>(&event);
            if (e->GetButton() == 1)
            {
                m_cameraController->SetActive(false);
            }
        }
    }

    void OnUpdate(Acroy::Timestep timestep) override
    {
        m_cameraController->OnUpdate(timestep);

        Acroy::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Acroy::RenderCommand::Clear();

        Acroy::Renderer::BeginScene(*m_camera);
        Acroy::Renderer::Submit(m_vao, m_shader);
        Acroy::Renderer::EndScene();
    }
};

class Sandbox : public Acroy::Application
{
public:
    Sandbox()
    {
        PushLayer(new GameLayer);
    }
};

Acroy::Application* Acroy::CreateApplication()
{
    return new Sandbox();
}
