cmake_minimum_required(VERSION 3.28)
project(TSReflection)

set(CMAKE_CXX_STANDARD 20)

add_executable(TSReflection
    main.cpp
    tree-sitter-cpp/bindings/c/tree-sitter-cpp.h
    tree-sitter-cpp/src/tree_sitter/alloc.h
    tree-sitter-cpp/src/tree_sitter/array.h
    tree-sitter-cpp/src/tree_sitter/parser.h
    tree-sitter-cpp/src/parser.c
    tree-sitter-cpp/src/scanner.c
)

set(BUILD_SHARED_LIBS OFF)
add_subdirectory(../tree-sitter/lib tree-sitter)
target_link_libraries(TSReflection PUBLIC tree-sitter)
target_include_directories(TSReflection PUBLIC ../tree-sitter/lib/include)