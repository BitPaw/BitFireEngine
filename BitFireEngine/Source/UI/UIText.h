#pragma once

#include "UIElement.h"
#include "../../../SystemResource/Source/Math/Geometry/Shape/Rectangle.h"
#include "../../../SystemResource/Source/Font/Font.h"

#define TextSizeMax 1024

namespace BF
{
	class UIText : public UIElement
	{
		private:
		List<Rectangle> _textBlockList;

		Font* _font;

		public:
		Vector2<float> AncerPosition;
		size_t FontID;
		size_t TextSizeCurrent;
		wchar_t TextContent[TextSizeMax];

		UIText();

		void Setup(const wchar_t* text, Font* font, float x, float y);

		void SetFont(Font& font);
		void SetTextPosition(float x, float y);
		void SetText(const char* text);
		void SetText(const wchar_t* text);
		
		void UpdateText(); 
		void PrintObjectData();		
	};
}