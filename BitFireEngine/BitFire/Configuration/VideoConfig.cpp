#include "VideoConfig.h"

VideoConfig::VideoConfig()
{
	WindowRefreshRateMode = RefreshRateMode::VSync;
	ScreenResolution = Size(800, 600);
	FullScreen = false;
}
