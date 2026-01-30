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
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_windowInstance);
    }
}
