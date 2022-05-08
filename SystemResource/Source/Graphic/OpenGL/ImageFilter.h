#pragma once

namespace BF
{
	enum class ImageFilter
	{
		Invalid,

		// No filter Option, use this for Pixelated Textures.
		NoFilter,

		// Level I Filter
		Bilinear,

		// Level II Filter
		Trilinear
	};
}