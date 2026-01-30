#pragma once

#include "Renderer/RenderingContext.hpp"
struct GLFWwindow;

namespace Acroy
{
    class OpenGLContext : public RenderingContext
    {
    public:
        OpenGLContext(GLFWwindow* windowInstance);

        void Init() override;
        void SwapBuffers() override;

    private:
        GLFWwindow* m_windowInstance;
    };
}
