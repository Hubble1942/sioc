# (c) by Christian Ewald

# groups source files by their folder structure
macro(group_by_folder_structure FILE_LIST)
    
    foreach(FILE ${${FILE_LIST}})
        get_filename_component(PARENT_DIR "${FILE}" PATH)
        string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")
        source_group("${GROUP}" FILES "${FILE}")
    endforeach()
    
endmacro()