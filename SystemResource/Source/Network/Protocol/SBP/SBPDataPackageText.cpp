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

		TextData.Format = (TextFormat)textModeID;
	}

	byteStream.Read(TextData.SizeInBytes, EndianLittle);
	byteStream.Read(TextData.TextData, TextData.SizeInBytes);

	return byteStream.DataCursor;
}

size_t BF::SBPDataPackageText::Serialize(void* outputData, const size_t outputDataSize) const
{
	ByteStream byteStream(outputData, outputDataSize);

	const unsigned char textModeID = (TextFormat)TextData.Format;

	byteStream.Write(textModeID);
	byteStream.Write(TextData.SizeInBytes, EndianLittle);
	byteStream.Write(TextData.TextData, TextData.SizeInBytes);

	return byteStream.DataCursor;
}