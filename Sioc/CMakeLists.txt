# Sioc - simple inversion of control container
# /Sioc

# find all source files
file(GLOB_RECURSE Sioc_SRC RELATIVE ${CMAKE_CURRENT_LIST_DIR} "*.h" "*.cpp")
group_by_folder_structure(Sioc_SRC)

add_library(Sioc ${Sioc_SRC})