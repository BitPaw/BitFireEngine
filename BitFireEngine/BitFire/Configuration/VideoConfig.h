#pragma once

#include "RefreshRateMode.h"

#include "../Mathematic/Geometry/Point.hpp"

namespace BF
{
	class VideoConfig
	{
		public:
		RefreshRateMode WindowRefreshRateMode;
		Point<unsigned int> ScreenResolution;
		bool FullScreen;

		VideoConfig();
	};
}