cmake_minimum_required(VERSION 3.5)

project(tests LANGUAGES CXX C VERSION 0.0.1)

set( TARGET tests)

find_package(Catch2 REQUIRED)
add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2 PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)

set(EXECUTABLE_OUTPUT_PATH ../bin)
set(LIBRARY_OUTPUT_PATH ../lib)
