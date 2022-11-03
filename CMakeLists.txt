cmake_minimum_required(VERSION 3.14)

project(converter LANGUAGES CXX C VERSION 0.0.1)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 17)

set( TARGET converter )

find_package(CLI11 2.1.2)
if(NOT ${CLI11_FOUND})
    execute_process(
        COMMAND bash -c "echo  ${MY_SUDO_PASS} | sudo -S apt-get install libcli11-dev -y"
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error
        RESULT_VARIABLE result
    )
    if(output)
        message(${output})
    endif()
    if(error)
        message(${error})
    endif()

    message(${result})
endif()


include(${CMAKE_TOOLCHAIN_FILE})


add_executable(converter src/main.cpp)


# set executable output path
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set library output path
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)