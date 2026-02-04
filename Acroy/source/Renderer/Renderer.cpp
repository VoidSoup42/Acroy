#include "Renderer/Renderer.hpp"

namespace Acroy
{
    Camera Renderer::s_camera;

    int nothing = 0;

    void Renderer::BeginScene(const Camera& camera)
    {
        s_camera = camera;
    }
    
    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const Shader& shader)
    {      
        shader.Bind();
        shader.SetUniformMat4("u_view", s_camera.GetView());
        shader.SetUniformMat4("u_proj", s_camera.GetProjection());
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}