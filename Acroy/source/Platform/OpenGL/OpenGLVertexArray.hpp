#pragma once

#include "Core/Core.hpp"
#include "Renderer/VertexArray.hpp"

namespace Acroy
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        void AddVertexBuffer(Ref<VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(Ref<IndexBuffer>& indexBuffer) override;

        void Bind() const override;
        void UnBind() const override;

        inline const std::vector<Ref<VertexBuffer>> GetVertexBuffers() const override { return m_vertexBuffers; }
		inline const Ref<IndexBuffer> GetIndexBuffer() const override { return m_indexBuffer; }

    private:
        uint32_t m_rendererId = 0;
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
    };
    
}
