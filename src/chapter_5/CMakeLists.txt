cmake_minimum_required(VERSION 3.5)

project(chapter_five)

set(CMAKE_CXX_STANDARD 11)

add_executable(TestPoint
  "TestComplex.cpp"
  "Complex.hpp"
  "Complex.cpp"
)