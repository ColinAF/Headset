cmake_minimum_required(VERSION 3.10)
project(Headset)

set(CMAKE_CXX_STANDARD 11)

# ----------------------------------------------------------------------------
# GLFW
# ----------------------------------------------------------------------------
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)

add_subdirectory(external/glfw)  # If you have a CMakeLists in external/glfw

# ----------------------------------------------------------------------------
# GLAD
# ----------------------------------------------------------------------------
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# ----------------------------------------------------------------------------
# Our executable
# ----------------------------------------------------------------------------
add_executable(MyOpenGLProject
    src/main.cpp
    # Optional if you want to embed shaders:
    # src/shaders/vertex_shader.glsl
    # src/shaders/fragment_shader.glsl
)

target_link_libraries(MyOpenGLProject
    glfw
    glad
    # Link extra libraries if needed (e.g. X11 on Linux, etc.)
)

# Copy shaders next to the executable (optional convenience step)
add_custom_command(TARGET MyOpenGLProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/shaders"
    "${CMAKE_BINARY_DIR}/src/shaders")
