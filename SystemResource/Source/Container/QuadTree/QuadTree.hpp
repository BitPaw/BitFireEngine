#pragma once

#include "QuadTreeChunk.hpp"

#include <cassert>
#include <cstdlib>

namespace BF
{
	enum class QuadTreeResult
	{
		Invalid,

		InvalidParameter,

		Success,
		ElementOutOfField,
		Dublicate,

		Overlapping,


		QuadrantUpperLeft,
		QuadrantUpperRight,
		QuadrantLowerLeft,
		QuadrantLowerRight
	};

	// 2D-BinaryTree structure
	// NumberType: int, float, double
	// 
	template<typename NumberType, typename PayloadType>
	struct QuadTree
	{
		public:	
		size_t NodeListSize;
		QuadTreeChunk<NumberType, PayloadType> RootChunk;
			
        QuadTree(const NumberType x, const NumberType y, const NumberType width, const NumberType height)
        {
			NodeListSize = 0;
			RootChunk.Border.Set(x, y, width, height);
        }

		~QuadTree()
		{
			RootChunk.Clear();
		}

		void Clear()
		{
			NodeListSize = 0;	
			RootChunk.Clear();
		}

		/*
		void MemoryReserve(size_t amountOfElements)
		{
			size_t oldLength = NodeListSize;
			void* newData = realloc(NodeList, amountOfElements * sizeof(QuadTreeChunk<NumberType, T>));

			assert(newData);		

			NodeList = (QuadTreeChunk<NumberType, T>*)newData;
			NodeListSize = amountOfElements;

			for (size_t i = oldLength; i < amountOfElements; i++)
			{
				NodeList[i] = QuadTreeChunk<NumberType, T>();
			}
		}*/

#define QuadTreeElementOutOfField -1



		QuadTreeResult Search(const NumberType x, const NumberType y, const NumberType width, const NumberType height, PayloadType& data)
		{
			const Rectangle<NumberType> targetRectangle(x, y, width, height);
			QuadTreeChunk<NumberType, PayloadType>* chunkCurrent = nullptr;
			QuadTreeChunk<NumberType, PayloadType>* chunkResult = nullptr;
			QuadTreeResult result = QuadTreeResult::Invalid;

			do
			{
				result = Seek(targetRectangle, data, chunkCurrent, chunkResult);
			}
			while (result == QuadTreeResult::Success);		
			
			return result;
		}

		void Insert()
		{

		}

		QuadTreeResult Seek
		(
			const Rectangle& rectangle, // boundingbox of data
			PayloadType& data, 
			const QuadTreeChunk<NumberType, PayloadType>* targetAdress, // where to start
			QuadTreeChunk<NumberType, PayloadType>* nextHopAdress // where to add
		)
		{
			if (!target) // nullponter check
			{
				return QuadTreeResult::InvalidParameter;
			}

			const auto& currentChunk = *targetAdress;
			const bool isInTarget = currentChunk.Contain(rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height);

			if (!isInTarget)
			{
				return QuadTreeResult::ElementOutOfField;
			}		
		
			while (true)
			{
				QuadTreeResult qudrantResult; 	// Check for quadrant

				switch (qudrantResult)
				{
					case BF::QuadTreeResult::QuadrantUpperLeft:
						nextHopAdress = currentChunk.Children[0];
						break;

					case BF::QuadTreeResult::QuadrantUpperRight:
						nextHopAdress = currentChunk.Children[1];
						break;

					case BF::QuadTreeResult::QuadrantLowerLeft:
						nextHopAdress = currentChunk.Children[2];
						break;

					case BF::QuadTreeResult::QuadrantLowerRight:
						nextHopAdress = currentChunk.Children[3];
						break;

					case BF::QuadTreeResult::Overlapping:
						nextHopAdress = targetAdress;
						return BF::QuadTreeResult::Success; // Add to this current Node

					default: // Inavlid state
						assert(false);
				}
			}			

			return QuadTreeResult::Success;
		}


		char Add(const NumberType x, const NumberType y, const NumberType width, const NumberType height, const PayloadType data)
		{
			return Add(x, y, width, height, data, *NodeList, nodeDataIndex);
		}

		char Add(NumberType x, NumberType y, NumberType width, NumberType height, T* data, QuadTreeChunk<NumberType, T>& node, size_t& nodeDataIndex)
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


			QuadTreeChunk<NumberType, T>* nextNode = &NodeList[nodeDataIndex++];
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
	};
}