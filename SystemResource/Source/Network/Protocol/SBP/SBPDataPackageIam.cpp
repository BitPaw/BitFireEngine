#include "SBPDataPackageIam.h"

#include <OS/User.h>
#include <Hardware/Memory/Memory.h>

BF::SBPDataPackageIam::SBPDataPackageIam()
{
	Format = TextFormat::Invalid;
	NameSize = 0;
	NameW[0] = L'\0';

	SymbolID.Value = SBPDataPackageIamID;
}

void BF::SBPDataPackageIam::Fill()
{
	Format = TextFormat::TextUNICODE;

	User::Name(NameW, PathMaxSize, NameSize);
}

size_t BF::SBPDataPackageIam::Parse(const void* inputData, const size_t inputDataSize)
{
	ByteStream byteStream(inputData, inputDataSize);

	// Add name
	{
		unsigned char type = 0;
		unsigned short size = 0;

		byteStream.Read(type);
		byteStream.Read(size, Endian::Little);

		NameSize = size;

		const Byte__* nameStart = byteStream.CursorCurrentAdress();

		switch(type)
		{
			case TextFormatASCII:
				Format = TextFormat::TextASCII;
				Memory::Copy(NameA, nameStart, size);
				break;

			case TextFormatUNICODE:
				Format = TextFormat::TextUNICODE;
				Memory::Copy(NameW, nameStart, size);
				break;

			default:
				break;
		}	
	}

	return byteStream.DataCursorPosition;
}

size_t BF::SBPDataPackageIam::Serialize(void* outputData, const size_t outputDataSize) const
{
	ByteStream byteStream(outputData, outputDataSize);

	// Add name
	{	
		unsigned char type = 0;
		unsigned short size = NameSize;

		switch(Format)
		{
			case BF::TextFormat::TextASCII:
				type = TextFormatASCII;
				break;

			case BF::TextFormat::TextUNICODE:
				type = TextFormatUNICODE;
				break;

			case BF::TextFormat::TextUTF8:
				type = TextFormatUTF8;
				break;
		}

		byteStream.Write(type);
		byteStream.Write(size, Endian::Little);
		byteStream.Write(NameW, size);
	}

	return byteStream.DataCursorPosition;
}