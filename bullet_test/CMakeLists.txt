cmake_minimum_required(VERSION 3.10)
project(bullet_test)

# Add bullet from parent directory
add_subdirectory(../external/bullet3)

# Create test executable
add_executable(bullet_test test_bullet.cpp)

# Link bullet libraries
target_link_libraries(bullet_test
    BulletDynamics
    BulletCollision
    LinearMath
)

# Include directories
target_include_directories(bullet_test PRIVATE
    ../external/bullet3/src
)
