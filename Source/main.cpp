#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../tree-sitter-cpp/bindings/c/tree-sitter-cpp.h"
#include "tree_sitter/api.h"

#include "MemoryWrap.h"
#include "NodeTypes.h"
#include "TreeWalker.h"


std::string ReadFile(const char* path)
{
	std::ifstream file(path);
	if (!file)
	{
		std::cout << std::format("Cannot open file '{}'", path);
		return {};
	}

	std::stringstream stream;
	stream << file.rdbuf();
	return stream.str();
}


bool TryParseFile1()
{
	auto code = ReadFile(ASSETS_PATH "SimpleClasses/File1.h");
	if (code.empty())
		return false;

	TUniquePtr<TSParser, ts_parser_delete> parser(ts_parser_new());
	if (!parser)
		return false;

	ts_parser_set_language(&*parser, tree_sitter_cpp());
	TUniquePtr<TSTree, ts_tree_delete> tree{ts_parser_parse_string(&*parser, nullptr, code.data(), code.length())};
	if (!tree)
		return false;

	TreeWalker walker(std::move(tree));
	auto rootNode = walker.Root();
	if (!rootNode.has_value())
		return false;

	auto& root = *rootNode;
	auto childrenNum = ts_node_child_count(root);
	for (uint32_t i = 0; i < childrenNum; ++i)
	{
		auto child = ts_node_child(root, i);
		std::cout << ts_node_type(child) << std::endl;
	}

	TUniquePtr<char> string(ts_node_string(root));
	if (!string)
		return false;

	std::cout << &*string << std::endl;
	return true;
}


int main()
{
	if (!TryParseFile1())
		return -1;

	return 0;
}