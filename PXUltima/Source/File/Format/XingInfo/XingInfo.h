#ifndef XingInfoInclude
#define XingInfoInclude

#include <stddef.h>

#include <Error/ActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum XingInfoVersion_
	{
		XingInfoVersionInvalid,
		XingInfoVersionInfo,
		XingInfoVersionXing
	}
	XingInfoVersion;

#define XingInfoTOCBufferSize 100u

	typedef struct XingInfo_
	{
		XingInfoVersion Version;
		unsigned int NumberOfFrames;
		unsigned int SizeInBytes;
		char TOCBuffer[XingInfoTOCBufferSize];
		unsigned int VBRScale; // 0-100
	}
	XingInfo;

	extern ActionResult XingInfoParse(XingInfo* xingInfo, const void* data, const size_t dataSize, size_t* dataRead);

#ifdef __cplusplus
}
#endif

#endif