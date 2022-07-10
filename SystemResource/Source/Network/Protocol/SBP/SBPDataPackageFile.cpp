#include "SBPDataPackageFile.h"

#include <Text/Text.h>
#include <File/ByteStream.h>

void BF::SBPDataPackageFile::Fill(const SBPDataPackageFileMode mode, const char* source, const char* target)
{
    Mode = mode;

	FilePathSourceFormat = TextFormat::TextASCII;
	FilePathSourceSize = Text::Copy(source, PathMaxSize, FilePathSourceA, PathMaxSize);
	
	FilePathTargetFormat = TextFormat::TextASCII;
	FilePathTargetSize = Text::Copy(target, PathMaxSize, FilePathTargetA, PathMaxSize);

	FileSize = 0;
}

size_t BF::SBPDataPackageFile::Parse(const void* inputData, const size_t inputDataSize)
{
	ByteStream byteStream(inputData, inputDataSize);

	return byteStream.DataCursorPosition;
}

size_t BF::SBPDataPackageFile::Serialize(void* outputData, const size_t outputDataSize) const
{
	ByteStream byteStream(outputData, outputDataSize);

    return byteStream.DataCursorPosition;
}