#pragma once

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

namespace BF
{
	enum class M4AChunkID
	{
		Invalid,

		FTYP,
		MDAT,
		MOOV,
		PNOT,
		UDTA,
		UUID,
		MOOF,
		FREE,
		SKIP,
		JP2,
		WIDE,
		LOAD,
		CTAB,
		IMAP,
		MATT,
		KMAT,
		CLIP,
		CRGN,
		SYNC,
		CHAP,
		TMCD,
		SCPT,
		SSRC,
		PICT
	};

	M4AChunkID ConvertM4AChunkID(const unsigned int chunkID);
}