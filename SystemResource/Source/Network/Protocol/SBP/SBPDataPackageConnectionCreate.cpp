#include "SBPDataPackageConnectionCreate.h"

void BF::SBPDataPackageConnectionCreate::Fill(SBPDataPackageConnectionCreateReason reason)
{
	Reason = reason;
}

size_t BF::SBPDataPackageConnectionCreate::Parse(const void* inputData, const size_t inputDataSize)
{
	return size_t();
}

size_t BF::SBPDataPackageConnectionCreate::Serialize(void* outputData, const size_t outputDataSize) const
{
	return size_t();
}
