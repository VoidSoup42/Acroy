#include "AcroyPCH.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Shader.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Acroy
{
    Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPI::API::None:   ACROY_CORE_ASSERT(false, "RendererAPI::None currently not supported");
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
        }

        ACROY_CORE_ASSERT(false, "Unknown API");
        return nullptr;
    }
}
