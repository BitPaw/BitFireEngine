#pragma once

#include "../Sound.h"

namespace BF
{
	// Waveform Audio File
	struct WAV 
	{
		public:
		unsigned short AudioFormat;
		unsigned short NumerOfChannels;
		unsigned int SampleRate;
		unsigned int ByteRate;
		unsigned short BlockAllign;
		unsigned short BitsPerSample;

		unsigned int SoundDataSize;
		unsigned char* SoundData; 

		// Note: The sample data must end on an even byte boundary. Whatever that means. 

		WAV();
		~WAV();

		void Load(const char* filePath);
		void Save(const char* filePath);
		void ConvertTo(Sound& sound);
		void ConvertFrom(Sound& sound);
	};
}