# sioc
# /

###############################################################################
### General cmake settings
###############################################################################
cmake_minimum_required (VERSION 3.0)
project (sioc)

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

###############################################################################
### Custom macros
###############################################################################

# define macro to group source files by their folder structure
macro(group_by_folder_structure FILE_LIST)
    
    foreach(FILE ${${FILE_LIST}})
        get_filename_component(PARENT_DIR "${FILE}" PATH)
        string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")
        source_group("${GROUP}" FILES "${FILE}")
    endforeach()
    
endmacro()

###############################################################################
### What is to build
###############################################################################

add_subdirectory(sioc)