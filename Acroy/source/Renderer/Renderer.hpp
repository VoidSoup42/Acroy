#pragma once

#include <glm/glm.hpp>
#include "Renderer/RendererAPI.hpp"
#include "Renderer/RenderCommand.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Camera.hpp"

namespace Acroy
{
    class Renderer
    {
    public:
        inline static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI();}

        static void BeginScene(const Camera& cam);
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const Shader& shader);

    private:
        static Camera s_camera;
    };
}
