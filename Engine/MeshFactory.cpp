#include "MeshFactory.hpp"
#include <glm/gtc/constants.hpp>

namespace Acroy {

    std::shared_ptr<Mesh> MeshFactory::CreateQuad(glm::vec2 size)
    {
        float halfW = size.x * 0.5f;
        float halfH = size.y * 0.5f;

        std::vector<Vertex> vertices = {
            //       Position                Normal                 Color             TexCoord
            {{ -halfW, -halfH, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
            {{  halfW, -halfH, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
            {{  halfW,  halfH, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
            {{ -halfW,  halfH, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } }
        };

        std::vector<uint32_t> indices = {
            0, 1, 2,
            2, 3, 0
        };

        return std::make_shared<Mesh>(vertices, indices);
    }

    std::shared_ptr<Mesh> MeshFactory::CreateCube(glm::vec3 size)
    {
        glm::vec3 h = size * 0.5f;

        constexpr glm::vec3 frontColor  = {1, 0, 0}; // +Z
        constexpr glm::vec3 backColor   = {0, 1, 0}; // -Z
        constexpr glm::vec3 leftColor   = {0, 0, 1}; // -X
        constexpr glm::vec3 rightColor  = {1, 1, 0}; // +X
        constexpr glm::vec3 topColor    = {0, 1, 1}; // +Y
        constexpr glm::vec3 bottomColor = {1, 0, 1}; // -Y

        std::vector<Vertex> vertices = {
            // Front (+Z)
            {{-h.x, -h.y,  h.z}, {0, 0, 1}, frontColor,  {0,0}},
            {{ h.x, -h.y,  h.z}, {0, 0, 1}, frontColor,  {1,0}},
            {{ h.x,  h.y,  h.z}, {0, 0, 1}, frontColor,  {1,1}},
            {{-h.x,  h.y,  h.z}, {0, 0, 1}, frontColor,  {0,1}},

            // Back (-Z)
            {{ h.x, -h.y, -h.z}, {0, 0,-1}, backColor,   {0,0}},
            {{-h.x, -h.y, -h.z}, {0, 0,-1}, backColor,   {1,0}},
            {{-h.x,  h.y, -h.z}, {0, 0,-1}, backColor,   {1,1}},
            {{ h.x,  h.y, -h.z}, {0, 0,-1}, backColor,   {0,1}},

            // Left (-X)
            {{-h.x, -h.y, -h.z}, {-1,0,0}, leftColor,   {0,0}},
            {{-h.x, -h.y,  h.z}, {-1,0,0}, leftColor,   {1,0}},
            {{-h.x,  h.y,  h.z}, {-1,0,0}, leftColor,   {1,1}},
            {{-h.x,  h.y, -h.z}, {-1,0,0}, leftColor,   {0,1}},

            // Right (+X)
            {{ h.x, -h.y,  h.z}, {1,0,0}, rightColor,  {0,0}},
            {{ h.x, -h.y, -h.z}, {1,0,0}, rightColor,  {1,0}},
            {{ h.x,  h.y, -h.z}, {1,0,0}, rightColor,  {1,1}},
            {{ h.x,  h.y,  h.z}, {1,0,0}, rightColor,  {0,1}},

            // Top (+Y)
            {{-h.x,  h.y,  h.z}, {0,1,0}, topColor,    {0,0}},
            {{ h.x,  h.y,  h.z}, {0,1,0}, topColor,    {1,0}},
            {{ h.x,  h.y, -h.z}, {0,1,0}, topColor,    {1,1}},
            {{-h.x,  h.y, -h.z}, {0,1,0}, topColor,    {0,1}},

            // Bottom (-Y)
            {{-h.x, -h.y, -h.z}, {0,-1,0}, bottomColor,{0,0}},
            {{ h.x, -h.y, -h.z}, {0,-1,0}, bottomColor,{1,0}},
            {{ h.x, -h.y,  h.z}, {0,-1,0}, bottomColor,{1,1}},
            {{-h.x, -h.y,  h.z}, {0,-1,0}, bottomColor,{0,1}},
        };

        std::vector<uint32_t> indices;
        indices.reserve(36);

        for (uint32_t i = 0; i < 24; i += 4)
        {
            indices.insert(indices.end(), {
                i, i+1, i+2,
                i+2, i+3, i
            });
        }

        return std::make_shared<Mesh>(vertices, indices);
    }

    std::shared_ptr<Mesh> MeshFactory::CreateSphere(float radius, uint32_t segments)
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        for (uint32_t y = 0; y <= segments; y++) {
            float v = (float)y / segments;
            float phi = v * glm::pi<float>();

            for (uint32_t x = 0; x <= segments; x++) {
                float u = (float)x / segments;
                float theta = u * glm::two_pi<float>();

                glm::vec3 normal = {
                    glm::sin(phi) * glm::cos(theta),
                    glm::cos(phi),
                    glm::sin(phi) * glm::sin(theta)
                };

                glm::vec3 color = normal * 0.5f + 0.5f;

                vertices.push_back({
                    normal * radius,
                    glm::normalize(normal),
                    color,
                    {u, 1.0f - v}
                });
            }
        }

        for (uint32_t y = 0; y < segments; y++) {
            for (uint32_t x = 0; x < segments; x++) {
                
                uint32_t i0 = y * (segments + 1) + x;
                uint32_t i1 = i0 + segments + 1;

                indices.insert(indices.end(), {
                    i0,     i1,     i0 + 1,
                    i0 + 1, i1,     i1 + 1
                });
            }
        }

        return std::make_shared<Mesh>(vertices, indices);
    }
}
