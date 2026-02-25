#pragma once

#include "Core/Core.hpp"
#include <string>
#include <glm/glm.hpp>

namespace Acroy
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

        void Bind() const;
        void UnBind() const;

        void SetUniformInt(const char* name, const int value) const;
        void SetUniformFloat(const char* name, const float value) const;
        void SetUniformFloat2(const char* name, const glm::vec2& value) const;
        void SetUniformFloat3(const char* name, const glm::vec3& value) const;
        void SetUniformFloat4(const char* name, const glm::vec4& value) const;
        void SetUniformMat3(const char* name, const glm::mat3& matrix) const;
        void SetUniformMat4(const char* name, const glm::mat4& matrix) const;

    private:
        uint32_t m_rendererId;
    };
}
