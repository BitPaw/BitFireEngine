#pragma once
/*
#include "BinaryTreeDirection.h"
#include "BinaryTreeDataNode.hpp"
#include "BinaryTreeDataRotationInformation.h"

namespace BF
{
	template <class Key, class Value>
	class BinaryTreeData
	{
		private:
		BinaryTreeDataNode<Key, Value>* _node;
		unsigned int _size;

		BinaryTreeDirection CheckNodeDirection(Key value, Key target)
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

		void RotateLeft(BinaryTreeDataRotationInformation<Key, Value> rotationInformation)
		{
			rotationInformation->Parent->RightNode = rotationInformation->Child->LeftNode;
			rotationInformation->Child->LeftNode = rotationInformation->Parent;

			switch (rotationInformation->GrandParentDirection)
			{
				case BinaryTreeDirection::Left:
					rotationInformation->GrandParent->LeftNode = rotationInformation->Child;
					break;

				case BinaryTreeDirection::Right:
					rotationInformation->GrandParent->Right = rotationInformation->Child;
					break;
			}
		}

		void RotateRight(BinaryTreeDataRotationInformation<Key, Value> rotationInformation)
		{
			rotationInformation->Parent->LeftNode = rotationInformation->Child->RightNode;   
			rotationInformation->Child->RightNode = rotationInformation->Parent;

			switch (rotationInformation->GrandParentDirection)
			{
				case BinaryTreeDirection::Left:
					rotationInformation->GrandParent->LeftNode = rotationInformation->Child;
					break;

				case BinaryTreeDirection::Right:
					rotationInformation->GrandParent->Right = rotationInformation->Child;
					break;
			}		
		}

		public:
		BinaryTreeData()
		{
			_size = 0;
			_node = nullptr;
		}

		bool IsEmpty() { return _size == 0; }

		void Add(Key key, Value value)
		{
			BinaryTreeDataNode<Key, Value>* lastNode = nullptr;
			BinaryTreeDataNode<Key, Value>* currentNode = _node;
			BinaryTreeDirection direction = BinaryTreeDirection::None;

			if (IsEmpty())
			{
				_node = new BinaryTreeDataNode<Key, Value>(value);
			}
			else
			{
				while (currentNode != nullptr)
				{
					direction = CheckNodeDirection(value, currentNode->Data);

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
						lastNode->LeftNode = new BinaryTreeDataNode<Key, Value>(value);;
						break;

					case BinaryTreeDirection::Right:
						lastNode->RightNode = new BinaryTreeDataNode<Key, Value>(value);
						break;
				}
			}

			_size++;
		}

		void Remove(Key element)
		{
			_size--;
		}

		Value* Get(Key key)
		{
			BinaryTreeDataNode<Key, Value>* currentNode = _node;

			if (!IsEmpty())
			{
				while (currentNode != nullptr)
				{
					BinaryTreeDirection binaryTreeDirection = CheckNodeDirection(key, *currentNode->NodeID);

					switch (binaryTreeDirection)
					{
						case BinaryTreeDirection::None:
							// Found
							return currentNode->Data;

						case BinaryTreeDirection::Left:
							currentNode = currentNode->LeftNode;
							break;

						case BinaryTreeDirection::Right:
							currentNode = currentNode->RightNode;
							break;
					}
				}				
			}

			throw "Not Found";
		}
	};
}*/