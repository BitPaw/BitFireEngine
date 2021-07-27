#include "ResourceType.hpp"

const char* BF::ResourceTypeToString(ResourceType resourceType)
{
	switch (resourceType)
	{
		default:
		case ResourceType::Unknown:
			return "Unknown";

		case 	ResourceType::Dialog:
			return "Dialog";
		case 	ResourceType::Font:
			return "Font";
		case 	ResourceType::Image:
			return "Image";
		case 	ResourceType::Model:
			return "Model";
		case 	ResourceType::Shader:
			return "Shader";
		case 	ResourceType::Sound:
			return "Sound";


		case ResourceType::Level:
			return "Level";
	}
}
