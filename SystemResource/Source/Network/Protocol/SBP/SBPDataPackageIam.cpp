#include "SBPDataPackageIam.h"

#include <OS/User.h>

#include <Memory/Memory.h>
#include <File/ByteStream.h>

BF::SBPDataPackageIam::SBPDataPackageIam()
{
	Format = TextFormatInvalid;
	NameSize = 0;
	NameW[0] = L'\0';

	SymbolID.Value = SBPDataPackageIamID;
}

void BF::SBPDataPackageIam::Fill()
{
	Format = TextFormatUNICODE;

	UserNameGetW(NameW, PathMaxSize, &NameSize);
}

size_t BF::SBPDataPackageIam::Parse(const void* inputData, const size_t inputDataSize)
{
	ByteStream byteStream(inputData, inputDataSize);

	// Add name
	{
		unsigned char formatType = 0;
		unsigned short size = 0;

		byteStream.Read(formatType);
		byteStream.Read(size, EndianLittle);

		NameSize = size;
		Format = (TextFormat)formatType;

		const Byte__* nameStart = byteStream.CursorCurrentAdress();

		switch(Format)
		{
			case TextFormatASCII:
				MemoryCopy(nameStart, size, NameA, PathMaxSize);
				break;

			case TextFormatUNICODE:
				MemoryCopy(nameStart, size, NameW, PathMaxSize);
				break;

			default:
				break;
		}	
	}

	return byteStream.DataCursor;
}

size_t BF::SBPDataPackageIam::Serialize(void* outputData, const size_t outputDataSize) const
{
	ByteStream byteStream(outputData, outputDataSize);

	// Add name
	{	
		const unsigned char formatType = (TextFormat)Format;
		unsigned short size = NameSize;

		byteStream.Write(formatType);
		byteStream.Write(size, EndianLittle);
		byteStream.Write(NameW, size);
	}

	return byteStream.DataCursor;
}