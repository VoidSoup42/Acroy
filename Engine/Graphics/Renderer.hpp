#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Shader.hpp"
#include "Texture.hpp"
#include "../Camera.hpp"

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

    class RenderObject {
    public:
        std::shared_ptr<Mesh>     mesh;
        std::shared_ptr<Material> material;
        glm::mat4 transform{1.0};

        void Translate(const glm::vec3& pos);
        void Rotate(const glm::vec3& eulerAngles);
        void Scale(const glm::vec3& scale);
    };

    class Renderer {
    public:
        void SubmitObject(const RenderObject& object);
        void Draw(const Camera& camera) const;
        void Clear();

    private:
        std::vector<RenderObject> _objects;
    };
}
