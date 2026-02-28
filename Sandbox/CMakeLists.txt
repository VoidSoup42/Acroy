add_executable(Sandbox_Application
    source/Main.cpp
    source/SandboxLayer.hpp
    source/SandboxLayer.cpp
    source/CameraController.hpp
    source/CameraController.cpp
)

target_link_libraries(Sandbox_Application PUBLIC Acroy)

target_include_directories(Sandbox_Application PRIVATE
    ${CMAKE_SOURCE_DIR}/Acroy/source
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/glm
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/entt
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/imgui
)
