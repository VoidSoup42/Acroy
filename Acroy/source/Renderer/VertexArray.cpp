#include "Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Acroy
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPI::None:   ACROY_CORE_ASSERT(false, "RendererAPI::None currently not supported");
            case RendererAPI::OpenGL: return new OpenGLVertexArray();
        }

        ACROY_CORE_ASSERT(false, "Invalid Renderer API");
        return nullptr;
    }
}
