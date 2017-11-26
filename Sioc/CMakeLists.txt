# Sioc - simple inversion of control container
# /Sioc

include(GroupByFolderStructure)

include(Sioc.cmake)
group_by_folder_structure(Sioc_SRC)

add_library(Sioc ${Sioc_SRC})