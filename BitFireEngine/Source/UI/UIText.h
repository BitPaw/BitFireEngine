#pragma once

#include "UIElement.h"

#include <Math/Geometry/Rectangle.hpp>
#include <File/Font.h>

#define TextSizeMax 1024

namespace BF
{
	class UIText : public UIElement
	{
		private:
		float* _textBlockMeshList;
		size_t _textBlockMeshListSize;

		CFont* _font;

		public:
		Vector2<float> AncerPosition;
		size_t FontID;
		size_t TextSizeCurrent;
		wchar_t TextContent[TextSizeMax];

		UIText();

		void Setup(const wchar_t* text, CFont* font, float x, float y);

		void FontSet(CFont& font);

		void TextPositionSet(float x, float y);
		void TextSet(const char* text);
		void TextSet(const wchar_t* text);
		void TextUpdate();

		void PrintObjectData();
	};
}
