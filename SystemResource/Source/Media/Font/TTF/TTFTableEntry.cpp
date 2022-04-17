#include "TTFTableEntry.h"

BF::TTFTableEntry::TTFTableEntry()
{
	TypeRaw[0] = '#';
	TypeRaw[1] = '#';
	TypeRaw[2] = '#';
	TypeRaw[3] = '#';
	Type = TTFTableEntryType::UnkownType;
	CheckSum = 0;
	Offset = 0;
	Length = 0;
}