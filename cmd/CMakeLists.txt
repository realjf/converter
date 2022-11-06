cmake_minimum_required(VERSION 3.14)

project(converter_cmd LANGUAGES CXX C VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)



link_directories(${LIBRARY_OUTPUT_PATH})


add_executable(${PROJECT_NAME} src/main.cpp)


target_link_libraries(${PROJECT_NAME} converter)
target_include_directories(${PROJECT_NAME} PRIVATE converter)

