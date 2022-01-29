#include "Material.h"

BF::Material::Material()
{
	Ambient[0] = 0;
	Ambient[1] = 0;
	Ambient[2] = 0;

	Diffuse[0] = 0;
	Diffuse[1] = 0;
	Diffuse[2] = 0;

	Specular[0] = 0;
	Specular[1] = 0;
	Specular[2] = 0;

	Emission[0] = 0;
	Emission[1] = 0;
	Emission[2] = 0;

	Texture = nullptr;
}

BF::FileActionResult BF::Material::Load()
{
	return FileActionResult::Successful;
}
