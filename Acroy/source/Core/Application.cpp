#include "AcroyPCH.hpp"
#include "Core/Application.hpp"
#include "Core/Input.hpp"
#include "Core/Log.hpp"

#include <GLFW/glfw3.h>
#include "Renderer/Renderer.hpp"

namespace Acroy
{
    Application* Application::s_instance = nullptr;

    #define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

    Application::Application()
    {
        s_instance = this;
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));


        // =========================
        // Triangle
        // =========================
        m_vertexArray.reset(VertexArray::Create());

        float triangleVertices[] =
        {
            // pos              // color
            -0.5f, -0.5f, 0.0f,  1, 0, 0, 1,
            0.0f,  0.5f, 0.0f,  0, 1, 0, 1,
            0.5f, -0.5f, 0.0f,  0, 0, 1, 1
        };

        uint32_t triangleIndices[] = { 0, 1, 2 };

        std::shared_ptr<VertexBuffer> triangleVB;
        triangleVB.reset(VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
        std::shared_ptr<IndexBuffer> triangleIB;
        triangleIB.reset(IndexBuffer::Create(triangleIndices, 3));

        BufferLayout layout =
        {
            { "Position", ShaderDataType::Float3 },
            { "Color",    ShaderDataType::Float4 }
        };

        triangleVB->SetLayout(layout);
        m_vertexArray->AddVertexBuffer(triangleVB);
        m_vertexArray->SetIndexBuffer(triangleIB);

        // =========================
        // Square
        // =========================
        m_SquareVA.reset(VertexArray::Create());

        float squareVertices[] =
        {
            // pos              // color
            -0.75f, -0.5f, 0.0f,  1, 0, 0, 1,
            -0.25f, -0.5f, 0.0f,  0, 1, 0, 1,
            -0.25f,  0.5f, 0.0f,  0, 0, 1, 1,
            -0.75f,  0.5f, 0.0f,  1, 1, 0, 1
        };

        uint32_t squareIndices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, 6));

        squareVB->SetLayout(layout);
        m_SquareVA->AddVertexBuffer(squareVB);
        m_SquareVA->SetIndexBuffer(squareIB);

        auto test = squareVB->GetLayout();

        // =========================
        // Shader
        // =========================
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

        m_shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
    }

    void Application::OnEvent(Event& event)
    {
        if (event.GetEventType() == EventType::WindowClose)
            m_running = false;

		for (auto it = m_layerStack.begin(); it != m_layerStack.end(); ++it)
		{
			if (event.handled)
				break;
			(*it)->OnEvent(event);
		}
    }

    void Application::Run()
    {
        while (m_running)
        {

            RenderCommand::SetClearColor({(float)35/255, (float)35/255, (float)35/255, 1.0f});
            RenderCommand::Clear();

            m_shader->Bind();

            m_vertexArray->Bind();
            RenderCommand::DrawIndexed(m_vertexArray);
            m_SquareVA->Bind();
            RenderCommand::DrawIndexed(m_SquareVA);
            
            // Renderer::BeginScene();

            // m_shader->Bind();

            // Renderer::Submit(m_vertexArray, 3);
            // Renderer::Submit(m_SquareVA, 6);

            // Renderer::EndScene();
            
            for (Layer* layer : m_layerStack)
                layer->OnUpdate();

            m_window->Update();
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_layerStack.PushOverlay(layer);
    }
}
