add_executable(Sandbox_Application)

target_sources(Sandbox_Application PUBLIC Source/Sandbox.cpp)

target_link_libraries(Sandbox_Application PUBLIC Acroy)

include_directories(${CMAKE_SOURCE_DIR}/Acroy/Source)