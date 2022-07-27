#pragma once

#include <File/Format/PNG/PNG.h>
#include <Error/ActionResult.h>
#include <File/Image.h>

namespace BF
{
	class PNGX : public PNG
	{
		public:
		PNGX();
		~PNGX();

		ActionResult Load(const char* filePath);
		ActionResult Load(const wchar_t* filePath);
		ActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		ActionResult Save(const wchar_t* filePath);

		ActionResult ConvertFrom(Image& image);
		ActionResult ConvertTo(Image& image);
	};
}