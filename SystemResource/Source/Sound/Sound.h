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

		SoundFormat PeekFileFomat(const char* filePath);
		void Load(const char* filePath);
	};
}