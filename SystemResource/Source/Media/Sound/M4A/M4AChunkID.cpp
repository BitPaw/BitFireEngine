#include "M4AChunkID.h"

#include <File/ByteCluster.h>

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