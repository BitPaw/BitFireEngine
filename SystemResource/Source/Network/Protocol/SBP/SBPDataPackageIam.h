#pragma once

#include "SBPDataPackage.h"

#include <File/FilePath.h>
#include <Text/TextFormat.h>

#define SBPDataPackageIamID MakeInt('I', '\'', 'a', 'm')

namespace BF
{	
	struct SBPDataPackageIam : public SBPDataPackage
	{
		TextFormat Format;
		size_t NameSize;
		union
		{
			char NameA[PathMaxSize];
			wchar_t NameW[PathMaxSize];
		};

		SBPDataPackageIam();

		void Fill();

		virtual size_t Parse(const void* inputData, const size_t inputDataSize) override;
		virtual size_t Serialize(void* outputData, const size_t outputDataSize) const override;
	};
}