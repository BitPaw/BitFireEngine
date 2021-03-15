#include "VideoConfig.h"

BF::VideoConfig::VideoConfig()
{
	WindowRefreshRateMode = RefreshRateMode::VSync;
	ScreenResolution.Set(1000-150, 1000-250);
	FullScreen = false;
}
