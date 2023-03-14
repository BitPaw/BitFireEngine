#ifndef M4AInclude
#define M4AInclude

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum M4AChunkID_
	{
		M4AChunkInvalid,
		M4AChunkFTYP,
		M4AChunkMDAT,
		M4AChunkMOOV,
		M4AChunkPNOT,
		M4AChunkUDTA,
		M4AChunkUUID,
		M4AChunkMOOF,
		M4AChunkFREE,
		M4AChunkSKIP,
		M4AChunkJP2,
		M4AChunkWIDE,
		M4AChunkLOAD,
		M4AChunkCTAB,
		M4AChunkIMAP,
		M4AChunkMATT,
		M4AChunkKMAT,
		M4AChunkCLIP,
		M4AChunkCRGN,
		M4AChunkSYNC,
		M4AChunkCHAP,
		M4AChunkTMCD,
		M4AChunkSCPT,
		M4AChunkSSRC,
		M4AChunkPICT
	}
	M4AChunkID;

	typedef struct M4AChunk_
	{
		M4AChunkID TypePrimary;
		char TypeSub[4];
		unsigned int BlockSize;
	}
	M4AChunk;

	typedef struct M4A_
	{
		unsigned int __dummy__;
	}
	M4A;

	static M4AChunkID ConvertToM4AChunkID(const unsigned int chunkID);

	PXPublic PXActionResult M4AParse(M4A* m4a, const void* data, const PXSize dataSize, PXSize* dataRead);

#ifdef __cplusplus
}
#endif

#endif