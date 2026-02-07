#include <Acroy.hpp>
#include "Platform/OpenGL/OpenGLShader.hpp"

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
    Acroy::Ref<Acroy::Texture2D> m_planeTexture;
    Acroy::Ref<Acroy::Texture2D> m_cubeTexture;

    Acroy::Ref<Acroy::VertexArray> m_planeVAO;
    Acroy::Ref<Acroy::VertexArray> m_cubeVAO;

    std::vector<glm::vec3> m_cubePositions;


    void OnAttach() override
    {
        // -------------------------------
        // ----------- Plane -------------
        // -------------------------------
        float planeVertices[] = {
            // positions          // normals         // texcoords
            -15.0f, 0.0f, -15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
             15.0f, 0.0f, -15.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
             15.0f, 0.0f,  15.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -15.0f, 0.0f,  15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
        };
        uint32_t planeIndices[] = { 0, 1, 2, 2, 3, 0 };

        m_planeVAO = Acroy::VertexArray::Create();
        auto planeVBO = Acroy::VertexBuffer::Create(planeVertices, sizeof(planeVertices));
        Acroy::BufferLayout layout = {
            { "position", Acroy::ShaderDataType::Float3 },
            { "normal",   Acroy::ShaderDataType::Float3 },
            { "texCoord", Acroy::ShaderDataType::Float2 }
        };
        planeVBO->SetLayout(layout);
        auto planeIBO = Acroy::IndexBuffer::Create(planeIndices, 6);
        m_planeVAO->AddVertexBuffer(planeVBO);
        m_planeVAO->SetIndexBuffer(planeIBO);

        // -------------------------------
        // ----------- Cubes -------------
        // -------------------------------
        float cubeVertices[] = {
            // Front face
            -0.5f,-0.5f, 0.5f, 0,0,1, 0,0,
             0.5f,-0.5f, 0.5f, 0,0,1, 1,0,
             0.5f, 0.5f, 0.5f, 0,0,1, 1,1,
            -0.5f, 0.5f, 0.5f, 0,0,1, 0,1,
            // Back face
            -0.5f,-0.5f,-0.5f, 0,0,-1, 1,0,
             0.5f,-0.5f,-0.5f, 0,0,-1, 0,0,
             0.5f, 0.5f,-0.5f, 0,0,-1, 0,1,
            -0.5f, 0.5f,-0.5f, 0,0,-1, 1,1,
            // Left
            -0.5f,-0.5f,-0.5f,-1,0,0, 0,0,
            -0.5f,-0.5f, 0.5f,-1,0,0, 1,0,
            -0.5f, 0.5f, 0.5f,-1,0,0, 1,1,
            -0.5f, 0.5f,-0.5f,-1,0,0, 0,1,
            // Right
             0.5f,-0.5f,-0.5f,1,0,0, 1,0,
             0.5f,-0.5f, 0.5f,1,0,0, 0,0,
             0.5f, 0.5f, 0.5f,1,0,0, 0,1,
             0.5f, 0.5f,-0.5f,1,0,0, 1,1,
            // Top
            -0.5f, 0.5f,-0.5f,0,1,0, 0,1,
            -0.5f, 0.5f, 0.5f,0,1,0, 0,0,
             0.5f, 0.5f, 0.5f,0,1,0, 1,0,
             0.5f, 0.5f,-0.5f,0,1,0, 1,1,
            // Bottom
            -0.5f,-0.5f,-0.5f,0,-1,0, 1,1,
            -0.5f,-0.5f, 0.5f,0,-1,0, 1,0,
             0.5f,-0.5f, 0.5f,0,-1,0, 0,0,
             0.5f,-0.5f,-0.5f,0,-1,0, 0,1
        };
        uint32_t cubeIndices[] = {
             0,1,2,2,3,0,    4,5,6,6,7,4,
             8,9,10,10,11,8, 12,13,14,14,15,12,
             16,17,18,18,19,16, 20,21,22,22,23,20
        };
        m_cubeVAO = Acroy::VertexArray::Create();
        auto cubeVBO = Acroy::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
        cubeVBO->SetLayout({
            { "position", Acroy::ShaderDataType::Float3 },
            { "normal",   Acroy::ShaderDataType::Float3 },
            { "texCoord", Acroy::ShaderDataType::Float2 }
        });
        auto cubeIBO = Acroy::IndexBuffer::Create(cubeIndices, 36);
        m_cubeVAO->AddVertexBuffer(cubeVBO);
        m_cubeVAO->SetIndexBuffer(cubeIBO);

        // -------------------------------
        // ----------- Shader ------------
        // -------------------------------
        std::string vertexSrc = R"(
            #version 460 core
            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec3 a_normal;
            layout(location = 2) in vec2 a_texCoord;
            uniform mat4 u_model;
            uniform mat4 u_view;
            uniform mat4 u_proj;
            out vec2 v_texCoord;
            void main() { gl_Position = u_proj * u_view * u_model * vec4(a_position, 1.0); v_texCoord = a_texCoord; }
        )";
        std::string fragSrc = R"(
            #version 460 core
            out vec4 FragColor;
            in vec2 v_texCoord;

            uniform sampler2D u_texture;
            uniform bool u_scaleTex; // For testing

            void main()
            {
                if (u_scaleTex)
                    FragColor = texture(u_texture, v_texCoord*20);
                
                else
                    FragColor = texture(u_texture, v_texCoord);
            }
        )";
        m_shader = Acroy::Shader::Create(vertexSrc, fragSrc);

        // -------------------------------
        // ----------- Textures ----------
        // -------------------------------
        m_planeTexture = Acroy::Texture2D::Create("/home/sam/Documents/dev/OpenGL-Sandbox-main/resources/textures/Planks/planks.png");
        m_cubeTexture  = Acroy::Texture2D::Create("/home/sam/Documents/dev/Neonix/Resources/Textures/kenney_prototype-textures/PNG/Green/texture_01.png");

        std::dynamic_pointer_cast<Acroy::OpenGLShader>(m_shader)->SetUniformInt("u_texture", 0);

        // -------------------------------
        // ----------- Camera ------------
        // -------------------------------
        m_camera = Acroy::CreateRef<Acroy::Camera>(80.0f, 16.0f/9.0f, 0.1f, 100.0f);
        m_cameraController = std::make_unique<CameraController>(m_camera.get(), 3.0f, 0.1f, glm::vec3(0,3,10));

        // Cube positions
        m_cubePositions = {
            glm::vec3(-4.0f,1.0f,-4.0f),
            glm::vec3( 4.0f,1.0f, 2.0f),
            glm::vec3(-4.0f,1.0f, 4.0f)
        };
    }

    void OnUpdate(Acroy::Timestep ts) override
    {
        m_cameraController->OnUpdate(ts);

        Acroy::RenderCommand::SetClearColor({0.73f,0.81f,0.92f,1.0f});
        Acroy::RenderCommand::Clear();

        Acroy::Renderer::BeginScene(*m_camera);

        // Render plane
        m_planeTexture->Bind(0);
        std::dynamic_pointer_cast<Acroy::OpenGLShader>(m_shader)->SetUniformInt("u_scaleTex", 1);
        Acroy::Renderer::Submit(m_planeVAO, m_shader, glm::mat4(1.0f));

        // Render cubes
        m_cubeTexture->Bind(0);
        std::dynamic_pointer_cast<Acroy::OpenGLShader>(m_shader)->SetUniformInt("u_scaleTex", 0);
        for (auto& pos : m_cubePositions)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
            Acroy::Renderer::Submit(m_cubeVAO, m_shader, model);
        }

        Acroy::Renderer::EndScene();
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
