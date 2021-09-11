#pragma once

#include "../Sound.h"

namespace BF
{
	// MPEG audio layer 3 file 
	struct MP3
	{
		public:
		void Load(const char* filePath);
		void Save(const char* filePath);
		void ConvertTo(Sound& sound);
		void ConvertFrom(Sound& sound);
	};
}