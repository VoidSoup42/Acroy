#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Acroy
{
    class Camera
    {
    public:
        Camera(const glm::mat4& proj) : m_projection(proj) {}
        Camera(const Camera& other) = default;
        Camera() = default;
        virtual ~Camera() = default;

        const glm::mat4& GetProjection() const { return m_projection; }

        virtual void Resize(float width, float height) {}
    
    protected:
        glm::mat4 m_projection { 1.0f };
    };
}