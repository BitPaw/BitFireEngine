#ifndef XingInfoInclude
#define XingInfoInclude

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>
#include <File/PXDataStream.h>

#define XingInfoTOCBufferSize 100u

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

	typedef struct XingInfo_
	{
		XingInfoVersion Version;
		unsigned int NumberOfFrames;
		unsigned int SizeInBytes;
		char TOCBuffer[XingInfoTOCBufferSize];
		unsigned int VBRScale; // 0-100
	}
	XingInfo;

	PXPublic PXActionResult XingInfoParse(XingInfo* const xingInfo, PXDataStream* const pxDataStream);

#ifdef __cplusplus
}
#endif

#endif