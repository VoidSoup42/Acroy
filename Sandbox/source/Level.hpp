#pragma once

#include <Core/Timestep.hpp>
#include <Scene/Scene.hpp>

class Level
{
public:
    void Load(const Acroy::Ref<Acroy::Camera> cam);
    void Update(Acroy::Timestep timestep);

private:
    Acroy::Ref<Acroy::Scene> m_scene;
};