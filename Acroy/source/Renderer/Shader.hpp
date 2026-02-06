#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Acroy
{
    class Shader
    {
    public:
        static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);

        virtual ~Shader() {};

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
    };
}
