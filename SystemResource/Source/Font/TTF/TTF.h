#pragma once

#include "Chunks/TTFHeader.h"
#include "Chunks/TTFHorizontalHeader.h"
#include "Chunks/TTFMaximumProfile.h"
#include "Chunks/TTFLinearThreshold.h"
#include "Chunks/TTFVerticalDeviceMetrics.h"
#include "Chunks/CMAP/CharacterMapping.h"
#include "Chunks/OS2/TTFCompatibility.h"
#include "Chunks/DSIG/TTFDigitalSignature.h"

#include "../IFontFormat.hpp"

namespace BF::TTF
{
	struct TTF : public IFontFormat
	{
		public:
		TTFHeader Header;
		TTFHorizontalHeader HorizontalHeader;
		TTFMaximumProfile MaximumProfile;
		TTFCompatibility Compatibility;

		CMAP::CharacterMapping CharacterMapping;

		TTFDigitalSignature DigitalSignature;
		TTFLinearThreshold LinearThreshold;
		TTFVerticalDeviceMetrics VerticalDeviceMetrics;

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Font& font);
		FileActionResult ConvertFrom(Font& font);
	};
}