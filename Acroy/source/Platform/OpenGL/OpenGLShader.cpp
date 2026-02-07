#include "AcroyPCH.hpp"
#include "Core/Log.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace Acroy
{
    OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
    {
        uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const char* source = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);

            ACROY_CORE_ERROR("Failed to compile vertex shader");
            ACROY_CORE_ERROR(infoLog.data());

            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            ACROY_CORE_ERROR("Failed to compile fragment shader");
            ACROY_CORE_ERROR(infoLog.data());

            return;
        }

        m_rendererId = glCreateProgram();

        glAttachShader(m_rendererId, vertexShader);
        glAttachShader(m_rendererId, fragmentShader);

        glLinkProgram(m_rendererId);

        GLint isLinked = 0;
        glGetProgramiv(m_rendererId, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_rendererId, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_rendererId, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(m_rendererId);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            ACROY_CORE_ERROR("Failed to link shader program");
            ACROY_CORE_ERROR(infoLog.data());

            return;
        }

        glDetachShader(m_rendererId, vertexShader);
        glDetachShader(m_rendererId, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteShader(m_rendererId);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_rendererId);
    }

    void OpenGLShader::UnBind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetUniformInt(const char* name, const int value) const
    {
        glUniform1i(glGetUniformLocation(m_rendererId, name), value);
    }

    void OpenGLShader::SetUniformFloat(const char* name, const float value) const
    {
        glUniform1f(glGetUniformLocation(m_rendererId, name), value);
    }

    void OpenGLShader::SetUniformFloat2(const char* name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(m_rendererId, name), 1, glm::value_ptr(value));
    }

    void OpenGLShader::SetUniformFloat3(const char* name, const glm::vec2& value) const
    {
        glUniform3fv(glGetUniformLocation(m_rendererId, name), 1, glm::value_ptr(value));
    }

    void OpenGLShader::SetUniformFloat4(const char* name, const glm::vec2& value) const
    {
        glUniform4fv(glGetUniformLocation(m_rendererId, name), 1, glm::value_ptr(value));
    }

    void OpenGLShader::SetUniformMat3(const char* name, const glm::mat3& matrix) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_rendererId, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::SetUniformMat4(const char* name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_rendererId, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

}