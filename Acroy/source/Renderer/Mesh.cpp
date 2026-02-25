#include "Mesh.hpp"

namespace Acroy
{
    Mesh::Mesh(void* vertexData, uint32_t vertexSize, uint32_t* indexData, uint32_t indexCount, const BufferLayout& layout)
    {
        m_vertexArray  = CreateRef<VertexArray>();
        m_vertexBuffer = CreateRef<VertexBuffer>(vertexData, vertexSize);
        m_indexBuffer  = CreateRef<IndexBuffer>(indexData, indexCount);

        m_vertexBuffer->SetLayout(layout);
        m_vertexArray->AddVertexBuffer(m_vertexBuffer);
        m_vertexArray->SetIndexBuffer(m_indexBuffer);
    }
}
