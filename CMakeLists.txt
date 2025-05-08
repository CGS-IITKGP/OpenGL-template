cmake_minimum_required(VERSION 3.10)
project(ogt)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)


add_executable(ogt
    src/main.cpp
    src/glad.c
    src/shader/shader.cpp
    src/model/mesh.cpp
    src/model/model.cpp
)

target_include_directories(ogt PRIVATE
    /usr/include
)

target_link_libraries(ogt
    OpenGL::GL
    glfw
    assimp::assimp
)