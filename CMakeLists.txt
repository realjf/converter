cmake_minimum_required(VERSION 3.14)

project(converter_app LANGUAGES CXX C VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# set executable output path
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set library output path
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(BUILD_SHARED_LIBS OFF)

add_compile_definitions(C_DEBUG SPDLOG_HEADER_ONLY FMT_HEADER_ONLY)


include(${CMAKE_TOOLCHAIN_FILE})
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(converter)
add_subdirectory(cmd)