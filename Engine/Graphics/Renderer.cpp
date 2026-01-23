#include "Renderer.hpp"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

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

        // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

        // Normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        // Color
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

        // textureCoordinate
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinate));

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

    void RenderObject::Translate(const glm::vec3& pos)
    {
        transform = glm::translate(transform, pos);
    }

    void RenderObject::Rotate(const glm::vec3& eulerAngles)
    {
        transform = glm::rotate(transform, eulerAngles.x, glm::vec3(1, 0, 0));
        transform = glm::rotate(transform, eulerAngles.y, glm::vec3(0, 1, 0));
        transform = glm::rotate(transform, eulerAngles.z, glm::vec3(0, 0, 1));
    }

    void RenderObject::Scale(const glm::vec3& scale)
    {
        transform = glm::scale(transform, scale);
    }

    void Renderer::Draw(const Camera& camera) const
	{
        for (const auto& object : _objects)
		{
            if (!object.mesh || !object.material) continue;

            auto& shader = object.material->shader;
            shader->Bind();

            shader->SetUniformMat4("u_model", object.transform);
            shader->SetUniformMat4("u_view", camera.GetViewMatrix());
            shader->SetUniformMat4("u_projection", camera.GetProjectionMatrix());

            if (object.material->diffuseTexture)
			{
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, object.material->diffuseTexture->GetID());
                shader->SetUniformInt("u_texture", 0);
            }

            glBindVertexArray(object.mesh->GetVertexArray());
            glDrawElements(GL_TRIANGLES, object.mesh->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }
        glBindVertexArray(0);
    }
}
