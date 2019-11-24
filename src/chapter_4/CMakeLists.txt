cmake_minimum_required(VERSION 3.5)

project(chapter_three)

set(CMAKE_CXX_STANDARD 11)

add_executable(TestPoint
  "TestPoint.cpp"
  "Point.hpp"
  "Point.cpp"
)