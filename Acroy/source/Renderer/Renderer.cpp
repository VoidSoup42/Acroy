#include "Renderer/Renderer.hpp"
#include <glad/glad.h>

namespace Acroy
{
    RenderCamera Renderer::s_camera;

    void Renderer::Init()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::BeginScene(const RenderCamera& cam)
    {
        s_camera = cam;
    }
    
    void Renderer::EndScene()
    {
        // Pass
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SetViewport(float x, float y, float width, float height)
    {
        glViewport(x, y, width, height);
    }

    void Renderer::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
    {      
        shader->Bind();
        shader->SetUniformMat4("u_model", transform);
        shader->SetUniformMat4("u_view", s_camera.view);
        shader->SetUniformMat4("u_proj", s_camera.proj);

        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::Submit(const Ref<Mesh>& mesh, const Ref<Shader>& shader, const glm::mat4& transform)
    {
        shader->Bind();
        shader->SetUniformMat4("u_model", transform);
        shader->SetUniformMat4("u_view", s_camera.view);
        shader->SetUniformMat4("u_proj", s_camera.proj);

        mesh->GetVertexArray()->Bind();
        glDrawElements(GL_TRIANGLES, mesh->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
}