#pragma once

#include "UIElement.h"

#include "../Utility/ASCIIString.h"
#include "../Mathematic/Geometry/Shape/Rectangle.h"
#include "../Resources/Font/Font.h"
#include "../Resources/Font/FNT/FNT.h"

namespace BF
{
	class Text : public UIElement
	{
		private:
		List<Rectangle> _textBlockList;

		void CreateText(ASCIIString& text, FNT* font, float x, float y);

		FNT* _font;

		public:
		unsigned int FontID;

		ASCIIString Content;
		int Width;
		int Height;
		Point<float> AncerPosition;

		Text(ASCIIString& text, FNT* font);
		Text(ASCIIString& text, FNT* font, float x, float y);

		void SetTextPosition(float x, float y);
		void SetText(ASCIIString& text);
		void UpdateText(); 
		void PrintObjectData();		
	};
}