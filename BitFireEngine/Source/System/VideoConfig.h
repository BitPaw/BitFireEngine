#pragma once

#include <Video/RefreshRateMode.h>

namespace BF
{
	class VideoConfig
	{
		public:
		RefreshRateMode WindowRefreshRateMode;
		unsigned int ScreenResolution[2];
		bool FullScreen;

		VideoConfig();
	};
}