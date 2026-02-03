#include <Acroy.hpp>

class GameLayer : public Acroy::Layer
{
private:
    std::unique_ptr<Acroy::Shader> m_shader;
    std::shared_ptr<Acroy::VertexArray> m_vao;

    void OnAttach() override
    {
        // -------------------------------
        // ----------- Buffers -----------
        // -------------------------------
        
        float triangleVertices[] =
        {
            // pos              // color
           -0.5f, -0.5f, 0.0f,  1, 0, 0, 1,
            0.0f,  0.5f, 0.0f,  0, 1, 0, 1,
            0.5f, -0.5f, 0.0f,  0, 0, 1, 1
        };

        uint32_t triangleIndices[] = {0, 1, 2};

        m_vao.reset(Acroy::VertexArray::Create());

        std::shared_ptr<Acroy::VertexBuffer> vbo;
        vbo.reset(Acroy::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));

        Acroy::BufferLayout layout = {
            { "positon", Acroy::ShaderDataType::Float3 },
            { "color", Acroy::ShaderDataType::Float4 }
        };

        vbo->SetLayout(layout);

        std::shared_ptr<Acroy::IndexBuffer> ibo;
        ibo.reset(Acroy::IndexBuffer::Create(triangleIndices, 3));

        m_vao->AddVertexBuffer(vbo);
        m_vao->SetIndexBuffer(ibo);

        // -------------------------------
        // ----------- Shader ------------
        // -------------------------------
        std::string vertexSrc = R"(
            #version 460 core
            layout (location = 0) in vec3 a_position;
            layout (location = 1) in vec4 a_color;

            out vec4 v_color;

            void main()
            {
                gl_Position = vec4(a_position, 1.0);
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

        m_shader = std::make_unique<Acroy::Shader>(vertexSrc, fragmentSrc);
    }

    void OnUpdate() override
    {
        Acroy::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1.0});
        Acroy::RenderCommand::Clear();

        Acroy::Renderer::BeginScene();
        m_shader->Bind();
        Acroy::Renderer::Submit(m_vao);
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