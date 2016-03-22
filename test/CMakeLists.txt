project(redwalk CXX)
cmake_minimum_required(VERSION 2.8.0)

include_directories("$CMAKE_CURRENT_SOURCE_DIR")
include_directories("$CMAKE_CURRENT_BINARY_DIR/src")

add_executable(unit_tests
  unit_tests.cpp
)
set_property(TARGET unit_tests PROPERTY CXX_STANDARD 11)
target_compile_features(unit_tests PRIVATE cxx_constexpr)
target_compile_features(unit_tests PRIVATE cxx_nullptr)

add_custom_target(check
  DEPENDS unit_tests
  COMMAND ./unit_tests
)
