#pragma once


namespace BF
{
	struct PNGHeader
	{
		//  4 bytes
		int Width;

		// 4 bytes
		int Height;

		/* 
			Bit depth is a single-byte integer giving the number of bits per sample or per palette index (not per pixel). 
			Valid values are 1, 2, 4, 8, and 16, although not all values are allowed for all color types. 
		*/
		char BitDepth;

		/* 
			Color type is a single-byte integer that describes the interpretation of the image data. 
			Color type codes represent sums of the following values: 1 (palette used), 2 (color used), 
			and 4 (alpha channel used). Valid values are 0, 2, 3, 4, and 6. 		
		*/
		char ColorType;
		char CompressionMethod;
		char FilterMethod;
		char InterlaceMethod;
	};
}