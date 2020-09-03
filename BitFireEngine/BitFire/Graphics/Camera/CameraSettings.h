#pragma once

#include "CameraMode.h"

#include "../../Configuration/RefreshRateMode.h"

class CameraSettings
{
public:
	RefreshRateMode RefreshRate;
	CameraMode Mode;

	float FieldOfView;
	float Height;
	float Width;
	float Near;
	float Far;

	CameraSettings(const float height, const float width);
	~CameraSettings();

	float GetVieldOfViewY();
	float GetAspectRatio();
};