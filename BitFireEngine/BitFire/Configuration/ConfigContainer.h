#pragma once

#include "AudioConfig.h"
#include "VideoConfig.h"

namespace BF
{

	class ConfigContainer
	{
		public:
		VideoConfig Video;
		AudioConfig Audio;
	};
}