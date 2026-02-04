#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Acroy
{
    Camera::Camera(float fov, float aspect, float zNear, float zFar)
        : m_fov(fov)
        , m_aspect(aspect)
        , m_zNear(zNear)
        , m_zFar(zFar)
    {
        m_projection = glm::perspective(glm::radians(fov), m_aspect, m_zNear, m_zFar);
        m_view = glm::mat4(1.0f);
    }
}
