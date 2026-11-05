# Sioc - simple inversion of control container
# /test

set(SiocTest_SRC
    AsTypeTest.cpp
    Detail/TypeInfoTest.cpp
    InjectedTest.cpp
    LazyTest.cpp
    LifetimeTest.cpp
    NamedTest.cpp
    RegisterResolveTest.cpp
    TestHelpers/SomeClasses.h
)

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
