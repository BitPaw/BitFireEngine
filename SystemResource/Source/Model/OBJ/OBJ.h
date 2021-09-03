#pragma once

#include "OBJElement.h"
#include "MTL/MTL.h"

#include "../Model.h"

namespace BF
{
	// [.OBJ] Wavefront - 3D model format
	struct OBJ
	{
		public:
		char Name[20];
		unsigned char VertexStructureSize;

		unsigned int MaterialListSize;
		MTL* MaterialList;

		unsigned int ElementListSize;
		OBJElement* ElementList;

		OBJ();
		~OBJ();

		void Load(const char* filePath);
		void Save(const char* filePath);
		void Convert(Model& model);
		void Clear();

		void PrintData();
	};
}