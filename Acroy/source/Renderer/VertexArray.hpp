#pragma once

#include "Core/Core.hpp"
#include "Renderer/Buffer.hpp"

namespace Acroy
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void AddVertexBuffer(Ref<VertexBuffer>& vertexBuffer);
        void SetIndexBuffer(Ref<IndexBuffer>& indexBuffer);

        void Bind() const;
        void UnBind() const;

        inline const std::vector<Ref<VertexBuffer>> GetVertexBuffers() const { return m_vertexBuffers; }
		inline const Ref<IndexBuffer> GetIndexBuffer() const { return m_indexBuffer; }

    private:
        uint32_t m_rendererID = 0;
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
    }; 
}
