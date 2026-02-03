#pragma once

#include <glm/glm.hpp>
#include "Renderer/RendererAPI.hpp"
#include "Renderer/RenderCommand.hpp"

namespace Acroy
{
    class Renderer
    {
    public:
        inline static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI();}

        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
    };
}
