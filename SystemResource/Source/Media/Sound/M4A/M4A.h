#pragma once

#include "../ISoundFormat.hpp"

#include "M4AChunkID.h"

#include <File/ByteCluster.h>

namespace BF
{
	struct M4AChunk
	{
		public:
		M4AChunkID TypePrimary;
		char TypeSub[4];
		unsigned int BlockSize;
	};

	// mpeg-4 audio file
	struct M4A : public ISoundFormat
	{
		public:
		FileActionResult Load(const char* filePath);
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}