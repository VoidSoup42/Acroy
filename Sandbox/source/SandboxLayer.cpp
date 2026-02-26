#include "SandboxLayer.hpp"
#include <Core/Log.hpp>
#include <Renderer/Renderer.hpp>
#include <Events/ApplicationEvent.hpp>
#include <Events/MouseEvent.hpp>
#include <imgui.h>

void SandboxLayer::OnAttach()
{
    ACROY_INFO("SandboxLayer attached");

    m_camera = Acroy::CreateRef<Acroy::Camera>(80.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
    m_cameraController = std::make_unique<CameraController>(m_camera.get(), 3.0f, 0.1f, glm::vec3(0,1,10));

    m_level.Load(m_camera);
}

void SandboxLayer::OnUpdate(Acroy::Timestep timestep)
{
    Acroy::Renderer::SetClearColor({0.73f,0.81f,0.92f,1.0f});
    Acroy::Renderer::Clear();

    m_cameraController->OnUpdate(timestep);
    m_level.Update(timestep);
}

void SandboxLayer::OnImGuiRender()
{
    ImGui::ShowDemoWindow();
}

void SandboxLayer::OnEvent(Acroy::Event& event)
{
    // ACROY_TRACE("{0}", event.ToString());

    if (event.GetEventType() == Acroy::EventType::WindowResize)
    {
        auto e = dynamic_cast<Acroy::WindowResizeEvent*>(&event);
        m_camera->SetAspect((float)e->GetWidth() / e->GetHeight());
    }

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
