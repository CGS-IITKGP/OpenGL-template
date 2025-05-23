cmake_minimum_required(VERSION 3.10)
project(ogt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_SAMPLES OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)

find_package(OpenGL REQUIRED)

add_subdirectory(external/assimp)
add_subdirectory(external/glfw)

add_executable(ogt
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c
    ${CMAKE_SOURCE_DIR}/src/shader/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/model/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/model/model.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/fileio.cpp
)
target_include_directories(ogt PRIVATE
    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/glm
    ${CMAKE_SOURCE_DIR}/external/
)


target_link_libraries(ogt
    OpenGL::GL
    glfw
    assimp::assimp
)

if(APPLE)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    find_library(CORESERVICES_LIBRARY CoreServices)
    target_link_libraries(ogt
     ${COREFOUNDATION_LIBRARY} ${CORESERVICES_LIBRARY})
endif()