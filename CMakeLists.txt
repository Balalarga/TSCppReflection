cmake_minimum_required(VERSION 3.28)
project(TSReflection)

set(CMAKE_CXX_STANDARD 20)

add_executable(TSReflection
    Source/main.cpp
    tree-sitter-cpp/bindings/c/tree-sitter-cpp.h
    tree-sitter-cpp/src/tree_sitter/alloc.h
    tree-sitter-cpp/src/tree_sitter/array.h
    tree-sitter-cpp/src/tree_sitter/parser.h
    tree-sitter-cpp/src/parser.c
    tree-sitter-cpp/src/scanner.c
    Source/MemoryWrap.h
    Source/NodeTypes.h
    Source/NodeTypes.cpp
    Source/TreeWalker.h
    Source/TreeWalker.cpp
)

add_compile_definitions(ASSETS_PATH="${CMAKE_CURRENT_LIST_DIR}/Assets/")

set(BUILD_SHARED_LIBS OFF)
add_subdirectory(tree-sitter/lib tree-sitter)
target_link_libraries(TSReflection PUBLIC tree-sitter)
target_include_directories(TSReflection PUBLIC tree-sitter/lib/include)