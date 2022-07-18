#include "SBPData.h"

#include <File/ByteStream.h>
#include <OS/User.h>
#include <Hardware/Memory/Memory.h>

BF::SBPData::SBPData()
{
	SourceID = SourceInvalid;
	TargetID = TargetInvalid;
	CommandID.Value = MakeInt('#', '#', '#', '#');
	ID = 0;
	DataSize = 0;
	Data = nullptr;
}

BF::SBPData::SBPData(const unsigned int command, const unsigned int source, const unsigned int target, const unsigned int id, const unsigned int dataSize, const void* adress)
{
	Set(command, source, target, id, dataSize, adress);
}

void BF::SBPData::Set
(
	const unsigned int command,
	const unsigned int source,
	const unsigned int target,
	const unsigned int id,
	const unsigned int dataSize,
	const void* adress
)
{
	CommandID.Value = command;
	SourceID = source;
	TargetID = target;
	ID = id;
	DataSize = dataSize;
	Data = (void*)adress;
}

unsigned int BF::SBPData::Size()
{
	return 0;
}

void BF::SBPData::Clear()
{
	CommandID.Value = MakeInt('#', '#', '#', '#');
	SourceID = -1;
	TargetID = -1;
	ID = -1;
	DataSize = 0;
	Data = nullptr;
}


void BF::SBPData::Print()
{
	const char commandText[5]
	{
		CommandID.A,
		CommandID.B,
		CommandID.C,
		CommandID.D,
		'\0'
	};

	char sourceText[10];
	char targetText[10];

	if(SourceID >= (unsigned int)SourceLimitMaximum)
	{
		const char* textINN = nullptr;

		switch(TargetID)
		{
			default:
			case SourceInvalid:
				textINN = "Invalid";
				break;

			case SourceMe:
				textINN = "Me";
				break;

			case SourceServer:
				textINN = "Server";
				break;
		}

		sprintf(sourceText, "%s", textINN);
	}
	else
	{
		sprintf(sourceText, "%8X", Source);
	}

	if(TargetID >= (unsigned int)TargetLimitMaximum)
	{
		const char* textINN = nullptr;

		switch(TargetID)
		{
			default:
			case TargetInvalid:
				textINN = "Invalid";
				break;

			case TargetServer:
				textINN = "Me->Ser";
				break;

			case TargetAll:
				textINN = "Me->All";
				break;

			case TargetSpecific:
				textINN = "Me->Oth";
				break;

			case TargetYou:
				textINN = "Ser->You";
				break;

			case TargetYouAndOthers:
				textINN = "Othe->You";
				break;

			case TargetEveryBody:
				textINN = "ToAll";
				break;
		}

		sprintf(targetText, "%s", textINN);
	}
	else
	{
		sprintf(targetText, "%8X", Target);
	}

	printf
	(
		"+---------+----------+----------+----------+----------+\n"
		"| Command |  Source  |  Target  |    ID    |   Data   |\n"
		"| %7s | %8s | %8s | %8X | %6i B |\n"
		"+---------+----------+----------+----------+----------+\n",
		commandText,
		sourceText,
		targetText,
		ID,
		DataSize
	);

	if(DataSize)
	{
		printf("+-------------------[Payload Data]--------------------+\n");
		for(size_t i = 0; i < DataSize; ++i)
		{
			const char* text = (char*)Data;
			const char byte = text[i];
			const bool printableChar = (byte > 0x20) && (byte < 0x7F);
			const char printChar = printableChar ? byte : '.';

			printf("%c", printChar);

			if(((i + 1) % 64) == 0)
			{
				printf("\n");
			}
		}
		printf("\n");
		printf("+-----------------------------------------------------+\n");
	}
}

size_t BF::SBPData::PackageParse(SBPData& data, const void* inputBuffer, const size_t& inputBufferSize)
{
	ByteStream dataStream(inputBuffer, inputBufferSize);

	size_t bufferSize = 0;

	data.Clear();

	// long engigh

	if(inputBufferSize < 22u)
	{
		return 0;
	}

	// Check header
	{
		const bool validHeader = dataStream.ReadAndCompare("°°", 2u);

		if(!validHeader)
		{
			return 0;
		}
	}

	dataStream.Read(data.CommandID.Data, 4u);
	dataStream.Read(data.SourceID, EndianLittle);
	dataStream.Read(data.TargetID, EndianLittle);
	dataStream.Read(data.ID, EndianLittle);
	dataStream.Read(data.DataSize, EndianLittle);

	data.Data = dataStream.CursorCurrentAdress();

	return dataStream.DataCursor;
}

size_t BF::SBPData::PackageSerialize(const SBPData& data, void* outputBuffer, const size_t outputBufferSize)
{
	ByteStream stream(outputBuffer, outputBufferSize);

	stream.Write("°°", 2u);
	stream.Write(data.CommandID.Data, 4u);
	stream.Write(data.SourceID, EndianLittle);
	stream.Write(data.TargetID, EndianLittle);
	stream.Write(data.ID, EndianLittle);
	stream.Write(data.DataSize, EndianLittle);
	stream.Write(data.Data, data.DataSize);

	return stream.DataCursor;
}

size_t BF::SBPData::PackageSerialize
(
	void* outputBuffer,
	const size_t outputBufferSize,
	const unsigned int source,
	const unsigned int target,
	const SBPDataPackage* dataPackage,
	const ResponseID responseID
)
{
	SBPData data;

	data.SourceID = source;
	data.TargetID = target;
	data.ID = responseID;
	data.CommandID.Value = dataPackage->SymbolID.Value;


	const size_t bufferSize = 512u;
	char buffer[bufferSize]{ 0 };

	data.DataSize = dataPackage->Serialize(buffer, bufferSize);
	data.Data = buffer;

	const size_t result = PackageSerialize(data, outputBuffer, outputBufferSize);

	return result;
}