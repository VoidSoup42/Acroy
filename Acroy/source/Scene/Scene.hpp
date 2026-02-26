#pragma once

#include <entt.hpp>
#include "Core/Timestep.hpp"
#include "Renderer/Camera.hpp"
#include "Core/Core.hpp"

namespace Acroy
{
    class Entity;
    class Scene
    {
    public:
        Scene(const Ref<Camera>& cam);
        
        Entity Create(const std::string& name = std::string());
        
        void OnUpdate(Timestep ts);
        
    private:
        entt::registry m_registry;
        Ref<Camera> m_camera;

        friend class Entity;
    };
}
