#include "Material.h"

BF::Material::Material()
{
	Name.Copy("[N/A]");

	// Ranges between 0 and 1000
	Weight = 0;

	Ambient = Position<float>(1,1,1);
	Diffuse = Position<float>(1, 1, 1);
	Specular = Position<float>(1, 1, 1);
	Emission = Position<float>(0, 0, 0);

	Dissolved = 0;

	// range from 0.001 to 10. A value of 1.0 means that light does not bend as it passes through an object.
	Density = 1;

	Illumination = IlluminationMode::None;
}

BF::Material::~Material()
{
}