#ifndef RefreshRateModeInclude
#define RefreshRateModeInclude

#ifdef __cplusplus
extern "C"
{
#endif
#pragma once

	typedef enum RefreshRateMode_
	{
		Unlimited,
		VSync,
		CustomSync
	}
	RefreshRateMode;

#ifdef __cplusplus
}
#endif

#endif