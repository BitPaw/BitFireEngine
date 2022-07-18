#include "ClipBoardFormat.h"

#include <OS/OSVersion.h>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <Windows.h>

#define ClipBoardFormatTEXT CF_TEXT
#define ClipBoardFormatBITMAP CF_BITMAP
#define ClipBoardFormatMETAFILEPICT CF_METAFILEPICT
#define ClipBoardFormatSYLK CF_SYLK
#define ClipBoardFormatDIF CF_DIF
#define ClipBoardFormatTIFF   CF_TIFF
#define ClipBoardFormatOEMTEXT CF_OEMTEXT
#define ClipBoardFormatDIB CF_DIB
#define ClipBoardFormatPALETTE  CF_PALETTE
#define ClipBoardFormatPENDATA CF_PENDATA
#define ClipBoardFormatRIFF CF_RIFF
#define ClipBoardFormatWAVE CF_WAVE
#define ClipBoardFormatUNICODETEXT CF_UNICODETEXT
#define ClipBoardFormatENHMETAFILE CF_ENHMETAFILE
#define ClipBoardFormatOWNERDISPLAY CF_OWNERDISPLAY
#define ClipBoardFormatDSPTEXT   CF_DSPTEXT
#define ClipBoardFormatDSPBITMAP CF_DSPBITMAP
#define ClipBoardFormatDSPMETAFILEPICT CF_DSPMETAFILEPICT
#define ClipBoardFormatDSPENHMETAFILE  CF_DSPENHMETAFILE
#define ClipBoardFormatPRIVATEFIRST CF_PRIVATEFIRST
#define ClipBoardFormatPRIVATELAST CF_PRIVATELAST
#define ClipBoardFormatGDIOBJFIRST CF_GDIOBJFIRST
#define ClipBoardFormatGDIOBJLAST CF_GDIOBJLAST

#if defined(WindowsAtleastNT)
#define ClipBoardFormatHDROP CF_HDROP
#define ClipBoardFormatLOCALE CF_LOCALE
#else
#define ClipBoardFormatHDROP 15
#define ClipBoardFormatLOCALE 16
#endif

#if defined(WindowsAtleast2000)
#define ClipBoardFormatDIBV5 CF_DIBV5
#else
#define ClipBoardFormatDIBV5 17
#endif

#if defined(WindowsAtleast2000)
#define ClipBoardFormatMAX CF_MAX
#elif defined(WindowsAtleastNT)
#define ClipBoardFormatMAX 17
#else
#define ClipBoardFormatMAX 15
#endif

#endif

unsigned int BF::ToClipBoardFormat(const ClipBoardFormat clipBoardFormat)
{
#if defined(OSUnix)
    return -1;

#elif defined(OSWindows)
	switch (clipBoardFormat)
	{
		default:
		case BF::ClipBoardFormat::Invalid:
			return -1;

		case BF::ClipBoardFormat::Text:
			return ClipBoardFormatTEXT;

		case BF::ClipBoardFormat::BITMAP:
			return ClipBoardFormatBITMAP;

		case BF::ClipBoardFormat::METAFILEPICT:
			return ClipBoardFormatMETAFILEPICT;

		case BF::ClipBoardFormat::SYLK:
			return ClipBoardFormatSYLK;

		case BF::ClipBoardFormat::DIF:
			return ClipBoardFormatDIF;

		case BF::ClipBoardFormat::TIFF:
			return ClipBoardFormatTIFF;

		case BF::ClipBoardFormat::OEMTEXT:
			return ClipBoardFormatOEMTEXT;

		case BF::ClipBoardFormat::DIB:
			return ClipBoardFormatDIB;

		case BF::ClipBoardFormat::PALETTE:
			return ClipBoardFormatPALETTE;

		case BF::ClipBoardFormat::PENDATA:
			return ClipBoardFormatPENDATA;

		case BF::ClipBoardFormat::RIFF:
			return ClipBoardFormatRIFF;

		case BF::ClipBoardFormat::WAVE:
			return ClipBoardFormatWAVE;

		case BF::ClipBoardFormat::UNICODETEXT:
			return ClipBoardFormatUNICODETEXT;

		case BF::ClipBoardFormat::ENHMETAFILE:
			return ClipBoardFormatENHMETAFILE;

		case BF::ClipBoardFormat::HDROP:
			return ClipBoardFormatHDROP;

		case BF::ClipBoardFormat::LOCALE:
			return ClipBoardFormatLOCALE;

		case BF::ClipBoardFormat::DIBV5:
			return ClipBoardFormatDIBV5;

		case BF::ClipBoardFormat::MAX:
			return ClipBoardFormatMAX;

		case BF::ClipBoardFormat::OWNERDISPLAY:
			return ClipBoardFormatOWNERDISPLAY;

		case BF::ClipBoardFormat::DSPTEXT:
			return ClipBoardFormatDSPTEXT;

		case BF::ClipBoardFormat::DSPBITMAP:
			return ClipBoardFormatDSPBITMAP;

		case BF::ClipBoardFormat::DSPMETAFILEPICT:
			return ClipBoardFormatDSPMETAFILEPICT;

		case BF::ClipBoardFormat::DSPENHMETAFILE:
			return ClipBoardFormatDSPENHMETAFILE;

		case BF::ClipBoardFormat::PRIVATEFIRST:
			return ClipBoardFormatPRIVATEFIRST;

		case BF::ClipBoardFormat::PRIVATELAST:
			return ClipBoardFormatPRIVATELAST;

		case BF::ClipBoardFormat::GDIOBJFIRST:
			return ClipBoardFormatGDIOBJFIRST;

		case BF::ClipBoardFormat::GDIOBJLAST:
			return ClipBoardFormatGDIOBJLAST;
	}
#endif
}

