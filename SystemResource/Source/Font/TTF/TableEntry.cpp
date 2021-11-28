#include "TableEntry.h"

BF::TTF::TableEntry::TableEntry()
{
	TypeRaw[0] = '#';
	TypeRaw[1] = '#';
	TypeRaw[2] = '#';
	TypeRaw[3] = '#';
	Type = TableEntryType::UnkownType;
	CheckSum = 0;
	Offset = 0;
	Length = 0;
}