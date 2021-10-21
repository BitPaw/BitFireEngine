#pragma once

#include "OBJElement.h"
#include "MTL/MTL.h"
#include "OBJLineCommand.h"

#include "../IModelFormat.hpp"

namespace BF
{
#define OBJNameSize 50u

	// [.OBJ] Wavefront - 3D model format
	struct OBJ : public IModelFormat
	{
		private:
		static inline bool ShouldCreateNewMesh(OBJLineCommand objLineCommand, bool isCurrentlyInFaces);
		static inline OBJLineCommand PeekCommandLine(const char* commandLine);

		public:
		char Name[OBJNameSize];
		unsigned char VertexStructureSize;

		size_t MaterialFileListSize;
		MTL* MaterialFileList;

		unsigned int ElementListSize;
		OBJElement* ElementList;

		OBJ();
		~OBJ();

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Model& model);
		FileActionResult ConvertFrom(Model& model);
		void Clear();

		void PrintData();
	};
}