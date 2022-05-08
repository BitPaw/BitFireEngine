#pragma once

namespace BF
{
	enum class ImageType
	{
		Invalid,

		Texture2D,
		Texture3D,

		TextureCubeContainer,
		TextureCubeRight, 
		TextureCubeLeft,
		TextureCubeTop,
		TextureCubeDown, 
		TextureCubeBack, 
		TextureCubeFront
	};

	const char* ImageTypeToString(ImageType imageType);
}
