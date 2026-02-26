#pragma once

#include "Core/Core.hpp"
#include "Core/Log.hpp"
#include <cstdint>
#include <vector>

namespace Acroy
{
    enum class ShaderDataType
    {
        Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
    };

    static constexpr uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Bool:   return 4;
        }

        ACROY_CORE_ASSERT(false, "Invalid Shader Data Type");
        return 0;
    }

    struct VertexAttribute
    {
        const char* name;
        ShaderDataType type;
        size_t stride;
        size_t offset;
        bool normalized;

        constexpr uint32_t GetComponentCount() const
        {
            switch (type)
            {
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Mat3:   return 3 * 3;
                case ShaderDataType::Mat4:   return 4 * 4;
                case ShaderDataType::Bool:   return 1;
            }

            return 0;
        }

        VertexAttribute() {}
        VertexAttribute(const char* name, ShaderDataType type, bool normalized = false)
        : name(name), type(type), stride(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {}
    };
    
    class BufferLayout
    {
    public:
        BufferLayout() {}
        BufferLayout(const std::initializer_list<VertexAttribute>& attributes)
        : m_attributes(attributes) { CalculateOffsetAndStride(); }

        inline uint32_t GetStride() const { return m_stride; }
        inline std::vector<VertexAttribute> GetAttributes() const { return m_attributes; }

        inline std::vector<VertexAttribute>::const_iterator begin() const { return m_attributes.begin(); }
        inline std::vector<VertexAttribute>::const_iterator end() const { return m_attributes.end(); }

    private:
        void CalculateOffsetAndStride()
        {
            uint32_t offset = 0;
            for (VertexAttribute& attrib : m_attributes)
            {
                attrib.offset = offset;
                offset += ShaderDataTypeSize(attrib.type);
                m_stride += ShaderDataTypeSize(attrib.type);
            }
        }

        std::vector<VertexAttribute> m_attributes;
        uint32_t m_stride = 0;
    };

    class VertexBuffer
    {
    public:
        ~VertexBuffer();

        VertexBuffer(const void* vertices, uint32_t size);

        inline void SetLayout(const BufferLayout& layout) { m_layout = layout; }
        inline const BufferLayout& GetLayout() const { return m_layout; }

        void Bind() const;
        void UnBind() const;

    private:
        uint32_t m_rendererID;
        BufferLayout m_layout;
    };   

    class IndexBuffer
    {
    public:
        ~IndexBuffer();

        IndexBuffer(uint32_t* indices, uint32_t count);

        inline uint32_t GetIndicesCount() const { return m_indicesCount; }

        void Bind() const;
        void UnBind() const;

    private:
        uint32_t m_rendererID;
        uint32_t m_indicesCount;
    };
}
