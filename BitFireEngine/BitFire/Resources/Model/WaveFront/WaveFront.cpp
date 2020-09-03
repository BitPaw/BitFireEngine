#include "WaveFront.h"
#include <stdio.h>

Position* BF::WaveFront::GetVertexPositionFromGlobalID(unsigned int globalIndex)
{
	unsigned int prevMaxIndex = 0;
	unsigned int currentMaximumIndex = 0;
	unsigned int currentIndex = 0;

	for (unsigned int i = 0; i < ElementList.Size.Value; i++)
	{
		WaveFrontElement* element = &ElementList[i];
		const unsigned int listSize = element->VertexPositionList.Size.Value;

		prevMaxIndex = currentMaximumIndex;
		currentMaximumIndex += listSize;

		if (currentMaximumIndex > globalIndex)
		{
			unsigned int index = globalIndex - prevMaxIndex;

			if (index >= listSize)
			{
				printf(" S T O P \n");
			}

			return &element->VertexPositionList[index];
		}
	}

	printf("NULL REFERENCE!!\n");

	return nullptr;
}

Point* BF::WaveFront::GetVertexTextureCoordinatesFromGlobalID(unsigned int globalIndex)
{
	
	unsigned int prevMaxIndex = 0;
	unsigned int currentMaximumIndex = 0;
	unsigned int currentIndex = 0;

	for (unsigned int i = 0; i < ElementList.Size.Value; i++)
	{
		WaveFrontElement* element = &ElementList[i];
		const unsigned int listSize = element->TextureCoordinateList.Size.Value;

		prevMaxIndex = currentMaximumIndex;
		currentMaximumIndex += listSize;

		if (currentMaximumIndex > globalIndex)
		{
			unsigned int index = globalIndex - prevMaxIndex;

			if (index >= listSize)
			{
				printf(" S T O P \n");
			}

			return &element->TextureCoordinateList[index];
		}
	}

	printf("NULL REFERENCE!!\n");




	/*


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
	*/

	return nullptr;
}

Position* BF::WaveFront::GetVertexNormalFromGlobalID(unsigned int globalIndex)
{

	unsigned int prevMaxIndex = 0;
	unsigned int currentMaximumIndex = 0;
	unsigned int currentIndex = 0;

	for (unsigned int i = 0; i < ElementList.Size.Value; i++)
	{
		WaveFrontElement* element = &ElementList[i];
		const unsigned int listSize = element->VertexNormalPositionList.Size.Value;

		prevMaxIndex = currentMaximumIndex;
		currentMaximumIndex += listSize;

		if (currentMaximumIndex > globalIndex)
		{
			unsigned int index = globalIndex - prevMaxIndex;

			if (index >= listSize)
			{
				printf(" S T O P \n");
			}

			return &element->VertexNormalPositionList[index];
		}
	}

	printf("NULL REFERENCE!!\n");




	/*




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
	*/
	return nullptr;
}