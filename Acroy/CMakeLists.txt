add_library(Acroy SHARED
    source/Core/Input.hpp
    source/Core/Input.cpp

    source/Core/Window.hpp
    source/Core/Window.cpp

    source/Core/Application.hpp
    source/Core/Application.cpp

    source/Core/Log.hpp
    source/Core/Log.cpp

    source/Core/Layer.hpp
    source/Core/LayerStack.hpp
    source/Core/LayerStack.cpp
    source/Core/Timestep.hpp

    source/Scene/Components.hpp
    source/Scene/Scene.hpp
    source/Scene/Scene.cpp
    source/Scene/Entity.hpp
    source/Scene/Entity.cpp

    source/Renderer/Camera.hpp
    source/Renderer/Camera.cpp

    source/Renderer/Renderer.hpp
    source/Renderer/Renderer.cpp

    source/Renderer/Shader.hpp
    source/Renderer/Shader.cpp

    source/Renderer/Texture.hpp
    source/Renderer/Texture.cpp

    source/Renderer/Buffer.hpp
    source/Renderer/Buffer.cpp

    source/Renderer/VertexArray.hpp
    source/Renderer/VertexArray.cpp

    source/Renderer/Mesh.hpp
    source/Renderer/Mesh.cpp

    source/ImGui/ImGuiLayer.hpp
    source/ImGui/ImGuiLayer.cpp

    # Stb
    vendor/stb/stb_image.cpp

    # ImGui
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(Acroy PUBLIC
    ${CMAKE_SOURCE_DIR}/Acroy/source
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/glad/include
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/stb
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/entt
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/imgui
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
