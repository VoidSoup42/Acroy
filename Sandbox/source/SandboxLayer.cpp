#include "SandboxLayer.hpp"
#include <Core/Log.hpp>
#include <Renderer/Renderer.hpp>
#include <Events/ApplicationEvent.hpp>
#include <Events/MouseEvent.hpp>
#include <imgui.h>

void SandboxLayer::OnAttach()
{
    ACROY_INFO("SandboxLayer attached");

    m_level.Load();
}

void SandboxLayer::OnUpdate(Acroy::Timestep timestep)
{
    Acroy::Renderer::SetClearColor({0.73f,0.81f,0.92f,1.0f});
    Acroy::Renderer::Clear();

    m_level.Update(timestep);
}

void SandboxLayer::OnImGuiRender()
{
    // ImGui::ShowDemoWindow();
}

void SandboxLayer::OnEvent(Acroy::Event& event)
{
    ACROY_TRACE("{0}", event.ToString());

    if (event.GetEventType() == Acroy::EventType::WindowResize)
    {
        auto e = dynamic_cast<Acroy::WindowResizeEvent*>(&event);
        
        m_level.OnWindowResizeCallback(*e);
    }
}
