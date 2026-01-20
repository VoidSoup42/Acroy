#include "Renderer.hpp"
#include <GL/glew.h>
#include <print>

namespace Acroy {
    
    Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) : _indicesCount(indices.size())
    {
        glGenVertexArrays(1, &_vertexArray);
        glBindVertexArray(_vertexArray);

        glGenBuffers(1, &_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)offsetof(Vertex, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)offsetof(Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)offsetof(Vertex, textureCoordinate));

        glGenBuffers(1, &_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &_vertexArray);
        glDeleteBuffers(1, &_vertexBuffer);
        glDeleteBuffers(1, &_indexBuffer);
    }

    void Renderer::SubmitMesh(Mesh& mesh)
    {
        _meshes.push_back(std::make_unique<Mesh>(mesh));
    }

    void Renderer::Draw(Shader& shader) const
    {
        // clear the screen, color buffer, and depth buffer
        // use the shader
        shader.Bind();
        // setup view matrices
        // setup shader uniforms
        for (const auto& mesh : _meshes)
        {
            glBindVertexArray(mesh->GetVertexArray());
            glDrawElements(GL_TRIANGLES, mesh->GetIndicesCount(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
}
