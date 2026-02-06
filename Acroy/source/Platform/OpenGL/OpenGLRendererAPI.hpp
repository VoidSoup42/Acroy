#pragma once

#include "Core/Core.hpp"
#include "Renderer/RendererAPI.hpp"

namespace Acroy
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;
        void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}
