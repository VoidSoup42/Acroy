#pragma once

#include "Camera.hpp"

namespace Acroy
{
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera() = default;
        PerspectiveCamera(float fov, float aspect, float zNear, float zFar)
        : m_fov(fov)
        , m_aspect(aspect)
        , m_zNear(zNear)
        , m_zFar(zFar)
        {
            RecalculateProjection();
        }

        void SetFOV(float fov)
        {
            m_fov = fov;
            RecalculateProjection();
        }

        void Resize(float width, float height) override
        {
            m_aspect = width / height;
            RecalculateProjection();
        }

        inline float GetFOV() const { return m_fov; }
        inline float GetAspect() const { return m_aspect; }

        inline void SetProjection(const glm::mat4& proj) { m_projection = proj; }

    private:
        float m_aspect = 1.0f;
        float m_fov    = 60.0f;
        float m_zNear  = 0.1f;
        float m_zFar   = 1000.0f;

    private:
        void RecalculateProjection()
        {
            m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_zNear, m_zFar);
        }
    };
}