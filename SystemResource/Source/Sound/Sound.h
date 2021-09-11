#pragma once

#include "SoundPlayStyle.hpp"
#include "SoundFormat.h"
#include "../Resource.h"

namespace BF
{
	class Sound : public Resource
	{
		public:
		unsigned short NumerOfChannels;
		unsigned int SampleRate;
		unsigned short BitsPerSample;

		unsigned int DataSize;
		unsigned char* Data;

		SoundPlayStyle PlayStyle;

		Sound();

		static SoundFormat FileFormatPeek(const char* filePath);
		void Load(const char* filePath);
		void Save(const char* filePath, SoundFormat soundFormat);
	};
}