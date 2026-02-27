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
        Ref<Camera> cam;
        glm::mat4* camTransform = nullptr;

        auto camView = m_registry.view<TransformComponent, CameraComponent>();
        for (auto entity : camView)
        {
            auto [transform, camera] = camView.get<TransformComponent, CameraComponent>(entity);

            if (camera.primary)
            {
                cam = camera.camera;
                camTransform = &transform.transform;
                break;
            }
        }

        if (!cam)
        {
            ACROY_CORE_INFO("No Primary Camera in Scene");
            return;
        }


        auto view = m_registry.group<TransformComponent, MeshComponent, ShaderComponent>();

        Renderer::BeginScene({ cam->GetProjection(), glm::inverse(*camTransform) });

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

    void Scene::OnWindowResize(float width, float height)
    {
		auto view = m_registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
            cameraComponent.camera->Resize(width, height);
		}
    }
}
