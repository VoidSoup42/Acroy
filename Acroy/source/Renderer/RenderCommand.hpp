#pragma once

#include <memory>
#include "Core/Core.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/RendererAPI.hpp"

namespace Acroy
{
    class RenderCommand
    {
    public:
        inline static void Init() {
            s_rendererAPI->Init();
        }

        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
            s_rendererAPI->DrawIndexed(vertexArray);
        }

        inline static void SetClearColor(const glm::vec4& color) {
            s_rendererAPI->SetClearColor(color);
        }

        inline static void Clear() {
            s_rendererAPI->Clear();
        }

    private:
        static RendererAPI* s_rendererAPI;
    };
}