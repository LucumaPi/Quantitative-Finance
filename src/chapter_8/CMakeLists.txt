cmake_minimum_required(VERSION 3.5)

project(chapter_eight)

set(CMAKE_CXX_STANDARD 11)

add_executable(TestMultiAsset
  "TestMultiAsset.cpp"
  "MultiAssetPayoffStrategy.hpp"
  "MultiAssetFactory.hpp"
  "Inequalities.hpp"
  "Inequalities.cpp"
)

add_executable(TestOneFactorPayoff
  "TestOneFactorPayoff.cpp"
  "OneFactorPayoff.hpp"
  "OneFactorPayoff.cpp"
)

add_executable(TestPayoff
  "TestPayoff.cpp"
  "CallPayoff.hpp"
  "CallPayoff.cpp"
  "Payoff.hpp"
  "Payoff.cpp"
  "BullSpreadPayoff.hpp"
  "BullSpreadPayoff.cpp"
)

add_executable(TestRectangle
  "TestRectangle.cpp"
  "Rectangle.cpp"
  "Point.hpp"
  "Point.cpp"
)

add_executable(VirtualDestructors
  "VirtualDestructors.cpp"
)