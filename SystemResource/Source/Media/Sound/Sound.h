#pragma once

#include "SoundFormat.h"

#include <Resource.h>
#include <Error/ActionResult.h>

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

		Sound();
		~Sound();

		static SoundFormat FileFormatPeek(const wchar_t* filePath);

		size_t FullSizeInMemory();
		ActionResult Load(const wchar_t* filePath);
		ActionResult Save(const wchar_t* filePath, SoundFormat soundFormat);
	};
}