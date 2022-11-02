set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR amd64)

# set(CMAKE_GENERATOR "Unix Makefiles")


# specify the cross compiler
set(CMAKE_C_COMPILER_TARGET ${TARGET})
set(CMAKE_C_COMPILER gcc-10)
set(CMAKE_CXX_COMPILER_TARGET ${TARGET})
set(CMAKE_CXX_COMPILER g++-11)


set(CMAKE_FIND_ROOT_PATH "/usr/include/")

# C/C++ toolchain

# specify compiler flags
set(CMAKE_CXX_FLAGS "-Wall -g -Wextra -fexceptions -fno-threadsafe-statics" CACHE STRING "Common flags for C++ compiler")