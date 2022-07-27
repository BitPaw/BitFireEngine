#pragma once

#include <File/Image.h>

#include <Math/Geometry/Vector4.hpp>

namespace BF
{
	struct ImageFileFormatDetectionInfo
	{
		public:
		ImageFileFormat HintFileExtension;
		ImageFileFormat GuessCurrent;
		ImageFileFormat ResultDetected;
	};

	class ImageX : public Image
	{
		public:
		Vector4<unsigned char> GetPixel(unsigned int x, unsigned int y);

		ImageX();
		~ImageX();

		void FlipHorizontal();
		void FlipVertical();

		void Resize(const size_t width, const size_t height);

		void FillRandome();

		ActionResult Load(const char* filePath);
		ActionResult Load(const wchar_t* filePath);
		ActionResult Load(const unsigned char* fileData, const size_t fileDataSize, const ImageFileFormat imageFileFormat);
	};
}