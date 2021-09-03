#pragma once

#include "BinaryTreeDirection.h"
#include "BinaryTreeDataNode.hpp"

namespace BF
{
	template<class Key, class Value>
	struct BinaryTreeDataRotationInformation
	{
		public:
		BinaryTreeDirection GrandParentDirection;
		BinaryTreeDataNode<Key, Value>* GrandParent;
		BinaryTreeDataNode<Key, Value>* Parent;
		BinaryTreeDataNode<Key, Value>* Child;
	};
}