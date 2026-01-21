#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Acroy {

    class Texture
    {
    public:
        explicit Texture(const char* path);
        ~Texture();

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        Texture(Texture&& other) noexcept;
        Texture& operator=(Texture&& other) noexcept;

        uint32_t GetID() const      { return _id; }
        uint32_t GetChannels() const { return _channels; }
        glm::ivec2 GetSize() const  { return { _width, _height }; }

    private:
        uint32_t _id{0};
        int32_t  _width{0};
        int32_t  _height{0};
        int32_t  _channels{0};
    };

}
