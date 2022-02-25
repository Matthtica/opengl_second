cmake_minimum_required(VERSION 3.22)
project(Learn)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
add_subdirectory(glad)

add_executable(Learn main.cpp)

target_link_libraries(Learn
    glfw
    OpenGL
    glad
)
