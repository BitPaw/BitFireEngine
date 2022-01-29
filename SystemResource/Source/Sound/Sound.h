#pragma once

#include "SoundPlayStyle.hpp"
#include "SoundFormat.h"
#include "../Resource.h"
#include "../File/FileActionResult.hpp"

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

		static SoundFormat FileFormatPeek(const wchar_t* filePath);
		FileActionResult Load();
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath, SoundFormat soundFormat);
	};
}