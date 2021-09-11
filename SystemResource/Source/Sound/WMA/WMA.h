#pragma once

#include "../Sound.h"

namespace BF
{
	// Windows Media Audio
	struct WMA
	{
		public:
		void Load(const char* filePath);
		void Save(const char* filePath);
		void ConvertTo(Sound& sound);
		void ConvertFrom(Sound& sound);
	};
}