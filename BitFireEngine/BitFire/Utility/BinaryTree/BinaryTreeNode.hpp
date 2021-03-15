#pragma once

namespace BF
{
	template<class T>
	struct BinaryTreeNode
	{		
		public:
		T* Data;

		BinaryTreeNode<T>* LeftNode;
		BinaryTreeNode<T>* RightNode;

		BinaryTreeNode() 
		{
			NodeID = nullptr;
			LeftNode = nullptr;
			RightNode = nullptr;
		}

		BinaryTreeDirection GetBelenceDirection()
		{
			bool equal = (LeftNode == nullptr && RightNode == nullptr) || (LeftNode != nullptr && RightNode != nullptr);
			BinaryTreeDirection binaryTreeDirection;

			if (equal)
			{
				binaryTreeDirection = BinaryTreeDirection::None;
			}
			else
			{
				binaryTreeDirection = RightNode == nullptr ? BinaryTreeDirection::Left : BinaryTreeDirection::Right;
			}

			return binaryTreeDirection;
		}
	};
}