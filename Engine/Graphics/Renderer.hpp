#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <list>
#include <memory>

#include "Shader.hpp"

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
		Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
		~Mesh();

		inline uint32_t& GetVertexArray()  { return _vertexArray;  }
		inline uint32_t& GetIndicesCount() { return _indicesCount; }

	private:
		uint32_t _vertexArray;
		uint32_t _vertexBuffer;
		uint32_t _indexBuffer;
		uint32_t _indicesCount;
	};

	class Renderer
	{
	public:
		// Renderer();
		// ~Renderer();

		void SubmitMesh(Mesh& mesh);
		void Draw(Shader& shader) const;


	private:
		std::list<std::unique_ptr<Mesh>> _meshes;
	};
}
