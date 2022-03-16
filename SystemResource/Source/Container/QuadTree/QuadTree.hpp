#pragma once

#include "QuadTreeChunk.hpp"
#include "../../Math/Geometry/Rectangle.hpp"

#include <cassert>
#include <cstdlib>

namespace BF
{
	enum class QuadTreeResult
	{
		Invalid,

		InvalidParameter,
		OutOfMemory,

		Success,
		ElementOutOfField,
		Dublicate,

		Overlapping,


		QuadrantUpperLeft,
		QuadrantUpperRight,
		QuadrantLowerLeft,
		QuadrantLowerRight
	};

#define QuadChunk QuadTreeChunk<NumberType, PayloadType>

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
			QuadTreeChunk<NumberType, PayloadType>* chunkCurrent = &RootChunk;
			QuadTreeChunk<NumberType, PayloadType>* chunkResult = nullptr;
			QuadTreeResult result = QuadTreeResult::Invalid;

			do
			{
				result = Seek(targetRectangle, data, chunkCurrent, chunkResult);

				chunkCurrent = chunkResult;
			}
			while (result == QuadTreeResult::Success);		
			
			return result;
		}


		// Create childs of not exists.
		// If they exist, function does nothing
		QuadTreeResult CreateChilds(QuadTreeChunk<NumberType, PayloadType>** quadChunk)
		{
			QuadTreeChunk<NumberType, PayloadType>* chunk = new QuadTreeChunk<NumberType, PayloadType>();

			if (!chunk)
			{
				return QuadTreeResult::OutOfMemory;
			}

			*quadChunk = new QuadTreeChunk<NumberType, PayloadType>();
		}

		QuadTreeResult Insert(const NumberType x, const NumberType y, const NumberType width, const NumberType height, PayloadType payload)
		{			
			return Insert(Rectangle<NumberType>(x, y, width, height), payload);
		}

		QuadTreeResult Insert(const Rectangle<NumberType>& rectangle, const PayloadType payload)
		{
			QuadChunk* currentChunk = &RootChunk;
			QuadTreeResult qudrantResult;

			while(true)
			{
				Rectangle<NumberType> resultRectangle;

				qudrantResult = QuadrantCheck(currentChunk->Border, rectangle, resultRectangle);

				switch (qudrantResult)
				{
					case BF::QuadTreeResult::QuadrantUpperLeft:
					case BF::QuadTreeResult::QuadrantUpperRight:
					case BF::QuadTreeResult::QuadrantLowerLeft:
					case BF::QuadTreeResult::QuadrantLowerRight:
					{
						// garantie that memory exists for the childs
						QuadChunk** quadChunk = nullptr;					

						switch (qudrantResult)
						{
							case BF::QuadTreeResult::QuadrantUpperLeft:
								quadChunk = &currentChunk->Children[0];
								break;

							case BF::QuadTreeResult::QuadrantUpperRight:
								quadChunk = &currentChunk->Children[1];
								break;

							case BF::QuadTreeResult::QuadrantLowerLeft:
								quadChunk = &currentChunk->Children[2];
								break;

							case BF::QuadTreeResult::QuadrantLowerRight:
								quadChunk = &currentChunk->Children[3];
								break;								
						}

						if (!(*quadChunk))
						{
							CreateChilds(quadChunk);

							(*quadChunk)->Border = resultRectangle;
						}			

						currentChunk = *quadChunk;

						break;
					}

					case BF::QuadTreeResult::ElementOutOfField:						
						return BF::QuadTreeResult::ElementOutOfField;

					case BF::QuadTreeResult::Overlapping:
					{
						// Insert


						return BF::QuadTreeResult::Success; // Add to this current Node
					}
					default: // Inavlid state
						assert(false);
				}
			}

			return QuadTreeResult::Success;
		}

		QuadTreeResult QuadrantCheck(const Rectangle<NumberType>& border, const Rectangle<NumberType>& target, Rectangle<NumberType>& result)
		{
			const bool isInBorder = border.Contain(target);

			if (!isInBorder)
			{
				return QuadTreeResult::ElementOutOfField;
			}

			const NumberType hMax = (border.X + border.Width);
			const NumberType vMax = (border.X + border.Width);
			const NumberType hMid = hMax / (NumberType)2;
			const NumberType vMid = vMax / (NumberType)2;

			const Rectangle<NumberType> rectangleNW(border.X,    vMid, hMid, vMid);
			const Rectangle<NumberType> rectangleNE(hMid, vMid, hMid, vMid);
			const Rectangle<NumberType> rectangleSW(border.X, border.Y,    hMid, vMid);
			const Rectangle<NumberType> rectangleSE(hMid, border.Y,    hMid, vMid);

			const bool checkNW = rectangleNW.Contain(target);
			const bool checkNE = rectangleNE.Contain(target);
			const bool checkSW = rectangleSW.Contain(target);
			const bool checkSE = rectangleSE.Contain(target);

			const char amount = checkNW + checkNE + checkSW + checkSE;
			

			//assert(amount > 0); // 0 invalidates the first "isInBorder" check

			switch (amount)
			{
				case 0:
					return QuadTreeResult::Overlapping;

				case 1:	// Exact found
				{
					const char quadKey = checkNW * 'A' + checkNE * 'B' + checkSW * 'C' + checkSE * 'D';

					switch (quadKey)
					{
						case 'A': result = rectangleNW;	return QuadTreeResult::QuadrantUpperLeft;
						case 'B': result = rectangleNE; return QuadTreeResult::QuadrantUpperRight;
						case 'C': result = rectangleSW; return QuadTreeResult::QuadrantLowerLeft;
						case 'D': result = rectangleSE; return QuadTreeResult::QuadrantLowerRight;
					}

					break;
				}				
				default:
					assert(false);
			}
		}

		QuadTreeResult Seek
		(
			const Rectangle<NumberType>& rectangle, // boundingbox of data
			PayloadType& data, 
			const QuadTreeChunk<NumberType, PayloadType>* targetAdress, // where to start
			QuadTreeChunk<NumberType, PayloadType>* nextHopAdress // where to add
		)
		{
			if (!targetAdress) // nullponter check
			{
				return QuadTreeResult::InvalidParameter;
			}					
		
			const auto& currentChunk = *targetAdress;

			while (true)
			{
				Rectangle<NumberType> resultRectangle;
				QuadTreeResult qudrantResult = QuadrantCheck(currentChunk.Border, rectangle, resultRectangle); 	// Check for quadrant

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

					case BF::QuadTreeResult::ElementOutOfField:
						return BF::QuadTreeResult::ElementOutOfField;

					case BF::QuadTreeResult::Overlapping:
						nextHopAdress = (QuadTreeChunk<NumberType, PayloadType>*)targetAdress; // removing const
						return BF::QuadTreeResult::Success; // Add to this current Node

					default: // Inavlid state
						assert(false);
				}
			}			

			return QuadTreeResult::Success;
		}
	};
}