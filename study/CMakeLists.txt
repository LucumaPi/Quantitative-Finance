cmake_minimum_required(VERSION 3.11...3.16)

set(PROJECT_NAME "DuffyProject")

project(${PROJECT_NAME}
    VERSION 1.0.0
    DESCRIPTION "An example project with Duffy"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_GENERATOR "Ninja")

add_subdirectory(src)
add_subdirectory(tests)