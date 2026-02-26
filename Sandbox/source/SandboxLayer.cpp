#include "SandboxLayer.hpp"
#include <Core/Log.hpp>
#include <Renderer/Renderer.hpp>

void SandboxLayer::OnAttach()
{
    ACROY_INFO("SandboxLayer attached");

    m_camera = Acroy::CreateRef<Acroy::Camera>(80.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);

    m_cameraController = std::make_unique<CameraController>(m_camera.get(), 3.0f, 0.1f, glm::vec3(0,1,10));
    m_cameraController->SetActive(true);

    m_level.Load(m_camera);
}

void SandboxLayer::OnUpdate(Acroy::Timestep timestep)
{
    Acroy::Renderer::SetClearColor({0.73f,0.81f,0.92f,1.0f});
    Acroy::Renderer::Clear();

    m_cameraController->OnUpdate(timestep);
    m_level.Update(timestep);
}

void SandboxLayer::OnEvent(Acroy::Event& event)
{
    ACROY_TRACE("{0}", event.ToString());
}
