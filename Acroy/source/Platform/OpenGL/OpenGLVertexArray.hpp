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
        void AddIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer) override;

        void Bind() const override;
        void UnBind() const override;

    private:
        uint32_t m_rendererId = 0;
    };
    
}
