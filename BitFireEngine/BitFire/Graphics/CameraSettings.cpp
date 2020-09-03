#include "CameraSettings.h"

CameraSettings::CameraSettings(const float height, const float width)
{
	RefreshRate = VSync;
	Mode = Orthographic;

	FieldOfView = 60;
	Height = height;
	Width = width;
	Near = 0.01F;
	Far = 1000;
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
