#pragma once

#include "TTFDigitalSignatureRecord.h"
#include "TTFDigitalSignatureBlock.h"

namespace BF
{
	struct TTFDigitalSignature
	{
		public:
		unsigned int Version;
		unsigned short NumberOfSignatures;
		unsigned short Flags;
		TTFDigitalSignatureRecord* SignatureRecordList;


		TTFDigitalSignatureBlock* SignatureBlockList;

		TTFDigitalSignature();
	};
}