#pragma once

#include "BinaryTreeDirection.h"
#include "BinaryTreeNode.hpp"

namespace BF
{
	template<class T>
	class BinaryTree
	{
		private:
		BinaryTreeNode<T>* _node;
		unsigned int _size;

		BinaryTreeDirection CheckNodeDirection(T value, T target)
		{
			const bool isBigger = value > target;

			if (isBigger)
			{
				return BinaryTreeDirection::Right;
			}
			else
			{
				return value == target ? BinaryTreeDirection::None : BinaryTreeDirection::Left;				
			}
		}

		public:
		BinaryTree()
		{
			_size = 0;
			_node = nullptr;
		}

		bool IsEmpty() { return _size == 0; }

		void Add(T element)
		{		
			BinaryTreeNode<T>* lastNode = nullptr;
			BinaryTreeNode<T>* currentNode = _node;
			BinaryTreeDirection direction = BinaryTreeDirection::None;

			if (IsEmpty())
			{
				_node = new BinaryTreeNode<T>(element);
			}
			else
			{
				while (currentNode != nullptr)
				{
					direction = CheckNodeDirection(element, currentNode->Data);

					lastNode = currentNode;

					switch (direction)
					{
						case BinaryTreeDirection::None:
							throw "Can not add, already exists";

						case BinaryTreeDirection::Left:
							currentNode = currentNode->LeftNode;
							break;

						case BinaryTreeDirection::Right:
							currentNode = currentNode->RightNode;
							break;
					}
				}

				switch (direction)
				{
					case BinaryTreeDirection::Left:
						lastNode->LeftNode = new BinaryTreeNode<T>(element);;
						break;

					case BinaryTreeDirection::Right:
						lastNode->RightNode = new BinaryTreeNode<T>(element);
						break;
				}
			}
			
			_size++;
		}

		void Remove(T element)
		{

		}

		T* Find(T element)
		{

		}

		void RotateLeft()
		{

		}

		void RotateRight()
		{

		}		
	};
}