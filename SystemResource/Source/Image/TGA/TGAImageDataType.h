#pragma once

namespace BF
{
	enum class TGAImageDataType
	{
		UnkownImageDataType,

		NoImageDataIsPresent, // 0
		UncompressedColorMapped, // 1
		UncompressedTrueColor, // 2
		UncompressedBlackAndWhite, // 3 (grayscale) image
		RunLengthEncodedColorMapped,  // 9
		RunLengthEncodedTrueColor, // 10
		RunLengthEncodedBlackAndWhite // 11 (grayscale) image 
	};
}