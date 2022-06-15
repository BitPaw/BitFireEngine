#include "XingInfo.h"

#include <File/ByteStream.h>

size_t BF::XingInfo::Parse(const unsigned char* data, const size_t dataSize)
{
	ByteStream dataStream(data, dataSize);

	// parse signature
	{
		const char infoTag[] = { 'I', 'n', 'f', 'o' };
		const char xingTag[] = { 'X', 'i', 'n', 'g' };
		char indetifier[4];

		dataStream.Read(indetifier, 4u);

		const bool isInfo =
			indetifier[0] == infoTag[0] &&
			indetifier[1] == infoTag[1] &&
			indetifier[2] == infoTag[2] &&
			indetifier[3] == infoTag[3];

		const bool isXing =
			indetifier[0] == xingTag[0] &&
			indetifier[1] == xingTag[1] &&
			indetifier[2] == xingTag[2] &&
			indetifier[3] == xingTag[3];

		const bool validHeader = isInfo || isXing;

		if(!validHeader)
		{
			return 0;
		}

		if(isInfo)
		{
			Version = XingInfoVersion::Info;
		}

		if(isXing)
		{
			Version = XingInfoVersion::Xing;
		}
	}	

	unsigned int flags = 0;

	dataStream.Read(flags, Endian::Big);

	const bool hasNumberOfFrames = flags & 0b00000001;
	const bool hasSizeInBytes = (flags & 0b00000010) >> 1;
	const bool hasTOCData = (flags & 0b00000100) >> 2;
	const bool hasVBRScale = (flags & 0b00001000) >> 3;

	// (0x0001) if set, then read one 32 bit integer in Big Endian.
	// It represents the total number of frames in the Audio file.
	if(hasNumberOfFrames)
	{
		dataStream.Read(NumberOfFrames, Endian::Big);
	}

	// (0x0002) is set, then read one 32 bit integer in Big Endian. 
	// It represents the total number of bytes of MPEG Audio in the file. 
	// This does not include the ID3 tag, however, it includes this very tag.
	if(hasSizeInBytes)
	{
		dataStream.Read(SizeInBytes, Endian::Big);
	}

	if(hasTOCData)
	{
		dataStream.Read(TOCBuffer, 100u);
	}

	if(hasVBRScale)
	{
		dataStream.Read(VBRScale, Endian::Big);
	}

	return dataStream.DataCursorPosition;
}
