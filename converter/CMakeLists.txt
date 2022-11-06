cmake_minimum_required(VERSION 3.14)
project(converter LANGUAGES CXX C VERSION 0.0.1)


set(CMAKE_CXX_STANDARD 17)

find_package(spdlog REQUIRED)

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

file(GLOB_RECURSE SOURCES "src/**.cpp")
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} 
PUBLIC 
$<INSTALL_INTERFACE:include> 
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
${CMAKE_FIND_ROOT_PATH})
target_link_libraries(${PROJECT_NAME} spdlog fmt)

