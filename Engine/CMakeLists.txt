add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME} PRIVATE Main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL glfw GLEW)