BF::ClipBoardFormat BF::ToClipBoardFormat(const unsigned int clipBoardFormat)
{
#if defined(OSUnix)
#elif defined(OSWindows)
	switch (clipBoardFormat)
	{
		case ClipBoardFormatTEXT:
			return BF::ClipBoardFormat::Text;

		case ClipBoardFormatBITMAP:
			return BF::ClipBoardFormat::BITMAP;

		case ClipBoardFormatMETAFILEPICT:
			return BF::ClipBoardFormat::METAFILEPICT;

		case ClipBoardFormatSYLK:
			return BF::ClipBoardFormat::SYLK;

		case ClipBoardFormatDIF:
			return BF::ClipBoardFormat::DIF;

		case ClipBoardFormatTIFF:
			return BF::ClipBoardFormat::TIFF;

		case ClipBoardFormatOEMTEXT:
			return BF::ClipBoardFormat::OEMTEXT;

		case ClipBoardFormatDIB:
			return BF::ClipBoardFormat::DIB;

		case ClipBoardFormatPALETTE:
			return BF::ClipBoardFormat::PALETTE;

		case ClipBoardFormatPENDATA:
			return BF::ClipBoardFormat::PENDATA;

		case ClipBoardFormatRIFF:
			return BF::ClipBoardFormat::RIFF;

		case ClipBoardFormatWAVE:
			return BF::ClipBoardFormat::WAVE;

		case ClipBoardFormatUNICODETEXT:
			return BF::ClipBoardFormat::UNICODETEXT;

		case ClipBoardFormatENHMETAFILE:
			return BF::ClipBoardFormat::ENHMETAFILE;

		case ClipBoardFormatHDROP:
			return BF::ClipBoardFormat::HDROP;

		case ClipBoardFormatLOCALE:
			return BF::ClipBoardFormat::LOCALE;

		case ClipBoardFormatDIBV5:
			return BF::ClipBoardFormat::DIBV5;

		case ClipBoardFormatMAX:
			return BF::ClipBoardFormat::MAX;

		case ClipBoardFormatOWNERDISPLAY:
			return BF::ClipBoardFormat::OWNERDISPLAY;

		case ClipBoardFormatDSPTEXT:
			return BF::ClipBoardFormat::DSPTEXT;

		case ClipBoardFormatDSPBITMAP:
			return BF::ClipBoardFormat::DSPBITMAP;

		case ClipBoardFormatDSPMETAFILEPICT:
			return BF::ClipBoardFormat::DSPMETAFILEPICT;

		case ClipBoardFormatDSPENHMETAFILE:
			return BF::ClipBoardFormat::DSPENHMETAFILE;

		case ClipBoardFormatPRIVATEFIRST:
			return BF::ClipBoardFormat::PRIVATEFIRST;

		case ClipBoardFormatPRIVATELAST:
			return BF::ClipBoardFormat::PRIVATELAST;

		case ClipBoardFormatGDIOBJFIRST:
			return BF::ClipBoardFormat::GDIOBJFIRST;

		case ClipBoardFormatGDIOBJLAST:
			return BF::ClipBoardFormat::GDIOBJLAST;

		default:
			return BF::ClipBoardFormat::Invalid;
	}
	#endif // defined
}
