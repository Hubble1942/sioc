# sioc
# /test

# add include paths to gtest, gmock
include_directories(${gtest_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}/include)

# ensure folder for test results exists
set(TEST_RESULT_DIR ${CMAKE_BINARY_DIR}/results/test)
file(MAKE_DIRECTORY ${TEST_RESULT_DIR})

# find all source files
file(GLOB_RECURSE SIOCTEST_SRC RELATIVE ${CMAKE_CURRENT_LIST_DIR} "*.h" "*.cpp")
group_by_folder_structure(SIOCTEST_SRC)

add_executable(sioctest ${SIOCTEST_SRC})
target_link_libraries(sioctest gmock_main)

add_custom_command(TARGET sioctest
    POST_BUILD
    COMMAND ${TestRuntime} $<TARGET_FILE:sioctest> --gtest_output="xml:${TEST_RESULT_DIR}/sioctest.xml"
    COMMENT "running unit tests...")


