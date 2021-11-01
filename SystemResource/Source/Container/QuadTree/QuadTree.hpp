#pragma once

#include "QuadTreeNode.hpp"
#include <cassert>
#include <cstdlib>

namespace BF
{
	template<typename NumberType, class T>
	struct QuadTree
	{
		public:	
		size_t NodeListSize;
		QuadTreeNode<NumberType, T>* NodeList;

        QuadTree()
        {
			NodeListSize = 0;
			NodeList = nullptr;
        }

		~QuadTree()
		{
			free(NodeList);
		}

		void NodeRootSetField(NumberType width, NumberType height)
		{
			NodeList[0].Width = width;
			NodeList[0].Height = height;
		}

		void MemoryReserve(size_t amountOfElements)
		{
			size_t oldLength = NodeListSize;
			void* newData = realloc(NodeList, amountOfElements * sizeof(QuadTreeNode<NumberType, T>));

			assert(newData);		

			NodeList = (QuadTreeNode<NumberType, T>*)newData;
			NodeListSize = amountOfElements;

			for (size_t i = oldLength; i < amountOfElements; i++)
			{
				NodeList[i] = QuadTreeNode<NumberType, T>();
			}
		}

		char Add(NumberType x, NumberType y, NumberType width, NumberType height, T* data)
		{
			size_t nodeDataIndex = 0;

			if (!NodeList)
			{
				MemoryReserve(1);
			}

			return Add(x, y, width, height, data, *NodeList, nodeDataIndex);
		}

		char Add(NumberType x, NumberType y, NumberType width, NumberType height, T* data, QuadTreeNode<NumberType, T>& node, size_t& nodeDataIndex)
		{
			NumberType farPointX = (x + width);
			NumberType farPointY = (y + height);
			bool isSmallerInX = node.X <= x && x <= node.Width;
			bool isSmallerInY = node.Y <= y && y <= node.Height;
			bool isBiggerInX = node.X <= farPointX && farPointX <= node.Width;
			bool isBiggerInY = node.Y <= farPointY && farPointY <= node.Height;
			bool isSmallerInNode = isSmallerInX && isSmallerInY;
			bool isBiggerInNode = isBiggerInX && isBiggerInY;
			bool isHalfInNode = (isSmallerInNode && !isBiggerInNode) || (!isSmallerInNode && isBiggerInNode);
			bool isInNode = isSmallerInNode && isBiggerInNode;

			if (!isInNode)
			{
				return QuadTreeNodeChildNotInField;
			}

			bool needToSplitt = node.FreeEntitys() == 0;
			NumberType widthHalf = node.Width / (NumberType)2;
			NumberType heightHalf = node.Height / (NumberType)2;
			bool isInLowerX = x <= widthHalf && width <= widthHalf;
			bool isInLowerY = y <= heightHalf && height <= heightHalf;
			bool isHigherX = widthHalf < x && widthHalf < width;
			bool isHigherY = widthHalf < y && widthHalf < height;
			bool isBiggerThanOneChildNode = (isInLowerX && isHigherX) || (isHigherX && isHigherY);
			bool storeInCurrentNode = isBiggerThanOneChildNode || isHalfInNode || !needToSplitt;

			bool northWest = !isInLowerX && !isInLowerY;
			bool northEast = isInLowerX && !isInLowerY;
			bool southWest = isInLowerX && isInLowerY;
			bool southEast = !isInLowerX && isInLowerY;

			if (needToSplitt)
			{
				if (NodeListSize < nodeDataIndex)
				{
					NodeListSize += QuadTreeNodeChildSize;
					MemoryReserve(NodeListSize);
				}		
			}

			if (storeInCurrentNode)
			{
				node.Data[node.DataSize++] = data;

				return QuadTreeNodeChildInsertedInField;
			}


			QuadTreeNode<NumberType, T>* nextNode = &NodeList[nodeDataIndex++];
				char ret = 0;


			if (northEast)
			{
				nextNode->SizeSet(node.X + widthHalf, node.Y, node.Width, heightHalf);
				node.Node[0] = nextNode;
				ret = QuadTreeNodeChildNorthEast;
			}

			if (northWest)
			{
				nextNode->SizeSet(node.X, node.Y, widthHalf, widthHalf);
				node.Node[1] = nextNode;
				ret = QuadTreeNodeChildNorthWest;
			}

			if (southEast)
			{
				nextNode->SizeSet(node.X + widthHalf, node.Y + widthHalf, node.Width, node.Height);
				node.Node[2] = nextNode;
				ret = QuadTreeNodeChildSouthEast;
			}

			if (southWest)
			{
				nextNode->SizeSet(node.X, node.Y, widthHalf, heightHalf);
				node.Node[3] = nextNode;
				ret = QuadTreeNodeChildSouthWest;
			}

			Add(x, y, width, height, data, *nextNode, nodeDataIndex);

			return ret;
		}



		void Clear()
		{

		}
	};
}