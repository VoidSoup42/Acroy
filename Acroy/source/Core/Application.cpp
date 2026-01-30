#include "AcroyPCH.hpp"
#include "Core/Application.hpp"
#include "Core/Input.hpp"
#include "Core/Log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Acroy
{
    Application* Application::s_instance = nullptr;

    #define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
    Application::Application()
    {
        s_instance = this;
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        // Temp
        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);

        const float vertices[] =
        {
            -0.5, -0.5, 0.0,
             0.0,  0.5, 0.0,
             0.5, -0.5, 0.0
        };
        const uint32_t indices[] = { 0, 1, 2 };
        glGenBuffers(1, &m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        std::string vertexSrc = R"(
            #version 460 core

            layout (location = 0) in vec3 a_position;

            out vec3 position;

            void main()
            {
                gl_Position = vec4(a_position, 1.0
                position = a_position;
            }
        
        )";

        std::string fragmentSrc = R"(
            #version 460 core

            out vec4 color;
            in vec3 position;

            void main()
            {
                color = vec4(position * 0.5 + 0.5, 1);
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

            // glClearColor(.75f, 0.1f, 0.35f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_shader->Bind();
            glBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
            
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
