add_executable(Sandbox_Application)

target_sources(Sandbox_Application PUBLIC source/Sandbox.cpp)

target_link_libraries(Sandbox_Application PUBLIC Acroy)

include_directories(
    ${CMAKE_SOURCE_DIR}/Acroy/source
    ${CMAKE_SOURCE_DIR}/Acroy/vendor/spdlog/include
)
