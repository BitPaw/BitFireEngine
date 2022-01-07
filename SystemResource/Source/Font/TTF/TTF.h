#pragma once

#include "Chunks/TTFHeader.h"
#include "Chunks/TTFHorizontalHeader.h"
#include "Chunks/TTFMaximumProfile.h"
#include "Chunks/TTFLinearThreshold.h"
#include "Chunks/TTFVerticalDeviceMetrics.h"
#include "Chunks/CMAP/TTFCharacterMapping.h"
#include "Chunks/OS2/TTFCompatibility.h"
#include "Chunks/DSIG/TTFDigitalSignature.h"

#include "../IFontFormat.hpp"
#include "Chunks/TTFPostScript.h"
#include "Chunks/KERN/TTFKerning.h"
#include "Chunks/CMAP/TTFCharacterMapping.h"

namespace BF
{
	struct TTF : public IFontFormat
	{
		public:
		//---------------------------------------------------------------------
		TTFHeader Header;
		TTFHorizontalHeader HorizontalHeader;
		TTFMaximumProfile MaximumProfile;
		TTFCompatibility Compatibility;

		TTFCharacterMapping CharacterMapping;
		TTFPostScript PostScript;
		TTFKerning Kerning;
		//---------------------------------------------------------------------

		//---<Windows Standard>------------------------------------------------
		TTFDigitalSignature DigitalSignature;
		TTFLinearThreshold LinearThreshold;
		TTFVerticalDeviceMetrics VerticalDeviceMetrics;
		//---------------------------------------------------------------------

		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Font& font);
		FileActionResult ConvertFrom(Font& font);
	};
}