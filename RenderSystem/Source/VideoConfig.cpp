#include "VideoConfig.h"

BF::VideoConfig::VideoConfig()
{
	WindowRefreshRateMode = RefreshRateMode::VSync;
	ScreenResolution[0] = 1000 - 150;
	ScreenResolution[1] = 1000 - 250;
	FullScreen = false;
}
