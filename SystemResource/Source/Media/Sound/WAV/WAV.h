#pragma once

#include "FMT.h"

#include "../ISoundFormat.hpp"
#include <File/FileActionResult.hpp>

namespace BF
{
	// Waveform Audio File
	struct WAV : public ISoundFormat
	{
		public:
		FMT FMTChunk;

		unsigned int SoundDataSize;
		unsigned char* SoundData; 

		WAV();
		~WAV();

		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}