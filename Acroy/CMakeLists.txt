add_library(${PROJECT_NAME} SHARED
    source/AcroyPCH.hpp

    source/Core/Core.hpp
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
)

include_directories(
    ${CMAKE_SOURCE_DIR}/Acroy/source
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/spdlog/include
)

add_subdirectory(vendor/glfw)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw OpenGL)
target_precompile_headers(Acroy PRIVATE source/AcroyPCH.hpp)