#include "AcroyPCH.hpp"
#include "Renderer/Shader.hpp"
#include "Core/Log.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Acroy
{
    Shader::Shader(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const char* source = vertexSrc.c_str();
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

        source = fragmentSrc.c_str();
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

    Shader::~Shader()
    {
        glDeleteProgram(m_rendererId);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_rendererId);
    }

    void Shader::UnBind() const
    {
        glUseProgram(0);
    }

    void Shader::SetUniformMat4(const char* name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_rendererId, name), 1, false, glm::value_ptr(matrix));
    }
}
