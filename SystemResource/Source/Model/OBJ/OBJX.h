#pragma once

#include <File/Format/OBJ/OBJ.h>
#include <Math/Geometry/Vector2.hpp>
#include <Math/Geometry/Vector3.hpp>
#include <File/FileActionResult.hpp>
#include <Model/Model.h>

namespace BF
{
	struct OBJX : public OBJ
	{
		private:
		static inline bool ShouldCreateNewMesh(OBJLineType objLineCommand, bool isCurrentlyInFaces);

		public:
		OBJX();
		~OBJX();

		//---<GlobalMesh>---
		float* GlobalVertexPosition(size_t index);
		float* GlobalTextureCoordinate(size_t index);
		float* GlobalVertexNormalPosition(size_t index);
		float* GlobalVertexParameter(size_t index);
		unsigned int* GlobalFaceElement(size_t index);
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