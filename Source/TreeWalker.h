#pragma once

#include "NodeTypes.h"


class TreeWalker
{
public:
	explicit TreeWalker(TUniquePtr<TSTree, ts_tree_delete>&& tree, TSLanguage* lang);

	TreeWalker(const TreeWalker&) = delete;
	TreeWalker& operator=(const TreeWalker&) = delete;
	TreeWalker(TreeWalker&&) = default;
	~TreeWalker() = default;

	std::optional<Node> Root();


protected:
	Node GetNode(TSNode node);


private:
	TUniquePtr<TSTree, ts_tree_delete> _tree;
	TSLanguage* _lang;
};