#include "AcroyPCH.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Texture.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

namespace Acroy
{
    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPI::API::None:   ACROY_CORE_ASSERT(false, "RendererAPI::None currently not supported");
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
        }

        ACROY_CORE_ASSERT(false, "Unknown API");
        return nullptr;
    }
}