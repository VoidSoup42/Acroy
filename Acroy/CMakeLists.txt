add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE
    source/Core.hpp
    source/Application.hpp
    source/Application.cpp
    source/Log.hpp
    source/Log.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/spdlog/include
)