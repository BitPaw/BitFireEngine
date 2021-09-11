#pragma once

#include "../../Sound/Sound.h"

namespace BF
{
	struct OGG 
	{
		public:
		void Load(const char* filePath);
		void Save(const char* filePath);
		void ConvertTo(Sound& sound);
		void ConvertFrom(Sound& sound);
	};
}