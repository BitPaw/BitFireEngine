#pragma once

#include "RefreshRateMode.h"

class CameraSettings
{
public:
	enum RefreshRateMode RefreshRate;

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