cmake_minimum_required(VERSION 3.5)

project(chapter_seven)

set(CMAKE_CXX_STANDARD 11)

add_executable(Person
  "Person.cpp"
  "DatesimDateTime.hpp"
  "DatesimDateTime.cpp"
  "DatasimDate.hpp"
  "DatasimDate.cpp"
  "temporaltype.hpp"
)

add_executable(TestAlias
  "TestAlias.cpp"
)

add_executable(testAlliasNamespace
  "testAlliasNamespace.cpp"
)

add_executable(TestImpliedVolatility
  "TestImpliedVolatility.cpp"
  "NonlinearSolver.hpp"
)

add_executable(testNamespace
  "testNamespace.cpp"
)

add_executable(TestNonlinearSolver
  "TestNonlinearSolver.cpp"
  "NonlinearSolver.hpp"
)

add_executable(TestPersonAndEmployee
  "TestPersonAndEmployee.cpp"
  "PersonAndEmployee.hpp"
  "DatesimDateTime.hpp"
  "DatesimDateTime.cpp"
  "DatasimDate.hpp"
  "DatasimDate.cpp"
  "temporaltype.hpp"
)