#pragma once

#include <glm/glm.hpp>
#include "Renderer/Shader.hpp"
#include "Renderer/Camera.hpp"
#include "VertexArray.hpp"
#include "Mesh.hpp"

namespace Acroy
{
    class Renderer
    {
    public:
        static void Init();
        static void SetClearColor(const glm::vec4& color);
        static void Clear();
        static void BeginScene(const Camera& cam);
        static void EndScene();

        static void Submit(const Ref<VertexArray>& vertexArray, Ref<Shader>& shader, const glm::mat4& transform);
        static void Submit(const Ref<Mesh>& mesh, Ref<Shader>& shader, const glm::mat4& transform);

    private:
        static Camera s_camera;
    };
}
