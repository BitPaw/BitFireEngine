#pragma once

#include "OBJElement.h"
#include "MTL/MTL.h"
#include "OBJLineCommand.h"

#include "../IModelFormat.hpp"

#define OBJNameSize 64u

namespace BF
{
	// [.OBJ] Wavefront - 3D model format
	struct OBJ : public IModelFormat
	{
		private:
		static inline bool ShouldCreateNewMesh(OBJLineCommand objLineCommand, bool isCurrentlyInFaces);
		static inline OBJLineCommand PeekCommandLine(const unsigned short lineTagID);

		public:
		wchar_t Name[OBJNameSize];
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
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Load(const unsigned char* data, const size_t dataSize, const wchar_t* fileName);

		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Model& model);
		FileActionResult ConvertFrom(Model& model);
		void Clear();

		void PrintData();
	};
}