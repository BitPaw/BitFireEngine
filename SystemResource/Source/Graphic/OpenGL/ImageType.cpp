#include "ImageType.h"

const char* BF::ImageTypeToString(ImageType imageType)
{
	switch (imageType)
	{
		case ImageType::Invalid:
			return "Invalid";

		case 	ImageType::Texture2D:
			return "2D";
		case ImageType::Texture3D:
			return "3D";

		case ImageType::TextureCubeContainer:
			return "Cube(Main)";
		case ImageType::TextureCubeRight:
			return "Cube(Right)";
		case ImageType::TextureCubeLeft:
			return "Cube(Left)";
		case ImageType::TextureCubeTop:
			return "Cube(Top)";
		case ImageType::TextureCubeDown:
			return "Cube(Down)";
		case ImageType::TextureCubeBack:
			return "Cube(Back)";
		case ImageType::TextureCubeFront:
			return "Cube(Front)";
	}
}
