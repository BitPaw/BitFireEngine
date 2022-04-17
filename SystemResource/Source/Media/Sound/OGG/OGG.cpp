#include "OGG.h"

#include <File/FileStream.h>

BF::FileActionResult BF::OGG::Load(const wchar_t* filePath)
{
	/*
	File file(filePath);
	file.ReadFromDisk();
	ByteStreamHusk byteStream(file.Data, file.DataSize);

	const char syncPattern[4] = { 'O','g','g','S' };
	char buffer[4];
	char segmentTable[255];

	byteStream.CopyBytesAndMove(buffer, 4);
	unsigned char versionFormat = byteStream.ExtractByteAndMove();
	unsigned long long granulePosition = byteStream.ExtractLongLongAndMove(Endian::Little);
	unsigned int serialNumber = byteStream.ExtractIntegerAndMove(Endian::Little);
	unsigned int pageSequenceNumber = byteStream.ExtractIntegerAndMove(Endian::Little);
	unsigned int checkSum = byteStream.ExtractIntegerAndMove(Endian::Little);
	unsigned char pageSegments = byteStream.ExtractByteAndMove();
	byteStream.CopyBytesAndMove(segmentTable, pageSegments);

	*/

	return FileActionResult::Successful;
}

BF::FileActionResult BF::OGG::Save(const wchar_t* filePath)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::OGG::ConvertTo(Sound& sound)
{
	return FileActionResult::Successful;
}

BF::FileActionResult BF::OGG::ConvertFrom(Sound& sound)
{
	return FileActionResult::Successful;
}