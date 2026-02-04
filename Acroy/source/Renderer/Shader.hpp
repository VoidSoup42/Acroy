#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Acroy
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void UnBind() const;

        void SetUniformMat4(const char* name, const glm::mat4& matrix) const;

    private:
        uint32_t m_rendererId = 0;
    };
}
