#pragma once

namespace BF
{
	enum class ClipBoardFormat
	{
		Invalid,

		Text,
		BITMAP,
		METAFILEPICT,
		SYLK,
		DIF,
		TIFF,
		OEMTEXT,
		DIB,
		PALETTE,
		PENDATA,
		RIFF,
		WAVE,
		UNICODETEXT,
		ENHMETAFILE,
		HDROP,
		LOCALE,
		DIBV5,
		MAX,
		OWNERDISPLAY,
		DSPTEXT,
		DSPBITMAP,
		DSPMETAFILEPICT,
		DSPENHMETAFILE,
		PRIVATEFIRST,
		PRIVATELAST,
		GDIOBJFIRST,
		GDIOBJLAST,
	};

	unsigned int ToClipBoardFormat(const ClipBoardFormat clipBoardFormat);
	ClipBoardFormat ToClipBoardFormat(const unsigned int clipBoardFormat);
}