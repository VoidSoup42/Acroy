#pragma once

#include "Renderer/Buffer.hpp"

namespace Acroy
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        void Bind() const override;
        void UnBind() const override;
        
    private:
        uint32_t m_rendererId;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        inline uint32_t GetCount() const override { return m_indicesCount; }

        void Bind() const override;
        void UnBind() const override;
        
    private:
        uint32_t m_rendererId;
        uint32_t m_indicesCount;
    };
}
