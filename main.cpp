#include "tree-sitter-cpp/bindings/c/tree-sitter-cpp.h"
#include "tree_sitter/api.h"
#include <functional>
#include <iostream>
#include <memory>


template<class T>
using TDeleterFuncPtr = void (*)(T *);

template<class T, TDeleterFuncPtr<T> FuncPtr>
struct TDeleter {
    void operator()(T *ptr) {
        FuncPtr(ptr);
    }
};
template<class T, TDeleterFuncPtr<T> FuncPtr>
using UniquePtr = std::unique_ptr<T, TDeleter<T, FuncPtr>>;

int main() {
    UniquePtr<TSParser, ts_parser_delete> parser(ts_parser_new());

    ts_parser_set_language(&*parser, tree_sitter_cpp());
    const char *source_code = R"(
struct A {
public:
    int intVar;
    float floatVar;
};
)";
    std::unique_ptr<TSTree, TDeleter<TSTree, ts_tree_delete>> tree(ts_parser_parse_string(
            &*parser,
            nullptr,
            source_code,
            strlen(source_code)));

    TSNode root_node = ts_tree_root_node(&*tree);
    auto childs = ts_node_child_count(root_node);
    for (uint32_t i = 0; i < childs; ++i) {
        auto child = ts_node_child(root_node, i);
        std::cout << ts_node_type(child) << std::endl;
    }

    std::unique_ptr<char> string(ts_node_string(root_node));
    std::cout << &*string << std::endl;

    return 0;
}