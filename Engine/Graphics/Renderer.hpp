#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Shader.hpp"
#include "Texture.hpp"

namespace Acroy {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textureCoordinate;
	};

	class Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices,
		     const std::vector<uint32_t>& indices);
		~Mesh();

		uint32_t GetVertexArray()  const { return _vertexArray;  }
		uint32_t GetIndicesCount() const { return _indicesCount; }

	private:
		uint32_t _vertexArray  = 0;
		uint32_t _vertexBuffer = 0;
		uint32_t _indexBuffer  = 0;
		uint32_t _indicesCount = 0;
	};

	struct Material
	{
		std::unique_ptr<Shader>  shader;
		std::unique_ptr<Texture> diffuseTexture;
		glm::vec3 diffuseColor{1.0f};
	};

	struct RenderObject
	{
		std::unique_ptr<Mesh>     mesh;
		std::unique_ptr<Material> material;
	};

	class Renderer
	{
	public:
		void SubmitObject(std::unique_ptr<RenderObject> object);
		void Draw() const;

	private:
		std::vector<std::unique_ptr<RenderObject>> _objects;
	};

}
