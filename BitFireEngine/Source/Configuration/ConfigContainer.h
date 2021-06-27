#pragma once

#include "../../../RenderSystem/Source/VideoConfig.h"
#include "../../../SoundSystem/Source/AudioConfig.h"

namespace BF
{
	class ConfigContainer
	{
		public:
		VideoConfig Video;
		AudioConfig Audio;
	};
}