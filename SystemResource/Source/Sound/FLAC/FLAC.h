#pragma once

#include "../Sound.h"

namespace BF
{
	// Free Lossless Audio Codec
	struct FLAC
	{
		public:
		void Load(const char* filePath);
		void Save(const char* filePath);
		void ConvertTo(Sound& sound);
	};
}