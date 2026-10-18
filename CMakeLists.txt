cmake_minimum_required(VERSION 4.4)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
set(CMAKE_CXX_MODULE_STD 1)

project(
    Ciri
    VERSION 0.1
    DESCRIPTION "."
    LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS "-freflection ${CMAKE_CXX_FLAGS}") # Remove one day? https://stackoverflow.com/questions/79940823/using-modules-and-reflection

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_subdirectory(modules)
add_subdirectory(examples)