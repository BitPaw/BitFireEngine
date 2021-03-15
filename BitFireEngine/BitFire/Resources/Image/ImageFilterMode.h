#pragma once

namespace BF
{
	enum class ImageFilterMode
	{
		// No filter Option, use this for Pixelated Textures.
		NoFilter,

		// Level I Filter
		Bilinear,

		// Level II Filter
		Trilinear
	};
}