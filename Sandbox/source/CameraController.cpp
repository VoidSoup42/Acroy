#include "CameraController.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <cmath>

CameraController::CameraController(Acroy::Camera* camera, float moveSpeed, float sensitivity, const glm::vec3& startPos)
    : m_camera(camera), m_moveSpeed(moveSpeed), m_sensitivity(sensitivity), m_active(false),
      m_position(startPos), m_rotation(0.0f, 270.0f), m_velocity(0.0f),
      m_firstMouse(true), m_lastX(0.0), m_lastY(0.0), m_smoothTime(0.1f)
{
    UpdateCamera();
}

void CameraController::SetActive(bool enabled)
{
    m_active = enabled;
}

bool CameraController::IsActive() const
{
    return m_active;
}

void CameraController::SetPosition(const glm::vec3& pos)
{
    m_position = pos;
    UpdateCamera();
}

void CameraController::OnUpdate(Acroy::Timestep ts)
{
    float dt = ts.GetSeconds();

    if (m_active)
    {
        Acroy::Input::SetMouseMode(Acroy::MouseMode::Disabled);
    }
    else
    {
        Acroy::Input::SetMouseMode(Acroy::MouseMode::Normal);
        m_firstMouse = true;
        return;
    }

    glm::vec2 mousePos = Acroy::Input::GetMousePosition();

    if (m_firstMouse)
    {
        m_lastX = mousePos.x;
        m_lastY = mousePos.y;
        m_firstMouse = false;
        return;
    }

    glm::vec2 delta(mousePos.x - m_lastX, m_lastY - mousePos.y);
    m_lastX = mousePos.x;
    m_lastY = mousePos.y;

    m_rotation.x += delta.y * m_sensitivity;
    m_rotation.y += delta.x * m_sensitivity;
    m_rotation.x = glm::clamp(m_rotation.x, -89.0f, 89.0f);

    float pitch = glm::radians(m_rotation.x);
    float yaw   = glm::radians(m_rotation.y);

    glm::vec3 forward {
        glm::cos(yaw) * glm::cos(pitch),
        glm::sin(pitch),
        glm::sin(yaw) * glm::cos(pitch)
    };
    forward = glm::normalize(forward);

    glm::vec3 right = glm::normalize(glm::cross(forward, {0, 1, 0}));
    glm::vec3 up    = glm::normalize(glm::cross(right, forward));

    glm::vec3 dir{0.0f};
    if (Acroy::Input::IsKeyPressed(87)) dir += forward;  // W
    if (Acroy::Input::IsKeyPressed(83)) dir -= forward;  // S
    if (Acroy::Input::IsKeyPressed(68)) dir += right;    // D
    if (Acroy::Input::IsKeyPressed(65)) dir -= right;    // A
    if (Acroy::Input::IsKeyPressed(69)) dir += up;       // E
    if (Acroy::Input::IsKeyPressed(81)) dir -= up;       // Q

    float speed = m_moveSpeed;
    if (Acroy::Input::IsKeyPressed(341)) speed *= 0.3f;  // Ctrl
    if (Acroy::Input::IsKeyPressed(340)) speed *= 2.0f;  // Shift

    float lerp = 1.0f - std::exp(-dt / m_smoothTime);

    if (glm::length(dir) > 0.0f)
    {
        dir = glm::normalize(dir);
        m_velocity = glm::mix(m_velocity, dir * speed, lerp);
    }
    else
    {
        m_velocity = glm::mix(m_velocity, glm::vec3(0.0f), lerp);
    }

    m_position += m_velocity * dt;

    UpdateCamera();
}

void CameraController::UpdateCamera()
{
    m_camera->SetPosition(m_position);
    m_camera->SetRotation({ m_rotation.x, m_rotation.y, 0.0f });
}