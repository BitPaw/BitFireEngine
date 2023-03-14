#ifndef PXTypeINCLUDE
#define PXTypeINCLUDE

#include <stddef.h>

#include <OS/System/OSVersion.h>

//-- Reivented public / private. The keywords are reserved, so we need other names.
#if OSUnix
#define PXPrivate static
#define PXPublic extern
#elif OSWindows
#define PXDLLExport __declspec(dllexport)
#define PXPrivate static
#define PXPublic extern PXDLLExport // The visual studio compiler also wants this definition, for microsoft stuff.
#endif
//-----------------------------------------------------------------------------

#ifndef PXYes
#define PXYes 1u
#endif

#ifndef PXNo
#define PXNo 0u
#endif

#ifndef PXTrue
#define PXTrue 1u
#endif

#ifndef PXFalse
#define PXFalse 0u
#endif

#ifndef PXNull
#define PXNull 0u
#endif



#ifdef __cplusplus
extern "C"
{
#endif


	typedef enum PXDataType_
	{
		PXDataTypeTypeInvalid,

		PXDataTypeInt8S,
		PXDataTypeInt8U,

		PXDataTypeLEInt16S,
		PXDataTypeLEInt16U,
		PXDataTypeLEInt32S,
		PXDataTypeLEInt32U,
		PXDataTypeLEInt64S,
		PXDataTypeLEInt64U,

		PXDataTypeBEInt16S,
		PXDataTypeBEInt16U,
		PXDataTypeBEInt32S,
		PXDataTypeBEInt32U,
		PXDataTypeBEInt64S,
		PXDataTypeBEInt64U,

		PXDataStreamFloat,
		PXDataStreamDouble
	}
	PXDataType;



	typedef unsigned char PXByte;
	typedef unsigned char PXBool;
	typedef unsigned char* PXAdress;

	// Integer 8-Bit
	typedef char PXInt8S;
	typedef unsigned char PXInt8U;

	// Integer 16-Bit, WORD
	typedef short PXInt16S;
	typedef unsigned short PXInt16U;

	// Integer 8-Bit, DWORD
	typedef int PXInt32S;
	typedef unsigned int PXInt32U;

	// Integer 64-Bit, QWORD
#if OSUnix
    typedef long long PXInt64S;
	typedef unsigned long long PXInt64U;
#elif OSWindows
	typedef __int64 PXInt64S;
	typedef unsigned __int64 PXInt64U;
#endif // OSUnix

#if OS32Bit
	typedef PXInt32U PXSize;
#elif OS64Bit
	typedef PXInt64U PXSize;
#else
#error Invalid Bit Version
#endif

	// Text
	typedef char PXCharASCII;
	typedef wchar_t PXCharUNICODE;
	typedef PXInt32U PXCharUTF8;

	typedef char* const PXTextASCII;
	typedef char* const PXTextUTF8;
	typedef wchar_t* const PXTextUNICODE;


#ifdef __cplusplus
}
#endif

#endif
