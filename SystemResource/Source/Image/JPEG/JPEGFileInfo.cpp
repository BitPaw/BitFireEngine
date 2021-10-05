#include "JPEGFileInfo.h"

#include <stdlib.h>

BF::JPEGFileInfo::JPEGFileInfo()
{
	Length = 0;
	Identifier[0] = 0;
	VersionMajor = 0;
	VersionMinor = 0;
	DensityUnits = 0;
	DensityX = 0;
	DensityY = 0;
	ThumbnailX = 0;
	ThumbnailY = 0;

	ThumbnailDataSize = 0;
	ThumbnailData = 0;
}

BF::JPEGFileInfo::~JPEGFileInfo()
{
	free(ThumbnailData);
}
