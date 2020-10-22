#include "CameraSettings.h"

BF::CameraSettings::CameraSettings(const unsigned int height, const unsigned int width)
{
	RefreshRate = RefreshRateMode::VSync;
	Mode = CameraMode::Orthographic;

	FieldOfView = 90;
	Height = height;
	Width = width;
	Near = 0.01F;
	//Far = 1000;
	Far = -1;
}

BF::CameraSettings::~CameraSettings()
{
	//delete RefreshRate;
}

float BF::CameraSettings::GetVieldOfViewY()
{
	return FieldOfView / 2.0f;
}

float BF::CameraSettings::GetAspectRatio()
{
	return Width / Height;
}
