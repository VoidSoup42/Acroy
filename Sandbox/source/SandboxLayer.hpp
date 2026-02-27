#pragma once

#include <Core/Layer.hpp>
#include <Renderer/Camera.hpp>
#include "Level.hpp"

class SandboxLayer : public Acroy::Layer
{
public:
    void OnAttach() override;
    void OnUpdate(Acroy::Timestep timestep) override;
    void OnEvent(Acroy::Event& event) override;
    void OnImGuiRender() override;

private:
    Level m_level;
};
