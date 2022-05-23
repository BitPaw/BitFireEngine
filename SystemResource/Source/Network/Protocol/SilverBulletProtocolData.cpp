#include "SilverBulletProtocolData.h"

BF::SilverBulletProtocolData::SilverBulletProtocolData()
{
	Source = SourceInvalid;
	Target = TargetInvalid;
	Command.Value = MakeInt('#', '#', '#', '#');
	ID = 0;
	DataSize = 0;
	Data = nullptr;
}

void BF::SilverBulletProtocolData::Set(unsigned int command, unsigned int source, unsigned int target, unsigned int id, unsigned int dataSize)
{
	Command.Value = command;
	Source = source;
	Target = target;
	ID = id;
	DataSize = dataSize;
	Data = nullptr;
}