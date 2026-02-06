#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Renderer/VertexArray.hpp"

namespace Acroy
{
    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0, OpenGL = 1
        };

        inline static API GetAPI() { return s_rendererAPI; }

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

    private:
        static API s_rendererAPI;
    };
}