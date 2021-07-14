#pragma once

#include "MTLMaterial.h"

namespace BF
{	
	// [.MTL]
	class MTL
	{
		public:
		unsigned int MaterialListSize;
		MTLMaterial* MaterialList;

		void Load(char* filePath);

		void PrintContent();
	};
}