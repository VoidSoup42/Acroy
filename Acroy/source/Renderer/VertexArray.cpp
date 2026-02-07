#include "Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Acroy
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPI::API::None:   ACROY_CORE_ASSERT(false, "RendererAPI::None currently not supported");
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
        }

        ACROY_CORE_ASSERT(false, "Invalid Renderer API");
        return nullptr;
    }
}
