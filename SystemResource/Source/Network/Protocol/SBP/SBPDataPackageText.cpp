#include "SBPDataPackageText.h"

#include <File/ByteStream.h>

BF::SBPDataPackageText::SBPDataPackageText()
{
	SymbolID.Value = SBPDataPackageTextID;
}

size_t BF::SBPDataPackageText::Parse(const void* inputData, const size_t inputDataSize)
{
	ByteStream byteStream(inputData, inputDataSize);

	{
		unsigned char textModeID = 0;

		byteStream.Read(textModeID);

		TextData.Format = ConvertTextFormat(textModeID);
	}

	byteStream.Read(TextData.SizeInBytes, Endian::Little);
	byteStream.Read(TextData.TextData, TextData.SizeInBytes);

	return byteStream.DataCursorPosition;
}

size_t BF::SBPDataPackageText::Serialize(void* outputData, const size_t outputDataSize) const
{
	ByteStream byteStream(outputData, outputDataSize);

	const unsigned char textModeID = ConvertTextFormat(TextData.Format);

	byteStream.Write(textModeID);
	byteStream.Write(TextData.SizeInBytes, Endian::Little);
	byteStream.Write(TextData.TextData, TextData.SizeInBytes);

	return byteStream.DataCursorPosition;
}