# Sioc - simple inversion of control container
# /check

# compiles the headers with the minimum language version required for using Sioc
add_library(SiocCpp17Check OBJECT Cpp17Check.cpp)

set_target_properties(SiocCpp17Check PROPERTIES
    CXX_STANDARD 17
)

# reject language extensions
target_compile_options(SiocCpp17Check PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-pedantic-errors>
)

# Qt 4's moc fails on nested namespace definitions (namespace A::B), even in headers it only includes
file(GLOB_RECURSE SIOC_HEADERS ${PROJECT_SOURCE_DIR}/Sioc/*.h)
foreach(header ${SIOC_HEADERS})
    file(STRINGS ${header} nested REGEX "^ *namespace +[A-Za-z0-9_]+::")
    if(nested)
        message(FATAL_ERROR "${header}: nested namespace definition, which Qt 4's moc can't parse: ${nested}")
    endif()
endforeach()
