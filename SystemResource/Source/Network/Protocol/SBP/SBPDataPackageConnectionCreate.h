#pragma once

#include "SBPDataPackage.h"

namespace BF
{
	enum class SBPDataPackageConnectionCreateReason
	{
		Invalid,

		VoiceChat,
		VideoChat,

		FileTransfer
	};

	class SBPDataPackageConnectionCreate : public SBPDataPackage
	{
		SBPDataPackageConnectionCreateReason Reason;

		void Fill(SBPDataPackageConnectionCreateReason reason);

		virtual size_t Parse(const void* inputData, const size_t inputDataSize) override;
		virtual size_t Serialize(void* outputData, const size_t outputDataSize) const override;
	};
}