cmake_minimum_required(VERSION 3.10)
project(bullet_test)

# Just add bullet
add_subdirectory(external/bullet3)

add_executable(bullet_test bullet_only_test.cpp)
target_link_libraries(bullet_test
    BulletDynamics BulletCollision LinearMath
)
target_include_directories(bullet_test PRIVATE
    external/bullet3/src
)
