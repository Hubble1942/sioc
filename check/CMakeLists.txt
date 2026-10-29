# Sioc - simple inversion of control container
# /check

# compiles the headers with the minimum language version required for using Sioc
add_library(SiocCpp14Check OBJECT Cpp14Check.cpp)

set_target_properties(SiocCpp14Check PROPERTIES
    CXX_STANDARD 14
)

# reject language extensions, e.g. C++17 nested namespace definitions
target_compile_options(SiocCpp14Check PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-pedantic-errors>
)
