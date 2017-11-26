# Sioc - simple inversion of control container
# /test

include(GroupByFolderStructure)

include(SiocTest.cmake)
group_by_folder_structure(SiocTest_SRC)

add_executable(SiocTest ${SiocTest_SRC})

target_include_directories(SiocTest PUBLIC
    ${gtest_SOURCE_DIR}/include
    ${gmock_SOURCE_DIR}/include
)

target_link_libraries(SiocTest
    gmock_main
)

add_custom_target(RunSiocTest DEPENDS SiocTest)
set_target_properties(RunSiocTest PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD TRUE)

add_custom_command(TARGET RunSiocTest
    POST_BUILD
    COMMAND ${TestRuntime} $<TARGET_FILE:SiocTest>
)
