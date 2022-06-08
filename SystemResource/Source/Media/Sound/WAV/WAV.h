#pragma once

#include "FMT.h"

#include <cstddef>

#include "../ISoundFormat.hpp"
#include <File/FileActionResult.hpp>

namespace BF
{
	// Waveform Audio File
	struct WAV : public ISoundFormat
	{
		public:
		FMT Format;

		unsigned int SoundDataSize; // 32-Bit
		unsigned char* SoundData; 

		WAV();
		~WAV();

		FileActionResult Load(const char* filePath);
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}