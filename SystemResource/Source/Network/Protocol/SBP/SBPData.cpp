#include "SBPData.h"
#include <File/ByteStream.h>
#include <Network/Protocol/SBP/SBPText.h>

BF::SBPData::SBPData()
{
	Source = SourceInvalid;
	Target = TargetInvalid;
	Command.Value = MakeInt('#', '#', '#', '#');
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
	Command.Value = command;
	Source = source;
	Target = target;
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
	const unsigned int clearValue = MakeInt('#', '#', '#', '#');
	const unsigned int size = DataSize;
	char* adress = (char*)Data;

	Source = clearValue;
	Target = clearValue;
	Command.Value = clearValue;
	ID = clearValue;
	DataSize = clearValue;
	Data = nullptr;
}

void BF::SBPData::GenerateMessage(const SBPData& data, unsigned char* buffer, size_t& bufferSize, const size_t bufferSizeMax)
{
	ByteStream stream(buffer, bufferSizeMax);

	stream.Write("°°", 2u);
	stream.Write(data.Command.Data, 4u);
	stream.Write(data.Source, Endian::Little);
	stream.Write(data.Target, Endian::Little);
	stream.Write(data.ID, Endian::Little);
	stream.Write(data.DataSize, Endian::Little);

	const Byte* dataStartPoint = (Byte*)data.Data;

	switch(data.Command.Value)
	{
		case SBPIDConnectionCreate:
		{

			break;
		}
		case SBPIDConnectionResult:
		{
			break;
		}
		case SBPIDConnectionKill:
		{
			break;
		}
		case SBPIDFile:
		{
			/*
			SBPFile sbpFile;
			const unsigned short* vale = (const unsigned short*)dataStartPoint;

			const unsigned short block = vale[0];
			const unsigned short size = block & !SBPFilePathSizeMask;
			const unsigned char flags = (block & SBPFilePathSizeMask) >> 12u;

			const unsigned char stringType = flags & SBPFilePathSizeMaskTextType;
			const unsigned char a = flags & SBPFilePathSizeMaskA;
			const unsigned char b = flags & SBPFilePathSizeMaskB;
			const unsigned char c = flags & SBPFilePathSizeMaskC;

			sbpFile.PathSourceSize = */

			break;
		}
		case SBPIDText:
		{
			SBPText sbpText;
			sbpText.Type = dataStartPoint[0];
			sbpText.Text = dataStartPoint + 1u;

			stream.Write(sbpText.Type);
			stream.Write(sbpText.Text, data.DataSize);

			break;
		}

		default:
			break;
	}

	bufferSize = stream.DataCursorPosition;
}