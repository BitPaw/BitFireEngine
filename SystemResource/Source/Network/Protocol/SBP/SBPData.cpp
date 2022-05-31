#include "SBPData.h"

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