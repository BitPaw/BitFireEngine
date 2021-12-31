#pragma once

#include "TTFFamilyType.h"
#include "TTFSerifStyle.h"
#include "TTFWeight.h"
#include "TTFProportion.h"
#include "TTFContrast.h"
#include "TTFStrokeVariatoon.h"
#include "TTFArmStyle.h"
#include "TTFLetterform.h"
#include "TTFMidline.h"
#include "TTFHeightX.h"

namespace BF
{
	struct TTFPanose
	{
		public:
		TTFFamilyType FamilyType;
		TTFSerifStyle SerifStyle;
		TTFWeight Weight;
		TTFProportion Proportion;
		TTFContrast Contrast;
		TTFStrokeVariatoon StrokeVariation;
		TTFArmStyle ArmStyle;
		TTFLetterform Letterform;
		TTFMidline Midline;
		TTFHeightX HeightX;

		TTFPanose();
	};
}