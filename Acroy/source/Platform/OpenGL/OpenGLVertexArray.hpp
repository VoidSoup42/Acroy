#pragma once

#include "Renderer/VertexArray.hpp"

namespace Acroy
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer) override;

        void Bind() const override;
        void UnBind() const override;

        inline const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const override { return m_vertexBuffers; }
		inline const std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return m_indexBuffer; }

    private:
        uint32_t m_rendererId = 0;
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
    };
    
}
