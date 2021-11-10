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

		size_t ElementListSize;
		OBJElement* ElementList;

		OBJ();
		~OBJ();

		//---<GlobalMesh>---
		Vector3<float>* GlobalVertexPosition(size_t index);
		Vector2<float>* GlobalTextureCoordinate(size_t index);
		Vector3<float>* GlobalVertexNormalPosition(size_t index);
		Vector3<float>* GlobalVertexParameter(size_t index);
		Vector3<unsigned int>* GlobalFaceElement(size_t index);
		//------------------

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Model& model);
		FileActionResult ConvertFrom(Model& model);
		void Clear();

		void PrintData();
	};
}