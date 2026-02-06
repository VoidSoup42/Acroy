#include "AcroyPCH.hpp"
#include "Core/Core.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"
#include <glad/glad.h>

namespace Acroy
{
    static GLenum ShaderDataTypeToGLType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Bool:   return GL_BOOL;
        }

        ACROY_CORE_ASSERT(false, "Unknown Shader Data Type")
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_rendererId);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_rendererId);
    }

    void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer>& vertexBuffer)
    {
        ACROY_CORE_ASSERT(vertexBuffer->GetLayout().GetAttributes().size(), "Vertex Buffer has no layout");

        m_vertexBuffers.push_back(vertexBuffer);
        glBindVertexArray(m_rendererId);
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

    void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer>& indexBuffer)
    {
        m_indexBuffer = indexBuffer;
        glBindVertexArray(m_rendererId);
        indexBuffer->Bind();
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_rendererId);
    }

    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }
}
