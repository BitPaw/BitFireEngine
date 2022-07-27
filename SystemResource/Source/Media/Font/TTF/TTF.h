#pragma once

#include <Error/ActionResult.h>

#include "Chunks/TTFHeader.h"
#include "Chunks/TTFHorizontalHeader.h"
#include "Chunks/TTFMaximumProfile.h"
#include "Chunks/TTFLinearThreshold.h"
#include "Chunks/TTFVerticalDeviceMetrics.h"
#include "Chunks/CMAP/TTFCharacterMapping.h"
#include "Chunks/OS2/TTFCompatibility.h"
#include "Chunks/DSIG/TTFDigitalSignature.h"

#include "Chunks/TTFPostScript.h"
#include "Chunks/KERN/TTFKerning.h"
#include "Chunks/CMAP/TTFCharacterMapping.h"
#include <File/Font.h>

namespace BF
{
	struct TTF
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

		ActionResult Load(const char* filePath);
		ActionResult Load(const wchar_t* filePath);
		ActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		ActionResult Save(const wchar_t* filePath);
		ActionResult ConvertTo(Font& font);
		ActionResult ConvertFrom(Font& font);
	};
}