#pragma once

#include "OBJElement.h"
#include "MTL/MTL.h"
#include "OBJLineCommand.h"

#include "../Model.h"

namespace BF
{
#define OBJNameSize 50u

	// [.OBJ] Wavefront - 3D model format
	struct OBJ
	{
		private:
		bool ShouldCreateNewMesh(OBJLineCommand objLineCommand, bool isCurrentlyInFaces);
		OBJLineCommand PeekCommandLine(const char* commandLine);

		public:
		char Name[OBJNameSize];
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