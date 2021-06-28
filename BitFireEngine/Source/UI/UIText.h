#pragma once

#include "UIElement.h"
#include "../../../MathSystem/Source/Geometry/Shape/Rectangle.h"
#include "../../../ResourceSystem/Source/Font/Font.h"

namespace BF
{
	class UIText : public UIElement
	{
		private:
		List<Rectangle> _textBlockList;

		Font* _font;

		public:
		unsigned int FontID;

		void Setup(AsciiString& text, Font& font, float x, float y);

		char TextContent[255];		
		Point<float> AncerPosition;

		UIText(const char* text, Font& font, float x, float y);
		UIText(AsciiString& text, Font& font, float x, float y);		

		void SetFont(Font& font);
		void SetTextPosition(float x, float y);

		void SetText(const char* text);
		void SetText(AsciiString& text);
		void UpdateText(); 
		void PrintObjectData();		
	};
}