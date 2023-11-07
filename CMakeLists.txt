cmake_minimum_required(VERSION 3.26)

project(FirstProject)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/glad)

add_subdirectory(extern/glfw)

add_subdirectory(extern/glm)

add_subdirectory(game)