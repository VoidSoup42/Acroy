#include "Platform/OpenGL/OpenGLContext.hpp"
#include "Core/Log.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Acroy
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowInstance) : m_windowInstance(windowInstance) {}

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_windowInstance);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ACROY_CORE_ASSERT(status, "Failed to initialize Glad!");

        ACROY_CORE_INFO("Vendor:   {}", (const char*)glGetString(GL_VENDOR));
        ACROY_CORE_INFO("Renderer: {}", (const char*)glGetString(GL_RENDERER));
        ACROY_CORE_INFO("Version:  {}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_windowInstance);
    }
}
