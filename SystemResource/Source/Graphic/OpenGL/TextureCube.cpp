#include "TextureCube.h"

BF::TextureCube::TextureCube()
{
	ID = -1;
}

bool BF::TextureCube::HasTextures()
{
	unsigned int counter = 0;

	for(size_t i = 0; i < TextureCubeImageListSize; i++)
	{
		const Image& image = ImageList[i];		
		const bool hasData = image.IsDataValid();

		counter += hasData;
	}

	return counter == 6;
}