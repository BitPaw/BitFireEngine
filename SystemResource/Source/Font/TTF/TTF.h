#pragma once

#include "Chunks/TTFHeader.h"
#include "Chunks/TTFHorizontalHeader.h"
#include "Chunks/TTFMaximumProfile.h"
#include "Chunks/TTFCompatibility.h"
#include "Chunks/TTFDigitalSignature.h"
#include "../IFontFormat.hpp"

namespace BF
{
	struct TTF : public IFontFormat
	{
		public:
		TTFHeader Header;
		TTFHorizontalHeader HorizontalHeader;
		TTFMaximumProfile MaximumProfile;
		TTFCompatibility Compatibility;

		TTFDigitalSignature DigitalSignature;

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Font& font);
		FileActionResult ConvertFrom(Font& font);
	};
}