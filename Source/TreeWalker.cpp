#include "TreeWalker.h"


TreeWalker::TreeWalker(TUniquePtr<TSTree, ts_tree_delete>&& tree, TSLanguage* lang) :
	_tree(std::move(tree)), _lang(lang)
{
}

std::optional<Node> TreeWalker::Root()
{
	if (!_tree)
		return std::nullopt;

	return GetNode(ts_tree_root_node(&*_tree));
}

Node TreeWalker::GetNode(TSNode node)
{
	auto type = ts_node_type(node);


	return {NullNode{}};
}