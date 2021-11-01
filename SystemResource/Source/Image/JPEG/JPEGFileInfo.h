#pragma once

namespace BF
{
	struct JPEGFileInfo
	{
		public:
		unsigned short Length;
		char Identifier[5];
		unsigned char VersionMajor;
		unsigned char VersionMinor;
		unsigned char DensityUnits;
		unsigned short DensityX;
		unsigned short DensityY;
		unsigned char ThumbnailX;
		unsigned char ThumbnailY;

		unsigned int ThumbnailDataSize;
		unsigned char* ThumbnailData;

		JPEGFileInfo();
		~JPEGFileInfo();
	};
}