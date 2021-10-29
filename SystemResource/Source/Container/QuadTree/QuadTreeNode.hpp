#pragma once

#define QuadTreeNodeChildSize 4

#include "QuadTreePosition.hpp"
#include "QuadTreeDirection.hpp"

namespace BF
{
	template<typename NumberType, typename T>
	struct QuadTreeNode
	{
		public:
		NumberType X;
		NumberType Y;
		NumberType Width;
		NumberType Height;
		T* Data;
		QuadTreeNode<NumberType, T>* Node[QuadTreeNodeChildSize] = { nullptr, nullptr, nullptr, nullptr };

		unsigned int FreeSlots()
		{
			unsigned int freeSlots = 0;

			for (size_t i = 0; i < QuadTreeNodeChildSize; i++)
			{
				freeSlots += Node[i] ? 1 : 0;
			}

			return freeSlots;
		}

		QuadTreeDirection DirectChildPosition(QuadTreePosition<NumberType> position)
		{
			bool isInX = X <= position.X && position.X <= Width;
			bool isInY = Y <= position.Y && position.Y <= Height;
			bool isInNode = isInX && isInY;		
			NumberType widthHalf = Width / (NumberType)2;
			NumberType heightHalf = Height / (NumberType)2;
			bool isLowerX = position.X <= widthHalf;
			bool isLowerY = position.Y <= heightHalf;

			if (!isInNode)
			{
				return QuadTreeDirection::None;
			}		
		
			if (isLowerX && isLowerY)
			{
				return QuadTreeDirection::SouthWest;
			}

			if (isLowerX && !isLowerY)
			{
				return QuadTreeDirection::NorthWest;
			}

			if (!isLowerX && isLowerY)
			{
				return QuadTreeDirection::SouthEast;
			}

			return QuadTreeDirection::NorthEast;		
		}
	};
}