#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Shader.hpp"
#include "Texture.hpp"

namespace Acroy {

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 textureCoordinate;
    };

    class Mesh {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        uint32_t GetVertexArray()  const { return _vertexArray;  }
        uint32_t GetIndicesCount() const { return _indicesCount; }

    private:
        uint32_t _vertexArray  = 0;
        uint32_t _vertexBuffer = 0;
        uint32_t _indexBuffer  = 0;
        uint32_t _indicesCount = 0;
    };

    struct Material {
        std::shared_ptr<Shader>  shader;
        std::shared_ptr<Texture> diffuseTexture;
        glm::vec3 diffuseColor{1.0f};
    };

    struct RenderObject {
        std::shared_ptr<Mesh>     mesh;
        std::shared_ptr<Material> material;
    };

    class Renderer {
    public:
        void SubmitObject(const RenderObject& object);
        void Draw() const;
        void Clear();

    private:
        std::vector<RenderObject> _objects;
    };
}
