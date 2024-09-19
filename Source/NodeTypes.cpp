#include "NodeTypes.h"


INode::INode(TSNode&& node) : _node(node)
{
}

const TSNode& INode::GetTSNode() const
{
	return _node;
}

void ClassNode::Child(std::function<void(Node)>&& walker)
{
}