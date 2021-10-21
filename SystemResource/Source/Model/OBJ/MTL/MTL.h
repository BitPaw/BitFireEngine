#pragma once

#include "MTLMaterial.h"

namespace BF
{	
	// [.MTL]
	class MTL
	{
		public:
		size_t MaterialListSize;
		MTLMaterial* MaterialList;

		MTL();
		~MTL();

		void Load(const char* filePath);

		void PrintContent();
	};
}