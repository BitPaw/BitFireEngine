#pragma once

#define QuadTreeNodeChildSize 4

#define QuadTreeNodeChildInsertedInField -5
#define QuadTreeNodeChildNotInField -10
#define QuadTreeNodeChildNorthEast -20
#define QuadTreeNodeChildNorthWest -21
#define QuadTreeNodeChildSouthEast -22 
#define QuadTreeNodeChildSouthWest -23

#include "QuadTreePosition.hpp"
#include "QuadTreeDirection.hpp"
#include <cstdlib>

#define QuadTreeNodeEntityChunkLimit 4

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
		size_t DataSize;
		T* Data[QuadTreeNodeEntityChunkLimit];
		QuadTreeNode<NumberType, T>* Node[QuadTreeNodeChildSize];

		QuadTreeNode()
		{
			X = 0;
			Y = 0;
			Width = 0;
			Height = 0;
			DataSize = 0;

			for (size_t i = 0; i < QuadTreeNodeEntityChunkLimit; i++)
			{
				Data[i] = nullptr;
			}

			for (size_t i = 0; i < QuadTreeNodeChildSize; i++)
			{
				Node[i] = nullptr;
			}
		}

		void SizeSet(size_t x, size_t y, size_t width, size_t height)
		{
			X = 0;
			Y = 0;
			Width = 0;
			Height = 0;
		}

		unsigned int FreeEntitys()
		{
			unsigned int freeEntitys = 0;

			for (size_t i = 0; i < QuadTreeNodeEntityChunkLimit; i++)
			{
				freeEntitys += Data[i] ? 0 : 1;
			}

			return freeEntitys;
		}

		unsigned int FreeChilds()
		{
			unsigned int freeSlots = 0;

			for (size_t i = 0; i < QuadTreeNodeChildSize; i++)
			{
				freeSlots += Node[i] ? 0 : 1;
			}

			return freeSlots;
		}
	};
}