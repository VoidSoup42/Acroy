#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Acroy
{
    class Camera
    {
    public:
        Camera() {};
        Camera(float fov, float aspect, float zNear, float zFar);

        inline void SetFOV(float fov) { m_fov = fov; }
        inline float GetFOV() const { return m_fov; }

        inline void SetProjection(glm::mat4 proj) { m_projection = proj; }
        inline const glm::mat4& GetProjection() const { return m_projection; }

        inline void SetView(const glm::mat4& view) { m_view = view; }
        inline const glm::mat4& GetView() const { return m_view; }

        inline void SetAspect(float aspect) { m_aspect = aspect; }
        inline float GetAspect() const { return m_aspect; }

        void SetPosition(const glm::vec3& position)
        {
            m_position = position;
            RecalculateView();
        }

        void SetRotation(const glm::vec3& eulers)
        {
            m_eulers = eulers;
            RecalculateView();
        }

        inline const glm::vec3& GetPosition() const { return m_position; }
        inline const glm::vec3& GetRotation() const { return m_eulers; }

    private:
        glm::mat4 m_projection { 1.0f };
        glm::mat4 m_view       { 1.0f };

        glm::vec3 m_position   { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_eulers     { 0.0f, 90.0f, 0.0f };

        float m_aspect = 1.0f;
        float m_fov    = 60.0f;
        float m_zNear  = 0.1f;
        float m_zFar   = 1000.0f;

    private:
        void RecalculateView()
        {
            float pitch = glm::radians(m_eulers.x);
            float yaw   = glm::radians(m_eulers.y);

            glm::vec3 forward;
            forward.x = cos(yaw) * cos(pitch);
            forward.y = sin(pitch);
            forward.z = sin(yaw) * cos(pitch);
            forward = glm::normalize(forward);

            const glm::vec3 worldUp { 0.0f, 1.0f, 0.0f };
            
            m_view = glm::lookAt(
                m_position,
                m_position + forward,
                worldUp
            );
        }
    };
}