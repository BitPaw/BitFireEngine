#pragma once

#include <Format/PXFont.h>

#define TextSizeMax 1024

namespace BF
{
	class UIText
	{
		private:
		float* _textBlockMeshList;
		size_t _textBlockMeshListSize;

		PXFont* _font;

		public:
		float AncerPosition[2];
		size_t FontID;
		size_t TextSizeCurrent;
		wchar_t TextContent[TextSizeMax];

		UIText();

		void Setup(const wchar_t* text, PXFont* font, float x, float y);

		void FontSet(PXFont& font);

		void TextPositionSet(float x, float y);
		void TextSet(const char* text);
		void TextSet(const wchar_t* text);
		void TextUpdate();

		void PrintObjectData();
	};
}
