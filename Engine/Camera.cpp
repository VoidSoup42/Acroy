#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Acroy
{
    Camera::Camera(float fov, float aspectRatio, float zNear, float zFar)
        : _fov(fov)
        , _aspect(aspectRatio)
        , _zNear(zNear)
        , _zFar(zFar) {
        RecalculateProjection();
    }

    void Camera::SetFOV(float fov)
    {
        _fov = fov;
        RecalculateProjection();
    }

    void Camera::SetAspectRatio(float aspect)
    {
        _aspect = aspect;
        RecalculateProjection();
    }

    void Camera::RecalculateProjection()
    {
        _projectionMatrix = glm::perspective(glm::radians(_fov), _aspect, _zNear, _zFar);
    }

    void Camera::RecalculateView()
    {
        glm::mat4 transform(1.0f);

        transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
        transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
        transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));

        transform = glm::translate(transform, _position);
        _viewMatrix = glm::inverse(transform);
    }
}
