#include "SBPDataPackageText.h"

#include <File/ParsingStreamX.h>

BF::SBPDataPackageText::SBPDataPackageText()
{
	SymbolID.Value = SBPDataPackageTextID;
}

size_t BF::SBPDataPackageText::Parse(const void* inputData, const size_t inputDataSize)
{
	ParsingStreamX parsingStream(inputData, inputDataSize);

	{
		unsigned char textModeID = 0;

		parsingStream.Read(textModeID);

		TextData.Format = (TextFormat)textModeID;
	}

	parsingStream.Read(TextData.SizeInBytes, EndianLittle);
	parsingStream.Read(TextData.TextData, TextData.SizeInBytes);

	return parsingStream.DataCursor;
}

size_t BF::SBPDataPackageText::Serialize(void* outputData, const size_t outputDataSize) const
{
	ParsingStreamX parsingStream(outputData, outputDataSize);

	const unsigned char textModeID = (TextFormat)TextData.Format;

	parsingStream.Write(textModeID);
	parsingStream.Write(TextData.SizeInBytes, EndianLittle);
	parsingStream.Write(TextData.TextData, TextData.SizeInBytes);

	return parsingStream.DataCursor;
}