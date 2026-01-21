add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE
    Core/Application.cpp
    Core/Window.cpp

    Graphics/Renderer.cpp
    Graphics/Shader.cpp
    Graphics/Texture.cpp

    # stb
    ${CMAKE_SOURCE_DIR}/Vendor/stb/stb_image_loader.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/Vendor/stb/
)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL glfw GLEW)
