#include "SBPDataPackageIam.h"

#include <OS/User.h>

#include <Memory/Memory.h>
#include <File/ParsingStreamX.h>

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
	ParsingStreamX parsingStream(inputData, inputDataSize);

	// Add name
	{
		unsigned char formatType = 0;
		unsigned short size = 0;

		parsingStream.Read(formatType);
		parsingStream.Read(size, EndianLittle);

		NameSize = size;
		Format = (TextFormat)formatType;

		const Byte__* nameStart = parsingStream.CursorCurrentAdress();

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

	return parsingStream.DataCursor;
}

size_t BF::SBPDataPackageIam::Serialize(void* outputData, const size_t outputDataSize) const
{
	ParsingStreamX parsingStream(outputData, outputDataSize);

	// Add name
	{	
		const unsigned char formatType = (TextFormat)Format;
		unsigned short size = NameSize;

		parsingStream.Write(formatType);
		parsingStream.Write(size, EndianLittle);
		parsingStream.Write(NameW, size);
	}

	return parsingStream.DataCursor;
}