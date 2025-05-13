cmake_minimum_required(VERSION 3.10)
project(ogt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

add_subdirectory(external/assimp)
add_subdirectory(external/glfw)

add_executable(ogt
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c
    ${CMAKE_SOURCE_DIR}/src/shader/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/model/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/model/model.cpp
)
target_include_directories(ogt PRIVATE
    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/glm
)


target_link_libraries(ogt
    OpenGL::GL
    glfw
    assimp::assimp
)