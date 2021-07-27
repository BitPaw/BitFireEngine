#pragma once

namespace BF
{
	enum class ResourceType
	{
		Unknown,

			Dialog,
			Font,
			Image,
			Model,
			Shader,
			Sound,


			Level
		

	
	};

	const char* ResourceTypeToString(ResourceType resourceType);
}