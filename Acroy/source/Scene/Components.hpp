#pragma once

#include "Renderer/Mesh.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Camera.hpp"
#include <glm/glm.hpp>

namespace Acroy
{
    struct TagComponent
    {
        std::string tag;

        TagComponent() = default;
        TagComponent(const std::string& tag) : tag(tag) {}
    };

    struct TransformComponent
    {
        glm::mat4 transform {1.0f};
        float somedata = 5;

        TransformComponent() = default;
        TransformComponent(const glm::mat4& transform) : transform(transform) {}

        operator const glm::mat4&() const { return transform; }
    };

    struct MeshComponent
    {
        Ref<Mesh> mesh;

        MeshComponent() = default;
        MeshComponent(const Ref<Mesh> mesh) : mesh(mesh) {}

        operator const Ref<Mesh>&() const { return mesh; }
    };

    struct ShaderComponent
    {
        Ref<Shader> shader;

        ShaderComponent() = default;
        ShaderComponent(const Ref<Shader> shader) : shader(shader) {}

        operator const Ref<Shader>&() const { return shader; }
    };

    struct TextureComponent
    {
        Ref<Texture> texture;
        float textureScale {1.0f};

        TextureComponent() = default;
        TextureComponent(const Ref<Texture> tex) : texture(tex) {}
    };

    struct CameraComponent
    {
        Ref<Camera> camera;
        bool primary;

        CameraComponent() = default;
        CameraComponent(const Ref<Camera> cam, bool primary = true)
        : camera(cam), primary(primary) {}

    };
}
