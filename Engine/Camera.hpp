#pragma once

#include <glm/glm.hpp>

namespace Acroy
{
    class Camera
    {
    public:
        Camera(float fov = 60.0, float aspectRatio = 1.0, float zNear = 0.1, float zFar = 100.0);

        void SetFOV(float fov);
        const float GetFOV() const { return _fov; }

        void SetAspectRatio(float aspect);
        const float GetAspectRatio() const { return _aspect; }

        const glm::mat4& GetProjectionMatrix() const { return _projectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return _viewMatrix; }

        void SetPosition(const glm::vec3& pos) { _position = pos; RecalculateView(); }
        void SetRotation(const glm::vec3& rot) { _rotation = rot; RecalculateView(); }
        // rotation: x = pitch, y = yaw, z = roll

    private:
        void RecalculateProjection();
        void RecalculateView();

        glm::mat4 _projectionMatrix {1.0};
        glm::mat4 _viewMatrix {1.0};
        glm::vec3 _position;
        glm::vec3 _rotation;

        float _fov;
        float _aspect;
        float _zNear;
        float _zFar;
    };
}
