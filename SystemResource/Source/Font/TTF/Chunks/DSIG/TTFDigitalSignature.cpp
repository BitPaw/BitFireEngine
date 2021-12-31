#include "TTFDigitalSignature.h"

BF::TTFDigitalSignature::TTFDigitalSignature()
{
	Version = 0;
	NumberOfSignatures = 0;
	Flags = 0;
	SignatureRecordList = nullptr;

	SignatureBlockList = nullptr;
}
