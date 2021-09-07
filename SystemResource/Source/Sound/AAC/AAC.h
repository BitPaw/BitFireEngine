#pragma once

#include "../Sound.h"

namespace BF
{
	// Advanced Audio Coding
	struct AAC
	{
		public:
		void Load(const char* filePath);
		void Save(const char* filePath);
		void ConvertTo(Sound& sound);
	};
}