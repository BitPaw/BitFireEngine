#pragma once

#include "RefreshRateMode.h"
#include "CameraMode.h"

class CameraSettings
{
public:
	enum RefreshRateMode RefreshRate;
	enum CameraMode Mode;

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