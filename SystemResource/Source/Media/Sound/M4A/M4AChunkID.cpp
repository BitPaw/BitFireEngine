#include "M4AChunkID.h"

#include <Container/ClusterInt.h>

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

BF::M4AChunkID BF::ConvertM4AChunkID(const unsigned int chunkID)
{
	switch(chunkID)
	{
		case  M4AChunkIDFTYP: return M4AChunkID::FTYP;
		case  M4AChunkIDMDAT: return M4AChunkID::MDAT; 
		case  M4AChunkIDMOOV: return M4AChunkID::MOOV; 
		case  M4AChunkIDPNOT: return M4AChunkID::PNOT; 
		case  M4AChunkIDUDTA: return M4AChunkID::UDTA; 
		case  M4AChunkIDUUID: return M4AChunkID::UUID;
		case  M4AChunkIDMOOF: return M4AChunkID::MOOF; 
		case  M4AChunkIDFREE: return M4AChunkID::FREE;
		case  M4AChunkIDSKIP: return M4AChunkID::SKIP; 
		case  M4AChunkIDJP2: return M4AChunkID::JP2; 
		case  M4AChunkIDWIDE: return M4AChunkID::WIDE; 
		case  M4AChunkIDLOAD: return M4AChunkID::LOAD; 
		case  M4AChunkIDCTAB: return M4AChunkID::CTAB; 
		case  M4AChunkIDIMAP: return M4AChunkID::IMAP;
		case  M4AChunkIDMATT: return M4AChunkID::MATT; 
		case  M4AChunkIDKMAT: return M4AChunkID::KMAT;
		case  M4AChunkIDCLIP: return M4AChunkID::CLIP;
		case  M4AChunkIDCRGN: return M4AChunkID::CRGN;
		case  M4AChunkIDSYNC: return M4AChunkID::SYNC; 
		case  M4AChunkIDCHAP: return M4AChunkID::CHAP; 
		case  M4AChunkIDTMCD: return M4AChunkID::TMCD; 
		case  M4AChunkIDSCPT: return M4AChunkID::SCPT;
		case  M4AChunkIDSSRC: return M4AChunkID::SSRC; 
		case  M4AChunkIDPICT: return M4AChunkID::PICT;

		default: return M4AChunkID::Invalid;
	}
}