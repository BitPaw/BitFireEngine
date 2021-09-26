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
		static inline bool ShouldCreateNewMesh(OBJLineCommand objLineCommand, bool isCurrentlyInFaces);
		static inline OBJLineCommand PeekCommandLine(const char* commandLine);

		public:
		char Name[OBJNameSize];
		unsigned char VertexStructureSize;

		unsigned int MaterialListSize;
		MTL* MaterialList;

		unsigned int ElementListSize;
		OBJElement* ElementList;

		OBJ();
		~OBJ();

		ResourceLoadingResult Load(const char* filePath);
		ResourceLoadingResult Save(const char* filePath);
		void Convert(Model& model);
		void Clear();

		void PrintData();
	};
}