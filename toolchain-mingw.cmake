set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR amd64)
set(CMAKE_SYSTEM_VERSION 10)
# set(CMAKE_SYSTEM_PROCESSOR Intel)


set(MINGW_COMPILER_PREFIX "x86_64-w64-mingw32" CACHE STRING
    "What compiler prefix to use for mingw")

set(MINGW_SYSROOT "/usr/${MINGW_COMPILER_PREFIX}" CACHE STRING
    "What sysroot to use for mingw")

find_program(CMAKE_RC_COMPILER NAMES ${MINGW_COMPILER_PREFIX}-windres)
find_program(CMAKE_C_COMPILER NAMES ${MINGW_COMPILER_PREFIX}-gcc)
find_program(CMAKE_CXX_COMPILER NAMES ${MINGW_COMPILER_PREFIX}-g++)
if(NOT CMAKE_CXX_COMPILER)
    execute_process(
        COMMAND bash -c "echo  ${MY_SUDO_PASS} | sudo -S apt-get install mingw-w64 -y"
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error
        RESULT_VARIABLE result
    )

    if(output)
        # message(${output})
    endif()

    if(error)
        message(${error})
    endif()

    # message(${result})
endif()


# specify the cross compiler
set(CMAKE_C_COMPILER_TARGET ${TARGET})
set(CMAKE_C_COMPILER ${MINGW_COMPILER_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER_TARGET ${TARGET})
set(CMAKE_CXX_COMPILER ${MINGW_COMPILER_PREFIX}-g++)

# C/C++ toolchain
set(MY_LINK_DIR /usr/lib/gcc/${MINGW_COMPILER_PREFIX}/10-win32)

# specify compiler flags
# Warn: if set -c option, then it compile and assemble, but do not link, when make,it will show the error "linker input file unused because linking not done"  
set(CMAKE_CXX_FLAGS "-Wall -g -fmessage-length=0 -Wextra -fexceptions -fPIC -static-libstdc++ -static-libgcc" CACHE STRING "Common flags for C++ compiler")


set(CMAKE_FIND_ROOT_PATH ${MINGW_SYSROOT})


# adjust the default behaviour of the FIND_XXX() commands:
# - search for build programs in the host environment?
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# - search for static libraries?
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# - search for headers?
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


add_compile_definitions(C_DEBUG)
