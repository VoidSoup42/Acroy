#pragma once

#include <Core/Layer.hpp>
#include <Renderer/Camera.hpp>
#include <Core/Core.hpp>
#include "CameraController.hpp"

class SandboxLayer : public Acroy::Layer
{
public:
    void OnAttach() override;
    void OnUpdate(Acroy::Timestep timestep) override;
    void OnEvent(Acroy::Event& event) override;
    void OnImGuiRender() override;

private:
    Acroy::Ref<Acroy::Scene> m_scene;
    Acroy::Scope<CameraController> m_cameraController;
};
