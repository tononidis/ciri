add_library(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME}
    PUBLIC
    FILE_SET CXX_MODULES FILES 
    Ciri.cppm
    Traits.cppm
    Buffer.cppm
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -freflection
    -fmodules-ts
)