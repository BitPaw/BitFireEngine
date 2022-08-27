#ifndef OGGInclude
#define OGGInclude

#include <stddef.h>

#include <Error/ActionResult.h>

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

	extern ActionResult OGGParse(OGG* ogg, const void* data, const size_t dataSize, size_t* dataRead);

#ifdef __cplusplus
}
#endif

#endif