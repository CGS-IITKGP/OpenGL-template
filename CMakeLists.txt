cmake_minimum_required(VERSION 3.10)
project(ogt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)


add_executable(ogt
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/glad.c
    ${CMAKE_SOURCE_DIR}/src/shader/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/model/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/model/model.cpp
)
target_include_directories(ogt PRIVATE
    # Add the location of your assimp library/ include folder
    ${CMAKE_SOURCE_DIR}/include
)


target_link_libraries(ogt
    OpenGL::GL
    glfw
    assimp::assimp
)