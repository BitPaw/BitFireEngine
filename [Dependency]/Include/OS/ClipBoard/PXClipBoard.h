#ifndef ClipBoardINCLUDE
#define ClipBoardINCLUDE

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum ClipBoardFormat_
	{
		ClipBoardFormatInvalid,
		ClipBoardFormatText,
		ClipBoardFormatBITMAP,
		ClipBoardFormatMETAFILEPICT,
		ClipBoardFormatSYLK,
		ClipBoardFormatDIF,
		ClipBoardFormatTIFF,
		ClipBoardFormatOEMTEXT,
		ClipBoardFormatDIB,
		ClipBoardFormatPALETTE,
		ClipBoardFormatPENDATA,
		ClipBoardFormatRIFF,
		ClipBoardFormatWAVE,
		ClipBoardFormatUNICODETEXT,
		ClipBoardFormatENHMETAFILE,
		ClipBoardFormatHDROP,
		ClipBoardFormatLOCALE,
		ClipBoardFormatDIBV5,
		ClipBoardFormatMAX,
		ClipBoardFormatOWNERDISPLAY,
		ClipBoardFormatDSPTEXT,
		ClipBoardFormatDSPBITMAP,
		ClipBoardFormatDSPMETAFILEPICT,
		ClipBoardFormatDSPENHMETAFILE,
		ClipBoardFormatPRIVATEFIRST,
		ClipBoardFormatPRIVATELAST,
		ClipBoardFormatGDIOBJFIRST,
		ClipBoardFormatGDIOBJLAST,
	}
	ClipBoardFormat;

	unsigned int PXClipBoardFormatToID(const ClipBoardFormat clipBoardFormat);
	ClipBoardFormat PXClipBoardFormatFromID(const unsigned int clipBoardFormat);

	typedef struct PXClipBoard_
	{
		unsigned int __Dummy_;
	}
	PXClipBoard;

	// Open clipboard, close it imedidly after using!
	// Fails if another window has the clipboard open.
	PXPublic PXActionResult PXClipBoardOpen(PXClipBoard* const clipBoard);

	// Use this right after using!
	PXPublic PXActionResult PXClipBoardClose(PXClipBoard* const clipBoard);

	PXPublic PXActionResult PXClipBoardSet(PXClipBoard* const clipBoard, const ClipBoardFormat format, const void* data);

	PXPublic PXActionResult PXClipBoardClear(PXClipBoard* const clipBoard);


#ifdef __cplusplus
}
#endif

#endif
