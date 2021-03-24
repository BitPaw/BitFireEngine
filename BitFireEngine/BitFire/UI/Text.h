#pragma once

#include "UIElement.h"

#include "../Utility/AsciiString.h"
#include "../Mathematic/Geometry/Shape/Rectangle.h"
#include "../Resources/Font/Font.h"
#include "../Resources/Font/FNT/FNT.h"

namespace BF
{
	class Text : public UIElement
	{
		private:
		List<Rectangle> _textBlockList;

		void CreateText(AsciiString& text, FNT* font, float x, float y);

		FNT* _font;

		public:
		unsigned int FontID;

		AsciiString Content;
		int Width;
		int Height;
		Point<float> AncerPosition;

		Text(AsciiString& text, FNT* font);
		Text(AsciiString& text, FNT* font, float x, float y);

		void SetTextPosition(float x, float y);
		void SetText(AsciiString& text);
		void UpdateText(); 
		void PrintObjectData();		
	};
}