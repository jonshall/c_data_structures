cmake_minimum_required(VERSION 3.16)

project(
    bst
    VERSION 1.0.0
    LANGUAGES "C"
    DESCRIPTION "Binary Search Tree"
)

find_program(CLANG_TIDY_PROG clang-tidy)
if(CLANG_TIDY_PROG)
        set(CMAKE_C_CLANG_TIDY ${CLANG_TIDY_PROG};
        "--checks=*,-llvm-include-order,-cppcoreguidelines-*,-readability-magic-numbers,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling,-hiccp-no-assembler")
        set(CMAKE_C_FLAGS "-g")
    else()
        set(CMAKE_C_COMPILER gcc)
        set(CMAKE_C_FLAGS "-g -Wall -pedantic")
    endif()

if(CMAKE_BUILD_TYPE STREQUAL "DEBUG" OR 
    CMAKE_BUILD_TYPE STREQUAL "Debug" OR 
    CMAKE_BUILD_TYPE STREQUAL "debug")
    message("Debugging version.")
    add_compile_definitions(DEBUG)
    else()
        message("RELEASE VERSION")
endif() 

message(" including directories")
include_directories(include/)

message(" add executables to bin dir")
set(EXECUTABLE_OUTPUT_PATH ../bin)

message(" adding libraries")
add_library(binary_search_tree SHARED src/binary_search_tree.c)

add_executable(bst src/binary_search_tree.c)
