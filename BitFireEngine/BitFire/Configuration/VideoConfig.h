#pragma once

#include "RefreshRateMode.h"
#include "../Mathematic/Geometry/Size.h"

namespace BF
{
	class VideoConfig
	{
		public:
		RefreshRateMode WindowRefreshRateMode;
		Size ScreenResolution;
		bool FullScreen;

		VideoConfig();
	};
}