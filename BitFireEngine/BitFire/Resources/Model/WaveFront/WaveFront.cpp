#include "WaveFront.h"
#include <stdio.h>

Position* WaveFront::GetVertexPositionFromGlobalID(unsigned int globalIndex)
{
	unsigned int indexCounter = 0;

	for (unsigned int i = 0; i < ElementListSize; i++)
	{
		WaveFrontElement* element = &ElementList[i];
		const unsigned int listSize = element->VertexPositonListSize;

		indexCounter += listSize;

		if (globalIndex <= indexCounter)
		{
			indexCounter -= listSize;
			indexCounter = (globalIndex - indexCounter);

			return &element->VertexPositionList[indexCounter];
		}
	}

	return nullptr;
}

Point* WaveFront::GetVertexTextureCoordinatesFromGlobalID(unsigned int globalIndex)
{
	
	unsigned int indexCounter = 0;

	for (unsigned int i = 0; i < ElementListSize; i++)
	{
		WaveFrontElement* element = &ElementList[i];
		const unsigned int listSize = element->TextureCoordinateListSize;

		indexCounter += listSize;

		if (globalIndex <= indexCounter)
		{
			indexCounter -= listSize;
			indexCounter = (globalIndex - indexCounter);

			return &element->TextureCoordinateList[indexCounter];
		}
	}

	return nullptr;
}

Position* WaveFront::GetVertexNormalFromGlobalID(unsigned int globalIndex)
{
	unsigned int indexCounter = 0;

	for (unsigned int i = 0; i < ElementListSize; i++)
	{
		WaveFrontElement* element = &ElementList[i];
		const unsigned int listSize = element->VertexNormalPositionListSize;

		indexCounter += listSize;

		if (globalIndex <= indexCounter)
		{
			indexCounter -= listSize;
			indexCounter = (globalIndex - indexCounter);

			return &element->VertexNormalPositionList[indexCounter];
		}
	}

	return nullptr;
}
