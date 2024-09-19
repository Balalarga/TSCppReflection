#ifndef TSREFLECTION_NODETYPES_H
#define TSREFLECTION_NODETYPES_H

#include <functional>
#include <optional>
#include <string_view>
#include <variant>

#include "MemoryWrap.h"
#include "tree_sitter/api.h"


class Node;

class INode
{
public:
	explicit INode(TSNode&& node);

	INode(INode&&) = default;
	INode(const INode&) = default;
	INode& operator=(INode&&) = default;
	INode& operator=(const INode&) = default;
	virtual ~INode() = default;

	const TSNode& GetTSNode() const;


private:
	TSNode _node;
};

class NullNode
{
};


class ClassNode: public INode
{
public:
	void Child(std::function<void(Node)>&& walker);
};


class StructNode: public ClassNode
{
public:
};


class Node: public std::variant<ClassNode, StructNode, NullNode>
{
	template <class T>
	T* Get() const
	{
		return std::get_if<T>(*this);
	}

	template <class T>
	bool IsA() const
	{
		return std::holds_alternative<T>(*this);
	}
};


#endif // TSREFLECTION_NODETYPES_H