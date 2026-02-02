#pragma once

#include "Renderer/Buffer.hpp"

namespace Acroy
{
    class VertexArray
    {
    public:
        static VertexArray* Create();

        virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual void AddIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
    }; 
}
