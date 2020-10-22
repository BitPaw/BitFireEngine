#include "VideoConfig.h"

BF::VideoConfig::VideoConfig()
{
	WindowRefreshRateMode = RefreshRateMode::VSync;
	ScreenResolution = Size(1920-150, 1080-250);
	FullScreen = false;
}
