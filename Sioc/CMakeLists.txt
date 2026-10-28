# Sioc - simple inversion of control container
# /Sioc

include(GroupByFolderStructure)

include(Sioc.cmake)
group_by_folder_structure(Sioc_SRC)

# header only library, the sources are listed to show them in IDEs
add_library(Sioc INTERFACE ${Sioc_SRC})
