#include "AcroyPCH.hpp"
#include "Texture.hpp"
#include "Core/Log.hpp"
#include <glad/glad.h>
#include <stb_image.h>

namespace Acroy
{
    Texture2D::Texture2D(const std::string& path)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererId);

        int x, y, channels;
        stbi_set_flip_vertically_on_load(1);
        uint8_t* bytes = stbi_load(path.c_str(), &x, &y, &channels, 0);

        if (!bytes)
        {
            ACROY_CORE_ERROR("Failed to load texture: {}", path);
            return;
        }

        m_width = x;
        m_height = y;

        GLenum internalFormat = 0;
        GLenum dataFormat = 0;

        switch (channels)
        {
            case 1: internalFormat = GL_R8;    dataFormat = GL_RED;   break;
            case 2: internalFormat = GL_RG8;   dataFormat = GL_RG;    break;
            case 3: internalFormat = GL_RGB8;  dataFormat = GL_RGB;   break;
            case 4: internalFormat = GL_RGBA8; dataFormat = GL_RGBA;  break;
            default:
                ACROY_CORE_ERROR("Unsupported number of channels: {}", channels);
                stbi_image_free(bytes);
                return;
        }

        glTextureStorage2D(m_rendererId, 4, internalFormat, m_width, m_height);
        glTextureSubImage2D(m_rendererId, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, bytes);

        glGenerateTextureMipmap(m_rendererId);

        glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(m_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(m_rendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(bytes);
        ACROY_CORE_INFO("Texture Loaded: {} (x:{}, y:{}), Channels: {}", path, x, y, channels);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_rendererId);
    }

    void Texture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_rendererId);
    }
}