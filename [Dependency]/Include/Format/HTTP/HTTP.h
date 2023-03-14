#ifndef PXHTTPINCLUDE
#define PXHTTPINCLUDE

#include <Format/Type.h>
#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum PXHTTPVersion_
	{
		PXHTTPVersionInvalid,
		PXHTTPVersion1x1,
		PXHTTPVersion2x0
	}
	PXHTTPVersion;

	typedef enum PXHTTPMethod_
	{
		PXHTTPMethodInvalid,
		PXHTTPMethodGet, // Transfer a current representation of the target resource.
		PXHTTPMethodHead, // Same as GET, but do not transfer the response content.
		PXHTTPMethodPost, // Perform resource-specific processing on the request content.
		PXHTTPMethodPut, // Replace all current representations of the target resource with the request content.
		PXHTTPMethodDelete, // Remove all current representations of the target resource.
		PXHTTPMethodConnect, // Establish a tunnel to the server identified by the target resource.
		PXHTTPMethodOptions, // Describe the communication options for the target resource.
		PXHTTPMethodTrace // Perform a message loop-back test along the path to the target resource.
	}
	PXHTTPMethod;

	typedef enum PXHTTPResponseType_
	{
		PXHTTPResponseInvalid,
		PXHTTPResponseSuccess
	}
	PXHTTPResponseType;

	typedef struct PXHTTPRequest_
	{
		PXHTTPMethod Method;
		PXHTTPVersion Version;

		char* TargetName;
		PXSize TargetNameLength;

		char* UserAgent;
		PXSize UserAgentLength;

		// Accept-Language
	}
	PXHTTPRequest;

	typedef struct PXHTTPResponse_
	{
		PXHTTPVersion Version;
		PXHTTPResponseType ResponseType;
	}
	PXHTTPResponse;

	PXPublic PXActionResult PXHTTPRequestParse(PXHTTPRequest* const pxHTTPRequest, PXDataStream* const pxDataStream);
	PXPublic PXActionResult PXHTTPRequestSerialize(PXHTTPRequest* const pxHTTPRequest, PXDataStream* const pxDataStream);

	PXPublic PXActionResult PXHTTPResponseParse(PXHTTPResponse* const pxHTTPResponse, PXDataStream* const pxDataStream);
	PXPublic PXActionResult PXHTTPResponseSerialize(PXHTTPResponse* const pxHTTPResponse, PXDataStream* const pxDataStream);

#ifdef __cplusplus
}
#endif

#endif