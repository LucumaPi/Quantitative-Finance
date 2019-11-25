cmake_minimum_required(VERSION 3.5)

project(chapter_six)

set(CMAKE_CXX_STANDARD 11)

add_executable(TestBoundsError
  "TestBoundsError.cpp"
)

add_executable(TestComplex
  "TestComplex.cpp"
  "Complex.hpp"
  "Complex.cpp"
)

add_executable(TestComplexArray
  "TestComplexArray.cpp"
  "Complex.hpp"
  "Complex.cpp"
)

add_executable(TestComplexArrayClass
  "TestComplexArrayClass.cpp"
  "Complex.hpp"
  "Complex.cpp"
  "ComplexArray.hpp"
  "ComplexArray.cpp"
)

add_executable(TestOptionStack
  "TestOptionStack.cpp"
)