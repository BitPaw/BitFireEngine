#include "TTFDigitalSignatureBlock.h"

BF::TTFDigitalSignatureBlock::TTFDigitalSignatureBlock()
{
	Reserved1 = 0;
	Reserved2 = 0;
	SignatureLength = 0;
	Signature = nullptr;
}
