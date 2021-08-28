#include "SkyBox.h"

BF::SkyBox::SkyBox()
{
	Faces[0].Type = ImageType::TextureCubeRight;
	Faces[1].Type = ImageType::TextureCubeLeft;
	Faces[2].Type = ImageType::TextureCubeTop;
	Faces[3].Type = ImageType::TextureCubeDown;
	Faces[4].Type = ImageType::TextureCubeBack;
	Faces[5].Type = ImageType::TextureCubeFront;
}
