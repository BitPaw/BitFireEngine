#pragma once

#include "RIFF.h"
#include "FMT.h"

#include "../Sound.h"
#include "../../ResourceLoadingResult.hpp"

namespace BF
{
	// Waveform Audio File
	struct WAV 
	{
		public:
		RIFF RIFFChunk;
		FMT FMTChunk;

		unsigned int SoundDataSize;
		unsigned char* SoundData; 

		WAV();
		~WAV();

		ResourceLoadingResult Load(const char* filePath);
		ResourceLoadingResult Save(const char* filePath);
		void ConvertTo(Sound& sound);
		void ConvertFrom(Sound& sound);
	};
}