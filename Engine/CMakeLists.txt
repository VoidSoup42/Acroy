add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE
    Core/Application.cpp
    Core/Window.cpp

    Graphics/Renderer.cpp
    Graphics/Shader.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL glfw GLEW)
