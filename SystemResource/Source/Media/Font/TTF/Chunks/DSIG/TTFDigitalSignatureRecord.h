#pragma once

namespace BF
{
	struct TTFDigitalSignatureRecord
	{
		public:
		unsigned int Format; // Format of the signature
		unsigned int Length; // Length of signature in bytes
		unsigned int SignatureBlockOffset; // Offset to the signature block from the beginning of the table

		TTFDigitalSignatureRecord();
	};
}