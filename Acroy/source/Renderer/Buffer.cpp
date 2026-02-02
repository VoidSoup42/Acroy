#include "AcroyPCH.hpp"
#include "Renderer/Buffer.hpp"
#include "Platform/OpenGL/OpenGLBuffer.hpp"
#include "Renderer/Renderer.hpp"
#include "Core/Log.hpp"

namespace Acroy
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPI::None:   ACROY_CORE_ASSERT(false, "RendererAPI::None currently not supported");
            case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }

        ACROY_CORE_ASSERT(false, "Unknown API");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPI::None:   ACROY_CORE_ASSERT(false, "RendererAPI::None currently not supported");
            case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
        }

        ACROY_CORE_ASSERT(false, "Unknown API");
        return nullptr;
    }
}
