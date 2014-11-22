# sioc
# /sioc

# find all source files
file(GLOB_RECURSE SIOC_SRC RELATIVE ${CMAKE_CURRENT_LIST_DIR} "*.h" "*.cpp")
group_by_folder_structure(SIOC_SRC)

add_library(sioc ${SIOC_SRC})