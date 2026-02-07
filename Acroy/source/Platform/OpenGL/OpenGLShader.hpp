#pragma once

#include "Renderer/Shader.hpp"

namespace Acroy
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        void SetUniformInt(const char* name, const int value) const;
        void SetUniformFloat(const char* name, const float value) const;
        void SetUniformFloat2(const char* name, const glm::vec2& value) const;
        void SetUniformFloat3(const char* name, const glm::vec2& value) const;
        void SetUniformFloat4(const char* name, const glm::vec2& value) const;
        void SetUniformMat3(const char* name, const glm::mat3& matrix) const;
        void SetUniformMat4(const char* name, const glm::mat4& matrix) const;
    
    private:
        uint32_t m_rendererId;
    };
}
