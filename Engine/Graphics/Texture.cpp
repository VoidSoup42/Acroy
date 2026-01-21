#include "Texture.hpp"

#include <stdexcept>
#include <GL/glew.h>
#include <stb_image.h>

namespace Acroy
{

    Texture::Texture(const char* path)
    {
        stbi_set_flip_vertically_on_load(true);

        uint8_t* data = stbi_load(path, &_width, &_height, &_channels, 0);
        if (!data)
        {
            throw std::runtime_error("Failed to load texture image");
        }

        uint32_t internalFormat;
        uint32_t dataFormat;

        switch (_channels)
        {
        case 4:
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
            break;
        case 3:
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
            break;
        case 2:
            internalFormat = GL_RG8;
            dataFormat = GL_RG;
            break;
        case 1:
            internalFormat = GL_R8;
            dataFormat = GL_RED;
            break;
        default:
            stbi_image_free(data);
            throw std::runtime_error("Unsupported texture channel count");
        }

        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        if (_channels == 1)
        {
            GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_ONE};
            glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
        }

        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }

    Texture::~Texture()
    {
        if (_id != 0)
        {
            glDeleteTextures(1, &_id);
        }
    }

    Texture::Texture(Texture &&other) noexcept
        : _id(other._id),
          _width(other._width),
          _height(other._height),
          _channels(other._channels)
    {
        other._id = 0;
    }

    Texture &Texture::operator=(Texture&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteTextures(1, &_id);

            _id = other._id;
            _width = other._width;
            _height = other._height;
            _channels = other._channels;

            other._id = 0;
        }
        return* this;
    }

}
