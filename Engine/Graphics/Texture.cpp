#include "Texture.hpp"
#include <GL/glew.h>
#include <stb_image.h>

namespace Acroy {
    Texture::Texture(const char* path)
    {
        stbi_set_flip_vertically_on_load(true);
        imageBytes = stbi_load(path, &_width, &_height, &_channels, 0);

        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);
        // glActiveTexture(GL_TEXTURE0 + slot);

        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        uint32_t format = (_channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, imageBytes);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(imageBytes);
    }
}
