#include "Renderer.hpp"
#include <GL/glew.h>

namespace Acroy {

    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
        : _indicesCount(static_cast<uint32_t>(indices.size()))
    {
        glGenVertexArrays(1, &_vertexArray);
        glGenBuffers(1, &_vertexBuffer);
        glGenBuffers(1, &_indexBuffer);

        glBindVertexArray(_vertexArray);

        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinate));

        glBindVertexArray(0);
    }

    Mesh::~Mesh()
	{
        glDeleteBuffers(1, &_indexBuffer);
        glDeleteBuffers(1, &_vertexBuffer);
        glDeleteVertexArrays(1, &_vertexArray);
    }

    void Renderer::SubmitObject(const RenderObject& object)
	{
        _objects.push_back(object);
    }

    void Renderer::Clear()
	{
        _objects.clear();
    }

    void Renderer::Draw() const
	{
        for (const auto& object : _objects)
		{
            if (!object.mesh || !object.material) continue;

            object.material->shader->Bind();

            if (object.material->diffuseTexture)
			{
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, object.material->diffuseTexture->GetID());
                object.material->shader->SetUniformInt("u_texture", 0);
            }

            glBindVertexArray(object.mesh->GetVertexArray());
            glDrawElements(GL_TRIANGLES, object.mesh->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }
        glBindVertexArray(0);
    }
}
