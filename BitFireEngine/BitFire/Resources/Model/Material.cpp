#include "Material.h"

BF::Material::Material()
{
	Texture = nullptr;

	Ambient.Set(0, 0, 0);
	Diffuse.Set(0, 0, 0);
	Specular.Set(0, 0, 0);
	Emission.Set(0, 0, 0);
}