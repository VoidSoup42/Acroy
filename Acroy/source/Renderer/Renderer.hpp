#pragma once

namespace Acroy
{
    enum class RendererAPI
    {
        None = 0, OpenGL = 1
    };

    class Renderer
    {
    public:
        inline static RendererAPI GetCurrentAPI() { return s_rendererAPI; }
        
    private:
        static RendererAPI s_rendererAPI;
    };
}
