#include "PortableNetworkGraphicChunk.h"

void PortableNetworkGraphicChunk::Validate()
{
	// Ancillary bit : bit 5 of first byte
	// 0 (uppercase) = critical, 1 (lowercase) = ancillary.

	bool ancillaryBit;

	// Private bit: bit 5 of second byte
	// Must be 0 (uppercase)in files conforming to this version of PNG.


	// Safe-to-copy bit: bit 5 of fourth byte
	// 0 (uppercase) = unsafe to copy, 1 (lowercase) = safe to copy.

}
