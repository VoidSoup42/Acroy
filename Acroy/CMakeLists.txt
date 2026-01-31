add_library(Acroy SHARED
    source/Core/Input.hpp
    source/Core/Window.hpp
    source/Core/Application.hpp
    source/Core/Application.cpp
    source/Core/Log.hpp
    source/Core/Log.cpp
    source/Core/Layer.hpp
    source/Core/LayerStack.hpp
    source/Core/LayerStack.cpp

    source/Platform/Linux/LinuxWindow.hpp
    source/Platform/Linux/LinuxWindow.cpp
    source/Platform/Linux/LinuxInput.hpp
    source/Platform/Linux/LinuxInput.cpp

    source/Renderer/Renderer.hpp
    source/Renderer/Renderer.cpp
    source/Renderer/RenderingContext.hpp
    source/Renderer/Shader.hpp
    source/Renderer/Shader.cpp
    source/Renderer/Buffer.hpp
    source/Renderer/Buffer.cpp

    source/Platform/OpenGL/OpenGLContext.hpp
    source/Platform/OpenGL/OpenGLContext.cpp
    source/Platform/OpenGL/OpenGLBuffer.hpp
    source/Platform/OpenGL/OpenGLBuffer.cpp
)

target_include_directories(Acroy PUBLIC
    ${CMAKE_SOURCE_DIR}/Acroy/source
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/glad/include
)

target_compile_definitions(Acroy PRIVATE
    GLFW_INCLUDE_NONE
)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glm)

target_link_libraries(Acroy PUBLIC glfw glad OpenGL glm::glm-header-only)
target_precompile_headers(Acroy PRIVATE source/AcroyPCH.hpp)