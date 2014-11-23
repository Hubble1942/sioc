# Sioc - simple inversion of control container
# /test

# add include paths to gtest, gmock
include_directories(${gtest_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}/include)

# ensure folder for test results exists
set(TEST_RESULT_DIR ${CMAKE_BINARY_DIR}/results/test)
file(MAKE_DIRECTORY ${TEST_RESULT_DIR})

# find all source files
file(GLOB_RECURSE SiocTest_SRC RELATIVE ${CMAKE_CURRENT_LIST_DIR} "*.h" "*.cpp")
group_by_folder_structure(SiocTest_SRC)

add_executable(SiocTest ${SiocTest_SRC})
target_link_libraries(SiocTest gmock_main)

add_custom_command(TARGET SiocTest
    POST_BUILD
    COMMAND ${TestRuntime} $<TARGET_FILE:SiocTest> --gtest_output="xml:${TEST_RESULT_DIR}/SiocTest.xml"
    COMMENT "running unit tests...")


