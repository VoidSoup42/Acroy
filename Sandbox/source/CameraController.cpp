#include "CameraController.hpp"
#include <Scene/Components.hpp>
#include <Core/Input.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

CameraController::CameraController(Acroy::Entity cameraEntity, float moveSpeed, float sensitivity)
: m_cameraEntity(cameraEntity)
, m_moveSpeed(moveSpeed)
, m_mouseSensitivity(sensitivity)
{
    auto& tc = m_cameraEntity.GetComponent<Acroy::TransformComponent>();
    m_position = glm::vec3(tc.transform[3]);

    UpdateVectors();
    RebuildTransform();
}

void CameraController::Activate()
{
    m_active     = true;
    m_firstMouse = true;
    Acroy::Input::SetMouseMode(Acroy::MouseMode::Disabled);
}

void CameraController::Deactivate()
{
    m_active   = false;
    m_velocity = glm::vec3(0.0f);
    Acroy::Input::SetMouseMode(Acroy::MouseMode::Normal);
}

void CameraController::OnUpdate(Acroy::Timestep ts)
{
    if (!m_active) return;
    
    float deltaTime = ts.GetSeconds();

    UpdateMouse();

    glm::vec3 direction(0.0f);

    float speed = m_moveSpeed;
    if (Acroy::Input::IsKeyPressed(341)) speed *= 0.3f;
    if (Acroy::Input::IsKeyPressed(340)) speed *= 2.0f;

    if (Acroy::Input::IsKeyPressed(87)) direction += m_front;
    if (Acroy::Input::IsKeyPressed(83)) direction -= m_front;
    if (Acroy::Input::IsKeyPressed(68)) direction += m_right;
    if (Acroy::Input::IsKeyPressed(65)) direction -= m_right;
    if (Acroy::Input::IsKeyPressed(69)) direction += m_up;
    if (Acroy::Input::IsKeyPressed(81)) direction -= m_up;

    glm::vec3 targetVelocity(0.0f);
    if (glm::length(direction) > 0.0f)
        targetVelocity = glm::normalize(direction) * speed;

    m_velocity = glm::mix(m_velocity, targetVelocity, 1.0f - std::exp(-deltaTime / m_smoothTime));

    m_position += m_velocity * deltaTime;

    RebuildTransform();
}

void CameraController::UpdateMouse()
{
    glm::vec2 mousePos = Acroy::Input::GetMousePosition();

    if (m_firstMouse)
    {
        m_lastMousePos = mousePos;
        m_firstMouse   = false;
        return;
    }

    glm::vec2 delta = mousePos - m_lastMousePos;
    m_lastMousePos  = mousePos;

    m_yaw   += delta.x * m_mouseSensitivity;
    m_pitch += -delta.y * m_mouseSensitivity;
    m_pitch  = glm::clamp(m_pitch, -89.0f, 89.0f);

    UpdateVectors();
}

void CameraController::UpdateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}

void CameraController::RebuildTransform()
{
    glm::mat4 rotation    = glm::inverse(glm::lookAt(glm::vec3(0.0f), m_front, m_up));
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_position);

    auto& tc = m_cameraEntity.GetComponent<Acroy::TransformComponent>();
    tc.transform = translation * rotation;
}
