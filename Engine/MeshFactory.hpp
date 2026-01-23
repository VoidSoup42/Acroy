#pragma once

#include "Graphics/Renderer.hpp"
#include <glm/glm.hpp>
#include <memory>

namespace Acroy
{
    class MeshFactory
    {
    public:
        static std::shared_ptr<Mesh> CreateQuad(glm::vec2 size);
        static std::shared_ptr<Mesh> CreateCube(glm::vec3 size);
        static std::shared_ptr<Mesh> CreateSphere(float radius, uint32_t segments = 32);
    };
}
