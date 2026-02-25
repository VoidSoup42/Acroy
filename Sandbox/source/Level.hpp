#pragma once

#include <Renderer/Texture.hpp>
#include <Renderer/Shader.hpp>
#include <Renderer/VertexArray.hpp>
#include <Renderer/Buffer.hpp>
#include <Core/Timestep.hpp>

class Level
{
public:
    void Load();
    void Update(Acroy::Timestep timestep);

private:
    Acroy::Ref<Acroy::Shader> m_shader;

    Acroy::Ref<Acroy::VertexArray> m_groundVertexArray;
    Acroy::Ref<Acroy::Texture2D> m_groundTexture;
    glm::mat4 m_groundTransform{1.0f};

    Acroy::Ref<Acroy::VertexArray> m_cubeVertexArray;
    Acroy::Ref<Acroy::Texture2D> m_cubeTexture;
    glm::mat4 m_cubeTransform{1.0f};
};