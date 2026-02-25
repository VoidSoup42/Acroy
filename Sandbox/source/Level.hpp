#pragma once

#include <Renderer/Texture.hpp>
#include <Renderer/Shader.hpp>
#include <Renderer/VertexArray.hpp>
#include <Renderer/Buffer.hpp>
#include <Core/Timestep.hpp>
#include <Renderer/Mesh.hpp>

class Level
{
public:
    void Load();
    void Update(Acroy::Timestep timestep);

private:
    Acroy::Ref<Acroy::Shader> m_shader;

    Acroy::Ref<Acroy::Mesh> m_groundMesh;
    Acroy::Ref<Acroy::Texture2D> m_groundTexture;
    glm::mat4 m_groundTransform{1.0f};

    Acroy::Ref<Acroy::Mesh> m_cubeMesh;
    Acroy::Ref<Acroy::Texture2D> m_cubeTexture;
    glm::mat4 m_cubeTransform{1.0f};
};