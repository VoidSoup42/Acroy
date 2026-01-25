add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE
        Source/Core.hpp
        Source/Application.hpp
        Source/Application.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL glfw GLEW)
