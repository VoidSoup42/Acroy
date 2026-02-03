#include "Renderer/RenderCommand.hpp"
#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Acroy
{
    RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI();
}