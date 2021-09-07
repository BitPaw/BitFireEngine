#pragma once

#include "../Sound.h"

namespace BF
{
	// mpeg-4 audio file
	struct M4A
	{
		public:
		void Load(const char* filePath);
		void Save(const char* filePath);
		void ConvertTo(Sound& sound);
	};
}