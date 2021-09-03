#pragma once

#include "UIElement.h"
#include "../../../SystemResource/Source/Math/Geometry/Shape/Rectangle.h"
#include "../../../SystemResource/Source/Font/Font.h"

namespace BF
{
	class UIText : public UIElement
	{
		private:
		List<Rectangle> _textBlockList;

		Font* _font;

		public:
		Vector2<float> AncerPosition;
		unsigned int FontID;
		char TextContent[255];

		UIText(const char* text, Font& font, float x, float y);
		UIText(AsciiString& text, Font& font, float x, float y);

		void Setup(AsciiString& text, Font& font, float x, float y);

		void SetFont(Font& font);
		void SetTextPosition(float x, float y);

		void SetText(const char* text);
		void SetText(AsciiString& text);
		void UpdateText(); 
		void PrintObjectData();		
	};
}