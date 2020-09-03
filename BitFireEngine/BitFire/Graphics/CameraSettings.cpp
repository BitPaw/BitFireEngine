#include "CameraSettings.h"

CameraSettings::CameraSettings(const float height, const float width)
{
	RefreshRate = VSync;

	FieldOfView = 60;
	Height = height;
	Width = width;
	Near = 0.2F;
	Far = 10000;
}

CameraSettings::~CameraSettings()
{
	//delete RefreshRate;
}

float CameraSettings::GetVieldOfViewY()
{
	return FieldOfView / 2.0f;
}

float CameraSettings::GetAspectRatio()
{
	return Width / Height;
}
