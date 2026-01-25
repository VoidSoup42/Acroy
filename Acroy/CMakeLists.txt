add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE
    source/Core/Core.hpp
    source/Core/Application.hpp
    source/Core/Application.cpp
    source/Core/Log.hpp
    source/Core/Log.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/spdlog/include
)