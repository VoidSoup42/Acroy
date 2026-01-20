#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Acroy
{
    class Shader
    {
    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Shader();

        void Bind() const;
        void UnBind() const;

        void SetUniformMat4(const char* name, const glm::mat4& value) const;
        void SetUniformInt(const char* name, int value) const;
        void SetUniformFloat(const char* name, float value) const;
        void SetUniformVec4(const char* name, const glm::vec4& value) const;
        inline uint32_t GetId() const { return _id; }

    private:
        uint32_t _id = 0;
    };
}