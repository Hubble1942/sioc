# Sioc - simple inversion of control container
# /

###############################################################################
### General cmake settings
###############################################################################
cmake_minimum_required(VERSION 3.14)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
project (Sioc)

###############################################################################
### boost Stuff
###############################################################################

set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost 1.64.0 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

###############################################################################
### Compiler settings
###############################################################################

# Visual C++ specific settings
if(MSVC)
    add_definitions(/W4)
endif(MSVC)

# GCC specific settings
if(CMAKE_COMPILER_IS_GNUCC)
    # all warnings
    add_definitions(-Wall -Wextra)

    # enable c++ 11 features in gcc (why aren't they enabled by default?)
    add_definitions(-std=c++11)
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
