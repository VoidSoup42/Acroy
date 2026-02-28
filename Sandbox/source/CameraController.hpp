#pragma once

#include <Scene/Entity.hpp>
#include <glm/glm.hpp>

class CameraController
{
public:
    CameraController(Acroy::Entity cameraEntity, float moveSpeed = 3.0f, float sensitivity = 0.1f);

    void OnUpdate(Acroy::Timestep ts);

    void Activate();
    void Deactivate();
    bool IsActive() const { return m_active; }

    void SetSpeed(float speed) { m_moveSpeed = speed; }
    void SetSensitivity(float sensitivity) { m_mouseSensitivity = sensitivity; }
    void SetSmoothTime(float smoothTime) { m_smoothTime = smoothTime; }
    float GetSmoothTime() const { return m_smoothTime; }

    inline glm::vec3& GetPosition() { return m_position; }
    inline glm::vec2  GetRotation() const { return { m_pitch, m_yaw }; }

private:
    void UpdateMouse();
    void UpdateVectors();
    void RebuildTransform();

private:
    Acroy::Entity m_cameraEntity;

    bool m_active = false;

    float m_moveSpeed        = 3.0f;
    float m_mouseSensitivity = 0.1f;
    float m_smoothTime       = 0.1f;

    float m_yaw   = 270.0f;
    float m_pitch = 0.0f;

    bool      m_firstMouse = true;
    glm::vec2 m_lastMousePos { 0.0f };

    glm::vec3 m_position { 0.0f, 1.0f, 3.0f };
    glm::vec3 m_velocity { 0.0f };

    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;

    const glm::vec3 m_worldUp { 0.0f, 1.0f, 0.0f };
};