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

        void SetUniformFloat(const char* name, const float& value) const;
        void SetUniformVec2(const char* name, const glm::vec2& value) const;
        void SetUniformVec3(const char* name, const glm::vec2& value) const;
        void SetUniformVec4(const char* name, const glm::vec2& value) const;
        void SetUniformMat3(const char* name, const glm::mat3& matrix) const;
        void SetUniformMat4(const char* name, const glm::mat4& matrix) const;
    
    private:
        uint32_t m_rendererId;
    };
}
