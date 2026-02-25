#pragma once

#include <Renderer/Camera.hpp>
#include <Core/Input.hpp>
#include <Core/Timestep.hpp>
#include <glm/glm.hpp>

class CameraController
{
public:
    CameraController(Acroy::Camera* camera, float moveSpeed, float sensitivity, const glm::vec3& startPos);

    void SetActive(bool enabled);
    bool IsActive() const;

    void OnUpdate(Acroy::Timestep ts);
    void SetPosition(const glm::vec3& pos);

private:
    void UpdateCamera();

private:
    Acroy::Camera* m_camera;

    glm::vec3 m_position;
    glm::vec2 m_rotation;
    glm::vec3 m_velocity;

    float m_moveSpeed;
    float m_sensitivity;
    float m_smoothTime;

    bool   m_active;
    bool   m_firstMouse;
    double m_lastX;
    double m_lastY;
};