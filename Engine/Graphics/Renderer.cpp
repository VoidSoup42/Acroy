#include "Renderer.hpp"

#include <GL/glew.h>
#include <cstddef>

namespace Acroy {

	Mesh::Mesh(const std::vector<Vertex>& vertices,
	           const std::vector<uint32_t>& indices)
		: _indicesCount(static_cast<uint32_t>(indices.size()))
	{
		glGenVertexArrays(1, &_vertexArray);
		glBindVertexArray(_vertexArray);

		glGenBuffers(1, &_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

		// position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

		// normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

		// texcoord
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, textureCoordinate)));

		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		if (_indexBuffer)
			glDeleteBuffers(1, &_indexBuffer);
		if (_vertexBuffer)
			glDeleteBuffers(1, &_vertexBuffer);
		if (_vertexArray)
			glDeleteVertexArrays(1, &_vertexArray);
	}

	void Renderer::SubmitObject(std::unique_ptr<RenderObject> object)
	{
		_objects.push_back(std::move(object));
	}

	void Renderer::Draw() const
	{
		for (const auto& object : _objects)
		{
			const auto& material = object->material;
			const auto& mesh     = object->mesh;

			material->shader->Bind();

			if (material->diffuseTexture)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(
					GL_TEXTURE_2D,
					material->diffuseTexture->GetID()
				);
				material->shader->SetUniformInt("u_texture", 0);
			}

			glBindVertexArray(mesh->GetVertexArray());
			glDrawElements(
				GL_TRIANGLES,
				mesh->GetIndicesCount(),
				GL_UNSIGNED_INT,
				nullptr
			);
		}

		glBindVertexArray(0);
	}

}
