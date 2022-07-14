#pragma once

#include "SBPDataPackage.h"

#include <Text/Text.h>

#define SBPDataPackageTextID MakeInt('T', 'e', 'x', 't')

namespace BF
{
	struct SBPDataPackageText : public SBPDataPackage
	{		
		Text TextData;

		SBPDataPackageText();

		virtual size_t Parse(const void* inputData, const size_t inputDataSize) override;
		virtual size_t Serialize(void* outputData, const size_t outputDataSize) const override;
	};
}