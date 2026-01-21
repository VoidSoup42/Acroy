#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Acroy {
    class Texture
    {
    public:
        Texture(const char* path);

        inline uint32_t GetTexture() const  { return _id; }
        inline uint32_t GetChannels() const { return _channels; }
        inline glm::vec2 GetSize() const    { return { _width, _height }; }
        
        inline uint8_t*& GetImageBytes()    { return imageBytes; }

    private:
        uint32_t _id;
        int32_t _width;
        int32_t _height;
        int32_t _channels;
        uint8_t* imageBytes;
    };
}
