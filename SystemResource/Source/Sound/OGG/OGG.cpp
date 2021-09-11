#include "OGG.h"
#include "../../File/File.h"
#include "../../Container/ByteStreamHusk.h"

void BF::OGG::Load(const char* filePath)
{
	File file(filePath);

	file.Read();

	ByteStreamHusk byteStream((unsigned char*)&file.Data[0], file.Size);;

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
}

void BF::OGG::Save(const char* filePath)
{
}

void BF::OGG::ConvertTo(Sound& sound)
{
}

void BF::OGG::ConvertFrom(Sound& sound)
{
}
