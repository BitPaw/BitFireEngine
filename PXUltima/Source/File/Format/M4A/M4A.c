#include "M4A.h"

#include <File/ParsingStream.h>
#include <Container/ClusterInt.h>
#include <Memory/Memory.h>

#define M4ADebugLog 1

#define M4AChunkIDFTYP MakeInt('f','t','y','p')
#define M4AChunkIDMDAT MakeInt('m','d','a','t')
#define M4AChunkIDMOOV MakeInt('m','o','o','v')
#define M4AChunkIDPNOT MakeInt('p','n','o','t')
#define M4AChunkIDUDTA MakeInt('u','d','t','a')
#define M4AChunkIDUUID MakeInt('u','u','i','d')
#define M4AChunkIDMOOF MakeInt('m','o','o','f')
#define M4AChunkIDFREE MakeInt('f','r','e','e')
#define M4AChunkIDSKIP MakeInt('s','k','i','p')
#define M4AChunkIDJP2 MakeInt('j','P','2',' ')
#define M4AChunkIDWIDE MakeInt('w','i','d','e')
#define M4AChunkIDLOAD MakeInt('l','o','a','d')
#define M4AChunkIDCTAB MakeInt('c','t','a','b')
#define M4AChunkIDIMAP MakeInt('i','m','a','p')
#define M4AChunkIDMATT MakeInt('m','a','t','t')
#define M4AChunkIDKMAT MakeInt('k','m','a','t')
#define M4AChunkIDCLIP MakeInt('c','l','i','p')
#define M4AChunkIDCRGN MakeInt('c','r','g','n')
#define M4AChunkIDSYNC MakeInt('s','y','n','c')
#define M4AChunkIDCHAP MakeInt('c','h','a','p')
#define M4AChunkIDTMCD MakeInt('t','m','c','d')
#define M4AChunkIDSCPT MakeInt('s','c','p','t')
#define M4AChunkIDSSRC MakeInt('s','s','r','c')
#define M4AChunkIDPICT MakeInt('P','I','C','T')

M4AChunkID ConvertToM4AChunkID(const unsigned int chunkID)
{
	switch(chunkID)
	{
		case  M4AChunkIDFTYP: return M4AChunkFTYP;
		case  M4AChunkIDMDAT: return M4AChunkMDAT;
		case  M4AChunkIDMOOV: return M4AChunkMOOV;
		case  M4AChunkIDPNOT: return M4AChunkPNOT;
		case  M4AChunkIDUDTA: return M4AChunkUDTA;
		case  M4AChunkIDUUID: return M4AChunkUUID;
		case  M4AChunkIDMOOF: return M4AChunkMOOF;
		case  M4AChunkIDFREE: return M4AChunkFREE;
		case  M4AChunkIDSKIP: return M4AChunkSKIP;
		case  M4AChunkIDJP2: return M4AChunkJP2;
		case  M4AChunkIDWIDE: return M4AChunkWIDE;
		case  M4AChunkIDLOAD: return M4AChunkLOAD;
		case  M4AChunkIDCTAB: return M4AChunkCTAB;
		case  M4AChunkIDIMAP: return M4AChunkIMAP;
		case  M4AChunkIDMATT: return M4AChunkMATT;
		case  M4AChunkIDKMAT: return M4AChunkKMAT;
		case  M4AChunkIDCLIP: return M4AChunkCLIP;
		case  M4AChunkIDCRGN: return M4AChunkCRGN;
		case  M4AChunkIDSYNC: return M4AChunkSYNC;
		case  M4AChunkIDCHAP: return M4AChunkCHAP;
		case  M4AChunkIDTMCD: return M4AChunkTMCD;
		case  M4AChunkIDSCPT: return M4AChunkSCPT;
		case  M4AChunkIDSSRC: return M4AChunkSSRC;
		case  M4AChunkIDPICT: return M4AChunkPICT;

		default: return M4AChunkInvalid;
	}
}

ActionResult M4AParse(M4A* m4a, const void* data, const size_t dataSize, size_t* dataRead)
{
	ParsingStream parsingStream;

	MemorySet(m4a, sizeof(M4A), 0);
	*dataRead = 0;
	ParsingStreamConstruct(&parsingStream, data, dataSize);

	while(!ParsingStreamIsAtEnd(&parsingStream))
	{
		M4AChunk chunk;

		unsigned int chunkSize = 0;
		ClusterInt typePrimaryID;

		ParsingStreamReadIU(&parsingStream, &chunkSize, EndianBig);
		ParsingStreamReadD(&parsingStream, typePrimaryID.Data, 4u);

		const size_t positionPrediction = parsingStream.DataCursor + chunkSize - 8;
		const M4AChunkID typePrimary = ConvertToM4AChunkID(typePrimaryID.Value);

#if M4ADebugLog
		printf
		(
			"[M4A] Chunk (%c%c%c%c) %i Bytes\n",
			typePrimaryID.A,
			typePrimaryID.B,
			typePrimaryID.C,
			typePrimaryID.D,
			chunkSize
		);
#endif

		switch(typePrimary)
		{
			case M4AChunkFTYP:
			{
				unsigned int sizeB = 0;
				char isoSignature[8]; // isom3gp4

				ParsingStreamReadD(&parsingStream, chunk.TypeSub, 4u);
				ParsingStreamReadUI(&parsingStream, &sizeB, EndianBig);
				ParsingStreamReadD(&parsingStream, isoSignature, 8u);

				break;
			}
			case M4AChunkMDAT:
				break;
			case M4AChunkMOOV:
				break;
			case M4AChunkPNOT:
				break;
			case M4AChunkUDTA:
				break;
			case M4AChunkUUID:
				break;
			case M4AChunkMOOF:
				break;
			case M4AChunkFREE:
				break;
			case M4AChunkSKIP:
				break;
			case M4AChunkJP2:
				break;
			case M4AChunkWIDE:
				break;
			case M4AChunkLOAD:
				break;
			case M4AChunkCTAB:
				break;
			case M4AChunkIMAP:
				break;
			case M4AChunkMATT:
				break;
			case M4AChunkKMAT:
				break;
			case M4AChunkCLIP:
				break;
			case M4AChunkCRGN:
				break;
			case M4AChunkSYNC:
				break;
			case M4AChunkCHAP:
				break;
			case M4AChunkTMCD:
				break;
			case M4AChunkSCPT:
				break;
			case M4AChunkSSRC:
				break;
			case M4AChunkPICT:
				break;

			case M4AChunkInvalid:
			default:
			{
				// Unhandled chunk
				break;
			}
		}

		if(parsingStream.DataCursor < positionPrediction)
		{
			const unsigned int offset = positionPrediction - parsingStream.DataCursor;

#if M4ADebugLog
			printf("[M4A] Illegal allignment detected! Moving %i Bytes\n", offset);
#endif

			parsingStream.DataCursor = positionPrediction;
		}
	}

	return ResultSuccessful;
}