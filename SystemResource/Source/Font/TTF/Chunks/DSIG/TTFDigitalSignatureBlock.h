#pragma once

namespace BF
{
	struct TTFDigitalSignatureBlock
	{
		unsigned short Reserved1; // Reserved for future use; set to zero.
		unsigned short Reserved2; // Reserved for future use; set to zero.
		unsigned int SignatureLength; // Length(in bytes) of the PKCS#7 packet in the signature field.
		char* Signature; // PKCS#7 packet

		TTFDigitalSignatureBlock();
	};
}