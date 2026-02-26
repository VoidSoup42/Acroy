#pragma once

#include <entt.hpp>
#include "Scene.hpp"
#include "Core/Log.hpp"

namespace Acroy
{
    class Entity
    {
    public:
        Entity(entt::entity id, Scene* scene);
        Entity(const Entity& other) = default;

        template <typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            ACROY_CORE_ASSERT(!HasComponent<T>(), "Entity alerady has coponent");
            return m_scene->m_registry.template emplace<T>(m_id, std::forward<Args>(args)...);
        }

        template <typename T>
        void RemoveComponent()
        {
            ACROY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
            m_scene->m_registry.template remove<T>(m_id);
        }

        template <typename T>
        T& GetComponent()
        {
            ACROY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
            return m_scene->m_registry.template get<T>(m_id);
        }

        template <typename T>
        bool HasComponent() const
        {
            return m_scene->m_registry.template all_of<T>(m_id);
        }

        operator bool() const { return m_id != entt::null; }

    private:
        entt::entity m_id{entt::null};
        Scene* m_scene = nullptr;
    };
}
