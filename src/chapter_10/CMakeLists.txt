cmake_minimum_required(VERSION 3.5)

project(chapter_nine)

set(CMAKE_CXX_STANDARD 11)

add_executable(TestExceptionSimple
  "TestExceptionSimple.cpp"
  "StringConversions.hpp"
  "StringConversions.cpp"
  "Vector.hpp"
  "Vector.cpp"
  "Array.hpp"
  "Array.cpp"
  "ArrayStructure.hpp"
  "ArrayStructure.cpp"
  "FullArray.hpp"
  "FullArray.cpp"
  "DatasimException.hpp"
  "DatasimException.cpp"
)