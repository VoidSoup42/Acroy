#include "Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp" // Temp

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

    void Renderer::Submit(const Ref<VertexArray>& vertexArray, Ref<Shader>& shader)
    {      
        shader->Bind();
        // shader.SetUniformMat4("u_view", s_camera.GetView());
        // shader.SetUniformMat4("u_proj", s_camera.GetProjection());

        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_view", s_camera.GetView());
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_proj", s_camera.GetProjection());

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}