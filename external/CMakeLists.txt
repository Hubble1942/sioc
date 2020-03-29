# Sioc - simple inversion of control container
# /external

include(FetchContent)

###############################################################################
### googletest
###############################################################################

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.1
)

set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    message(STATUS "Fetching googletest")
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set_target_properties(gmock PROPERTIES
    FOLDER "external"
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

set_target_properties(gtest PROPERTIES
    FOLDER "external"
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
