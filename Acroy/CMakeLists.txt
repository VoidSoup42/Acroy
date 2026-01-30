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

    source/Renderer/RenderingContext.hpp

    source/Platform/OpenGL/OpenGLContext.hpp
    source/Platform/OpenGL/OpenGLContext.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/Acroy/source
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/glad/include
)

target_compile_definitions(Acroy PRIVATE
    GLFW_INCLUDE_NONE
)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

target_link_libraries(Acroy PUBLIC glfw glad OpenGL)
target_precompile_headers(Acroy PRIVATE source/AcroyPCH.hpp)