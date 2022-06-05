#include "FNTLineType.h"

BF::FNTLineType BF::ConvertFNTLineType(const unsigned  char* line)
{
	// input check


	bool isCommonLine			= line[0] == 'c' && line[1] == 'o' && line[2] == 'm' && line[3] == 'm' && line[4] == 'o' && line[5] == 'n' && line[6] == ' ';
	bool isCharacterCountLine	= line[0] == 'c' && line[1] == 'h' && line[2] == 'a' && line[3] == 'r' && line[4] == 's' && line[5] == ' ';
	bool isCharacterDeclareLine = line[0] == 'c' && line[1] == 'h' && line[2] == 'a' && line[3] == 'r' && line[4] == ' ';
	bool isInfoLine				= line[0] == 'i' && line[1] == 'n' && line[2] == 'f' && line[3] == 'o' && line[4] == ' ';
	bool isPageLine				= line[0] == 'p' && line[1] == 'a' && line[2] == 'g' && line[3] == 'e' && line[4] == ' ';

	char code =
		isCommonLine * 1 +
		isCharacterCountLine * 2 +
		isCharacterDeclareLine * 3 +
		isInfoLine * 4 +
		isPageLine * 5;

	switch (code)
	{
		case 1: 
			return FNTLineType::Common;

		case 2:
			return FNTLineType::CharacterCount;

		case 3:
			return FNTLineType::CharacterDefinition;

		case 4:
			return FNTLineType::Info;

		case 5:
			return FNTLineType::Page;

		default:
			return FNTLineType::Unkown;
	}
}