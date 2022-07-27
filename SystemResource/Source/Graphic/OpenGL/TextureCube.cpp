#include "TextureCube.h"

BF::TextureCube::TextureCube()
{
	ID = -1;

	for(size_t i = 0; i < TextureCubeImageListSize; i++)
	{
		ImageConstruct(&ImageList[i]);
	}
}

bool BF::TextureCube::HasTextures()
{
	unsigned int counter = 0;

	for(size_t i = 0; i < TextureCubeImageListSize; i++)
	{
		const Image& image = ImageList[i];		
		const bool hasData = image.PixelData;

		counter += hasData;
	}

	return counter == 6;
}