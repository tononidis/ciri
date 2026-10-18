add_executable(
    Simple
    "Simple.cpp"
)

target_link_libraries(
    Simple
    PRIVATE
    ${PROJECT_NAME}
)

target_compile_options(
    Simple
    PRIVATE
    -fmodules-ts
)