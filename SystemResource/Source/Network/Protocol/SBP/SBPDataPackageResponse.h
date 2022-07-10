#pragma once

#include "SBPDataPackage.h"

#define SBPDataPackageResponseID MakeInt('R', 'e', 's', 'p')

namespace BF
{
	enum class SBPDataPackageResponseType
	{
		Invalid,

		OK,

		NoPermission,

		Denied
	};

	struct SBPDataPackageResponse : public SBPDataPackage
	{
		SBPDataPackageResponseType Type;

		SBPDataPackageResponse();

		virtual size_t Parse(const void* inputData, const size_t inputDataSize) override;
		virtual size_t Serialize(void* outputData, const size_t outputDataSize) const override;
	};
}