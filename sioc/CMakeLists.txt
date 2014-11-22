# sioc
# /sioc

# find all source files
file(GLOB_RECURSE sioc_SRC RELATIVE ${CMAKE_CURRENT_LIST_DIR} "*.h" "*.cpp")
group_by_folder_structure(sioc_SRC)

add_library(sioc ${sioc_SRC})