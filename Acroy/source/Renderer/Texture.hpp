#pragma once

#include "Core/Core.hpp"
#include <cstdint>

namespace Acroy
{
    class Texture
    {
    public:
        virtual ~Texture() = default;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        Texture2D(const std::string& path);
        ~Texture2D() override;

        inline uint32_t GetWidth() const override { return m_width; }
        inline uint32_t GetHeight() const override { return m_height; }

        void Bind(uint32_t slot) const override;

    private:
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_rendererId;
    };
}
