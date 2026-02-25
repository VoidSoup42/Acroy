#pragma once

#include <vector>

#include "VertexArray.hpp"
#include "Buffer.hpp"

namespace Acroy
{

    class Mesh
    {
    public:
        Mesh(void* vertexData, uint32_t vertexSize, uint32_t* indexData, uint32_t indexCount, const BufferLayout& layout);

        inline Ref<VertexArray> GetVertexArray() const { return m_vertexArray; }

    private:
        Ref<VertexArray> m_vertexArray;
        Ref<VertexBuffer> m_vertexBuffer;
        Ref<IndexBuffer> m_indexBuffer;

        uint32_t m_indicesCount = 0;
    };

}
