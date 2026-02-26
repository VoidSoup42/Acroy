#include "AcroyPCH.hpp"
#include "Scene.hpp"
#include "Entity.hpp"
#include "Core/Log.hpp"
#include "Renderer/Renderer.hpp"
#include "Components.hpp"

namespace Acroy
{
    Scene::Scene(const Ref<Camera>& cam) : m_camera(cam) {}

    Entity Scene::Create(const std::string& name)
    {
        Entity entity = { m_registry.create(), this };

        TagComponent& tag = entity.AddComponent<TagComponent>();
        tag = name.empty() ? "Object" : name;

        entity.AddComponent<TransformComponent>();
        return entity;
    }

    void Scene::OnUpdate(Timestep ts)
    {
        auto view = m_registry.group<TransformComponent, MeshComponent, ShaderComponent>();

        Renderer::BeginScene(m_camera);

        for (auto entity : view)
        {
            auto [transform, mesh, shader] = view.get<TransformComponent, MeshComponent, ShaderComponent>(entity);

            if (m_registry.any_of<TextureComponent>(entity)) {
                auto& texture = m_registry.get<TextureComponent>(entity);
                texture.texture->Bind(0);
                shader.shader->SetUniformFloat("u_textureScale", texture.textureScale);
            }
            
            Renderer::Submit(mesh, shader, transform);
        }

        Renderer::EndScene();
    }
}
