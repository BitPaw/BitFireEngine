#pragma once



#define QuadTreeNodeChildInsertedInField -5
#define QuadTreeNodeChildNotInField -10
#define QuadTreeNodeChildNorthEast -20
#define QuadTreeNodeChildNorthWest -21
#define QuadTreeNodeChildSouthEast -22 
#define QuadTreeNodeChildSouthWest -23

#include "../../Math/Geometry/Rectangle.hpp"
#include "QuadTreeDirection.hpp"
#include <cstdlib>


#define QuadTreeNodeChildSize 4
#define QuadTreeNodeEntityChunkLimit 4

namespace BF
{
	// The sub-rectangle in a quadtree
	template<typename NumberType, typename PayloadType>
	struct QuadTreeChunk
	{
		public:
		Rectangle<NumberType> Border;

		QuadTreeChunk<NumberType, PayloadType>* Children[QuadTreeNodeChildSize];

		size_t PayloadListSize;
		PayloadType* PayloadList[QuadTreeNodeEntityChunkLimit];
		
		QuadTreeChunk()
		{
			PayloadListSize = 0;			

			for (size_t i = 0; i < QuadTreeNodeEntityChunkLimit; i++) Children[i] = nullptr;;

			for (size_t i = 0; i < QuadTreeNodeChildSize; i++) PayloadList[i] = nullptr;	
		}		

		void Add(PayloadType&)
		{

		}

		void SizeSet(const size_t x, const size_t y, const size_t width, const size_t height)
		{
			X = 0;
			Y = 0;
			Width = 0;
			Height = 0;
		}

		void Clear()
		{
			//delete PayloadList;	
		}		
	};
}