#pragma once

#include "RIFF.h"
#include "FMT.h"

#include "../ISoundFormat.hpp"

namespace BF
{
	// Waveform Audio File
	struct WAV : public ISoundFormat
	{
		public:
		RIFF RIFFChunk;
		FMT FMTChunk;

		unsigned int SoundDataSize;
		unsigned char* SoundData; 

		WAV();
		~WAV();

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}