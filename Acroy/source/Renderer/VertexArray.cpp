#include "Renderer/Renderer.hpp"
#include <glad/glad.h>

namespace Acroy
{
    static GLenum ShaderDataTypeToGLType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;

            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;

            case ShaderDataType::Bool:
                return GL_BOOL;
        }

        ACROY_CORE_ASSERT(false, "Unknown Shader Data Type");
        return 0;
    }

    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_rendererID);
    }

    void VertexArray::AddVertexBuffer(Ref<VertexBuffer>& vertexBuffer)
    {
        ACROY_CORE_ASSERT(vertexBuffer->GetLayout().GetAttributes().size(), "Vertex Buffer has no layout");

        m_vertexBuffers.push_back(vertexBuffer);
        glBindVertexArray(m_rendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        for (const VertexAttribute& attrib : vertexBuffer->GetLayout())
        {
            glVertexAttribPointer(index, attrib.GetComponentCount(), ShaderDataTypeToGLType(attrib.type), attrib.normalized, vertexBuffer->GetLayout().GetStride(), reinterpret_cast<const void*>(attrib.offset));
            glEnableVertexAttribArray(index);
            index++;
        }

        vertexBuffer->UnBind();
        glBindVertexArray(0);
    }

    void VertexArray::SetIndexBuffer(Ref<IndexBuffer>& indexBuffer)
    {
        m_indexBuffer = indexBuffer;
        glBindVertexArray(m_rendererID);
        indexBuffer->Bind();
        glBindVertexArray(0);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_rendererID);
    }

    void VertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_rendererID);
    }

}
