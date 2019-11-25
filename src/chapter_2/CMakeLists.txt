cmake_minimum_required(VERSION 3.5)

project(chapter_two)

set(CMAKE_CXX_STANDARD 11)

add_executable(TestConversions
  "TestConversions.cpp"
)

add_executable(TestGenericInequalities
  "TestGenericInequalities.cpp"
  "GenericInequalities.hpp"
  "GenericInequalities.cpp"
)

add_executable(TestInequalities
  "TestInequalities.cpp"
  "Inequalities.hpp"
  "Inequalities.cpp"
)

add_executable(TestPerson
  "TestPerson.cpp"
  "Person.hpp"
  "Person.cpp"
  "DatasimDate.hpp"
  "DatasimDate.cpp"
  "temporaltype.hpp"
)