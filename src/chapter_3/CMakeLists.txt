cmake_minimum_required(VERSION 3.5)

project(chapter_three)

set(CMAKE_CXX_STANDARD 11)

add_executable(TestEuropeanOption
  "TestEuropeanOption.cpp"
  "EuropeanOption.hpp"
  "EuropeanOption.cpp"
)

add_executable(TestSimpleBondPricing
  "TestSimpleBondPricing.cpp"
  "SimpleBondPricing.hpp"
  "SimpleBondPricing.cpp"
)