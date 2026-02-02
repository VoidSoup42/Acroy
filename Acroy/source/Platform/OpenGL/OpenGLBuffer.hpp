#pragma once

#include "Renderer/Buffer.hpp"

namespace Acroy
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        inline void SetLayout(BufferLayout& layout) override { m_layout = layout; }
        inline const BufferLayout& GetLayout() const override { return m_layout; }

        void Bind() const override;
        void UnBind() const override;
        
    private:
        uint32_t m_rendererId;
        BufferLayout m_layout;
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
