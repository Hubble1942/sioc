# Sioc - simple inversion of control container
# /external

include(FetchContent)

###############################################################################
### googletest
###############################################################################

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
)

set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)

FetchContent_MakeAvailable(googletest)

set_target_properties(gmock PROPERTIES FOLDER "external")
set_target_properties(gtest PROPERTIES FOLDER "external")
