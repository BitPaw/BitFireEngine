#pragma once

#include "RefreshRateMode.h"
#include "../Mathematic/Geometry/Size.h"

class VideoConfig
{
public:
	RefreshRateMode WindowRefreshRateMode;
	Size ScreenResolution;
	bool FullScreen;

	VideoConfig();
};