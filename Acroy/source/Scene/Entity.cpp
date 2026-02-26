#include "Entity.hpp"

namespace Acroy
{
    Entity::Entity(entt::entity id, Scene* scene) : m_id(id), m_scene(scene) {}
}
