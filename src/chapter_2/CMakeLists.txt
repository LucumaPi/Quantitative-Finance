cmake_minimum_required(VERSION 3.12)

project(chapter_two VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)

add_executable(TestConversions TestConversions.cpp)

add_executable(TestGenericInequalities
  TestGenericInequalities.cpp
  GenericInequalities.hpp
  GenericInequalities.cpp
)

add_executable(TestInequalities
  TestInequalities.cpp
  Inequalities.hpp
  Inequalities.cpp
)

add_executable(TestPerson
  TestPerson.cpp
  Person.hpp
  Person.cpp
  DatasimDate.hpp
  DatasimDate.cpp
  temporaltype.hpp
)