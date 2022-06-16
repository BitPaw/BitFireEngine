#pragma once

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