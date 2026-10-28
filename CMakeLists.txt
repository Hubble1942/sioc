# Sioc - simple inversion of control container
# /

###############################################################################
### General cmake settings
###############################################################################
cmake_minimum_required(VERSION 3.16)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
project (Sioc)

###############################################################################
### Compiler settings
###############################################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Visual C++ specific settings
if(MSVC)
    add_definitions(/W4)
endif(MSVC)

# GCC specific settings
if(CMAKE_COMPILER_IS_GNUCC)
    # all warnings
    add_definitions(-Wall -Wextra)
endif(CMAKE_COMPILER_IS_GNUCC)

include_directories(${CMAKE_CURRENT_LIST_DIR})

###############################################################################
### What is to build
###############################################################################

add_subdirectory(external)
add_subdirectory(Sioc)
add_subdirectory(test)

###############################################################################
### Generate helper script to update cmake
###############################################################################
if(MSVC)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/update_cmake.cmd "@echo off\ncls\ncall ..\\scansources.cmd\ncmake ..\n")
endif()
