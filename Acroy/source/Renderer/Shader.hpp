#pragma once

#include "Core/Core.hpp"
#include <string>
#include <glm/glm.hpp>

namespace Acroy
{
    class Shader
    {
    public:
        static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);

        virtual ~Shader() {};

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
    };
}
