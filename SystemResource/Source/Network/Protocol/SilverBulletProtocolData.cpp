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