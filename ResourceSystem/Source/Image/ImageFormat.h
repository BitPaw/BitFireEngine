#pragma once

namespace BF
{
	enum class ImageFormat
	{
		BlackAndWhite,
		RGB,
		RGBA
	};

	const char* ImageFormatToString(ImageFormat imageFormat);
}