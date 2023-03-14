#ifndef OGGInclude
#define OGGInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct OGGPage_
	{
		unsigned char Version; // Often a zero
		unsigned char HeaderType;
		unsigned long long GranulePosition; // 8 Bytes
		unsigned int SerialNumber;
		unsigned int SequenceNumber;
		unsigned int CRC32CheckSum; // CRC32, is generated using a polynomial value of 0x04C11DB7.
		unsigned char PageSegments;
	}
	OGGPage;

	typedef enum OGGHeaderType_
	{
		OGGHeaderInvalid,
		OGGHeaderContinuation,
		OGGHeaderBeginning,
		OGGHeaderEnd
	}
	OGGHeaderType;

	typedef struct OGG_
	{
		unsigned int __dummy__;
	}
	OGG;

	PXPublic PXActionResult OGGParse(OGG* ogg, const void* data, const PXSize dataSize, PXSize* dataRead);

#ifdef __cplusplus
}
#endif

#endif