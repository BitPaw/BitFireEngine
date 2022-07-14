#include "SBPDataPackageFile.h"

#include <Text/Text.h>
#include <File/ByteStream.h>
#include <Hardware/Memory/Memory.h>

#define SBPDataPackageFileModeIDCreate 0x01
#define SBPDataPackageFileModeIDDelete 0x02
#define SBPDataPackageFileModeIDUpdate 0x03
#define SBPDataPackageFileModeIDMove 0x04
#define SBPDataPackageFileModeIDCopy 0x05
#define SBPDataPackageFileModeIDRename 0x06 

BF::SBPDataPackageFile::SBPDataPackageFile()
{
	SymbolID.Value = SBPDataPackageFileID;

	Mode = SBPDataPackageFileMode::Invalid;

	FilePathSourceFormat = TextFormat::Invalid;
	FilePathSourceSize = 0;
	FilePathSourceW[0] = L'0';

	FilePathTargetFormat = TextFormat::Invalid;
	FilePathTargetSize = 0;
	FilePathTargetW[0] = L'0';

	FileSize = 0;
}

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

	{
		unsigned char modeID = 0;

		byteStream.Read(modeID);

		switch(modeID)
		{
			default:
				return 0;

			case SBPDataPackageFileModeIDCreate:
				Mode = SBPDataPackageFileMode::Create;
				break;

			case SBPDataPackageFileModeIDDelete:
				Mode = SBPDataPackageFileMode::Delete;
				break;

			case SBPDataPackageFileModeIDUpdate:
				Mode = SBPDataPackageFileMode::Update;
				break;

			case SBPDataPackageFileModeIDMove:
				Mode = SBPDataPackageFileMode::Move;
				break;

			case SBPDataPackageFileModeIDCopy:
				Mode = SBPDataPackageFileMode::Copy;
				break;

			case SBPDataPackageFileModeIDRename:
				Mode = SBPDataPackageFileMode::Rename;
				break;
		}
	}

	const unsigned int bitMask = 0b00001111111111111111111111111111;

	// FilePath
	{
		unsigned int FilePathSourceInfoBlock = 0;

		byteStream.Read(FilePathSourceInfoBlock, Endian::Little);		

		unsigned char filePathSourceFormatID = (~bitMask & FilePathSourceInfoBlock) >> 28u;

		FilePathSourceSize = (bitMask & FilePathSourceInfoBlock);
		FilePathSourceFormat = ConvertTextFormat(filePathSourceFormatID);

		byteStream.Read(FilePathSourceA, FilePathSourceSize);
	}

	// FilePath
	{
		unsigned int FilePathSourceInfoBlock = 0;

		byteStream.Read(FilePathSourceInfoBlock, Endian::Little);

		unsigned char filePathSourceFormatID = (~bitMask & FilePathSourceInfoBlock) >> 28u;

		FilePathTargetSize = (bitMask & FilePathSourceInfoBlock);
		FilePathTargetFormat = ConvertTextFormat(filePathSourceFormatID);

		byteStream.Read(FilePathTargetW, FilePathSourceSize);
	}

	byteStream.Read(FileSize, Endian::Little);

	return byteStream.DataCursorPosition;
}

size_t BF::SBPDataPackageFile::Serialize(void* outputData, const size_t outputDataSize) const
{
	ByteStream byteStream(outputData, outputDataSize);

	{
		unsigned char modeID = 0;

		switch(Mode)
		{
			default:
			case BF::SBPDataPackageFileMode::Invalid:
				return 0;

			case BF::SBPDataPackageFileMode::Create:
				modeID = SBPDataPackageFileModeIDCreate;
				break;

			case BF::SBPDataPackageFileMode::Delete:
				modeID = SBPDataPackageFileModeIDDelete;
				break;

			case BF::SBPDataPackageFileMode::Update:
				modeID = SBPDataPackageFileModeIDUpdate;
				break;

			case BF::SBPDataPackageFileMode::Move:
				modeID = SBPDataPackageFileModeIDMove;
				break;

			case BF::SBPDataPackageFileMode::Copy:
				modeID = SBPDataPackageFileModeIDCopy;
				break;

			case BF::SBPDataPackageFileMode::Rename:
				modeID = SBPDataPackageFileModeIDRename;
				break;
		}

		byteStream.Write(modeID);
	}

	

	const unsigned int bitMask = 0b00001111111111111111111111111111;

	// FilePath
	{
		const unsigned char filePathSourceFormatID = ConvertTextFormat(FilePathSourceFormat);
		unsigned int FilePathSourceInfoBlock = FilePathSourceSize | (filePathSourceFormatID << 28u);

		byteStream.Write(FilePathSourceInfoBlock, Endian::Little);

		byteStream.Write(FilePathSourceA, FilePathSourceSize);
	}

	// FilePath
	{
		const unsigned char filePathSourceFormatID = ConvertTextFormat(FilePathTargetFormat);
		unsigned int FilePathSourceInfoBlock = FilePathTargetSize | (filePathSourceFormatID << 28u);

		byteStream.Write(FilePathSourceInfoBlock, Endian::Little);

		byteStream.Write(FilePathTargetA, FilePathTargetSize);
	}

	byteStream.Write(FileSize, Endian::Little);

    return byteStream.DataCursorPosition;
}