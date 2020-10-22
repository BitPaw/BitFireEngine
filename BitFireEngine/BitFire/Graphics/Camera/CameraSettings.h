#pragma once

#include "CameraMode.h"

#include "../../Configuration/RefreshRateMode.h"

namespace BF
{

	class CameraSettings
	{
		public:
		RefreshRateMode RefreshRate;
		CameraMode Mode;

		float FieldOfView;
		unsigned int Height;
		unsigned int Width;
		float Near;
		float Far;
		CameraSettings(const unsigned int height, const unsigned int width);
		~CameraSettings();

		float GetVieldOfViewY();
		float GetAspectRatio();
	};
}