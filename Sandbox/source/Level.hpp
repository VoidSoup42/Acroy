#pragma once

#include <Core/Timestep.hpp>
#include <Scene/Scene.hpp>
#include <Events/ApplicationEvent.hpp>

class Level
{
public:
    void Load();
    void Update(Acroy::Timestep timestep);

    void OnWindowResizeCallback(Acroy::WindowResizeEvent& e);

private:
    Acroy::Ref<Acroy::Scene> m_scene;
};